/*
 * Copyright 2013 Kyle Treubig
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <QtWidgets>

#include "ImageViewer.h"
#include "LibraryEntry.h"
#include "SearchEngine.h"
#include "SearchForm.h"
#include "SearchView.h"
#include "SettingKeys.h"
#include "Settings.h"

namespace vaultaire
{
	//--------------------------------------------------------------------------
	SearchView::SearchView(SearchEngine* engine, QWidget* parent) :
		QSplitter(parent),
		settings(new Settings(this)),
		engine(engine)
	{
		form = new SearchForm(engine, this);
		resultList = new QListWidget(this);
		viewer = new ImageViewer(this);

		connect(engine, SIGNAL(started()), viewer, SLOT(clear()));
		connect(engine, SIGNAL(started()), resultList, SLOT(clear()));
		connect(engine, SIGNAL(finished(QStringList)),
			this, SLOT(searchFinished(QStringList)));
		connect(resultList, SIGNAL(currentRowChanged(int)),
			this, SLOT(resultSelected(int)));

		QVBoxLayout* leftLayout = new QVBoxLayout;
		leftLayout->addWidget(form);
		leftLayout->addWidget(resultList);

		QWidget* leftWidget = new QWidget(this);
		leftWidget->setLayout(leftLayout);

		addWidget(leftWidget);
		addWidget(viewer);
		setStretchFactor(1, 2); // Give more weight to the viewer
	}

	//--------------------------------------------------------------------------
	SearchView::~SearchView()
	{
		// Free up the memory for all the found library entries
		deleteFoundEntries();
	}

	//--------------------------------------------------------------------------
	void SearchView::deleteFoundEntries()
	{
		while ( ! libEntries.isEmpty())
		{
			LibraryEntry* entry = libEntries.takeFirst();
			if (entry != 0)
			{
				delete entry;
			}
		}
	}

	//--------------------------------------------------------------------------
	void SearchView::searchFinished(const QStringList& results)
	{
		deleteFoundEntries();

		const QString libRoot(settings->value(LIB_ROOT_KEY,
			DEFAULT_LIB_ROOT).toString());

		// Populate entries list and results list widget
		for (int i=0; i<results.size(); i++)
		{
			QString foundFilePath = results.at(i);
			qDebug() << "Result #" << i << " " << foundFilePath;

			LibraryEntry* entry;
			if (foundFilePath.contains("ocr"))
			{
				entry = LibraryEntry::fromOcr(foundFilePath);
			}
			else // else meta file
			{
				entry = LibraryEntry::fromMeta(foundFilePath);
			}

			if (entry != 0)
			{
				libEntries.append(entry);

				// Display only partial image file path
				QString displayText = entry->fullImagePath();
				qDebug() << "Entry #" << i << " " << displayText;
				resultList->addItem(displayText.replace(libRoot, ""));
			}
		}
	}

	//--------------------------------------------------------------------------
	void SearchView::resultSelected(int row)
	{
		if (row >= 0 && row < libEntries.size())
		{
			qDebug() << "selected row " << row;
			LibraryEntry* entry = libEntries.at(row);
			qDebug() << "selected " << entry->fullImagePath();
			viewer->open(entry->fullImagePath());
		}
		else
		{
			qWarning() << "Selected invalid row " << row;
		}
	}
}

