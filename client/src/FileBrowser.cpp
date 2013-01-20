/*
 * Copyright 2012 Kyle Treubig
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

#include <QtGui>

#include "FileBrowser.h"
#include "SettingKeys.h"

namespace vaultaire
{
	/** Constructor */
	FileBrowser::FileBrowser(QWidget* parent) : QTableView(parent)
	{
		QSettings settings(QSettings::SystemScope,
			qApp->organizationName(), qApp->applicationName(), this);
		libRoot = settings.value(LIB_ROOT_KEY, DEFAULT_LIB_ROOT).toString();

		fsModel = new QFileSystemModel(this);
		fsModel->setFilter(QDir::AllEntries | QDir::AllDirs | QDir::NoDot); // Want ..

		setSelectionMode(QTableView::SingleSelection);
		setSelectionBehavior(QTableView::SelectRows);
		setShowGrid(false);
		setSortingEnabled(true);

		setModel(fsModel);
		horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
		horizontalHeader()->setResizeMode(3, QHeaderView::ResizeToContents);
		verticalHeader()->setVisible(false);
		setRootIndex(fsModel->setRootPath(libRoot));

		connect(this, SIGNAL(activated(QModelIndex)),
			this, SLOT(handleDoubleClick(QModelIndex)));
		connect(selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
			this, SLOT(handleSelection(QModelIndex,QModelIndex)));
	}

	/** Double-click handler */
	void FileBrowser::handleDoubleClick(const QModelIndex& index)
	{
		if (fsModel->isDir(index))
		{
			if (fsModel->data(index).toString() == "..")
			{
				if (fsModel->filePath(rootIndex()) != libRoot)
				{
					QModelIndex parent = fsModel->parent(rootIndex());
					setRootIndex(parent);
					emit directoryChanged(fsModel->filePath(parent));
				}
			}
			else
			{
				setRootIndex(index);
				emit directoryChanged(fsModel->filePath(index));
			}
		}
	}

	/** File-selection handler */
	void FileBrowser::handleSelection(const QModelIndex& index,
		const QModelIndex& prev)
	{
		if (index.row() == prev.row())
			return;

		if ( ! fsModel->isDir(index))
		{
			emit fileSelected(fsModel->filePath(index));
		}
	}
}

