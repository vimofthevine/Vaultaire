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

#include "SearchEngine.h"
#include "SearchForm.h"
#include "SettingKeys.h"
#include "Settings.h"

namespace vaultaire
{
	/** Constructor */
	SearchForm::SearchForm(SearchEngine* engine, QWidget* parent) :
		QWidget(parent),
		settings(new Settings(this)),
		engine(engine)
	{
		connect(engine, SIGNAL(started()), this, SLOT(searchStarted()));
		connect(engine, SIGNAL(failed()), this, SLOT(searchFailed()));
		connect(engine, SIGNAL(finished(QStringList)),
			this, SLOT(searchFinished(QStringList)));

		createButtons();
		createFields();
		updateCollectionAutoCompletion();
		createFSWatcher();

		QHBoxLayout* dateFilter = new QHBoxLayout;
		dateFilter->addWidget(year);
		dateFilter->addWidget(month);
		dateFilter->addWidget(date);

		QFormLayout* formLayout = new QFormLayout;
		formLayout->addRow(tr("Date Filter"), dateFilter);
		formLayout->addRow(tr("Collection"), collection);
		formLayout->addRow(tr("Search Field"), field);
		formLayout->addRow(tr("Search Paramter"), parameter);
		formLayout->addRow(tr("Case Insensitive"), caseSensitivity);

		QHBoxLayout* buttonsLayout = new QHBoxLayout;
		buttonsLayout->addWidget(searchButton);
		buttonsLayout->addWidget(resetButton);
		buttonsLayout->addWidget(cancelButton);

		QVBoxLayout* layout = new QVBoxLayout;
		layout->addLayout(formLayout);
		layout->addLayout(buttonsLayout);
		setLayout(layout);
	}

	/* Search button hit */
	void SearchForm::search()
	{
		QString yearStr = year->currentText();
		int yearInt = (yearStr == "None") ? -1 : yearStr.toInt();
		QString collStr = (collection->currentIndex() <= 0)
			? "" : collection->currentText();
		QString fieldStr = (field->currentIndex() <= 0)
			? "" : field->currentText();

		engine->search(
			yearInt,
			month->currentIndex(),
			date->currentIndex(),
			collStr,
			fieldStr,
			parameter->text(),
			caseSensitivity->isChecked());
	}

	/* Reset button hit */
	void SearchForm::reset()
	{
		year->setCurrentIndex(0);
		month->setCurrentIndex(0);
		date->setCurrentIndex(0);
		collection->setCurrentIndex(0);
		field->setCurrentIndex(0);
		parameter->setText("");
		updateButtons();
	}

	/* Search started slot */
	void SearchForm::searchStarted()
	{
		qDebug() << "search started...";
		enableFields(false);
		searchButton->setEnabled(false);
		resetButton->setEnabled(false);
		cancelButton->setEnabled(true);
	}

	/* Search failed slot */
	void SearchForm::searchFailed()
	{
		qDebug() << "search failed";
		QMessageBox::warning(this, tr("Search Failed"),
			tr("An error occured searching the library"));
		enableFields(true);
		updateButtons();
		cancelButton->setEnabled(false);
	}

	/** Search finished slot */
	void SearchForm::searchFinished(const QStringList& results)
	{
		qDebug() << "Search finished: " << results;
		enableFields(true);
		updateButtons();
		cancelButton->setEnabled(false);
	}

	/** Enables/disables fields */
	void SearchForm::enableFields(bool enabled)
	{
		year->setEnabled(enabled);
		month->setEnabled(enabled);
		date->setEnabled(enabled);
		collection->setEnabled(enabled);
		field->setEnabled(enabled);
		parameter->setEnabled(enabled);
		caseSensitivity->setEnabled(enabled);
	}

	/** Updates buttons to reflect state of form */
	void SearchForm::updateButtons()
	{
		//bool collectionIsEmpty = (collection->currentIndex() <= 0);
		bool fieldIsEmpty = (field->currentIndex() < 0);
		bool parameterIsEmpty = parameter->text().isEmpty();

		bool readyToSearch = ( ! fieldIsEmpty && ! parameterIsEmpty);
		bool formIsEmpty = parameterIsEmpty;

		searchButton->setEnabled(readyToSearch);
		resetButton->setEnabled( ! formIsEmpty);
	}

	/** Create buttons */
	void SearchForm::createButtons()
	{
		searchButton = new QPushButton(QIcon::fromTheme("edit-find"),
			tr("&Search"), this);
		searchButton->setEnabled(false);
		connect(searchButton, SIGNAL(clicked()), this, SLOT(search()));

		resetButton = new QPushButton(QIcon::fromTheme("edit-clear"),
			tr("&Reset"), this);
		resetButton->setEnabled(false);
		connect(resetButton, SIGNAL(clicked()), this, SLOT(reset()));

		cancelButton = new QPushButton(QIcon::fromTheme("edit-delete"),
			tr("&Cancel"), this);
		cancelButton->setEnabled(false);
		connect(cancelButton, SIGNAL(clicked()), engine, SLOT(cancel()));
	}

	/** Create fields */
	void SearchForm::createFields()
	{
		year = new QComboBox(this);
		year->addItem("None");
		for (int i=QDate::currentDate().year(); i>=1970; i--)
		{
			year->addItem(QString("%1").arg(i));
		}
		connect(year, SIGNAL(currentIndexChanged(int)),
			this, SLOT(updateButtons()));

		month = new QComboBox(this);
		month->addItem("None");
		for (int i=1; i<=12; i++)
		{
			month->addItem(QDate::longMonthName(i));
		}
		connect(month, SIGNAL(currentIndexChanged(int)),
			this, SLOT(updateButtons()));

		date = new QComboBox(this);
		date->addItem("None");
		for (int i=1; i<=31; i++)
		{
			date->addItem(QString("%1").arg(i));
		}
		connect(date, SIGNAL(currentIndexChanged(int)),
			this, SLOT(updateButtons()));

		collection = new QComboBox(this);
		connect(collection, SIGNAL(currentIndexChanged(int)),
			this, SLOT(updateButtons()));

		field = new QComboBox(this);
		field->addItem("All");
		field->addItem("Category");
		field->addItem("Title");
		field->addItem("Tags");
		field->addItem("OCR");
		connect(field, SIGNAL(currentIndexChanged(int)),
			this, SLOT(updateButtons()));

		parameter = new QLineEdit("", this);
		connect(parameter, SIGNAL(textEdited(QString)),
			this, SLOT(updateButtons()));

		caseSensitivity = new QCheckBox(this);
		caseSensitivity->setChecked(false);
	}

	/** Create file system watcher */
	void SearchForm::createFSWatcher()
	{
		QString libRoot = settings->value(LIB_ROOT_KEY,
			DEFAULT_LIB_ROOT).toString();
		watcher = new QFileSystemWatcher;
		watcher->addPath(libRoot);
		connect(watcher, SIGNAL(directoryChanged(QString)),
			this, SLOT(updateCollectionAutoCompletion()));
	}

	/** Update collection options */
	void SearchForm::updateCollectionAutoCompletion()
	{
		qDebug() << "updating collection options";
		QString libRoot = settings->value(LIB_ROOT_KEY,
			DEFAULT_LIB_ROOT).toString();
		qDebug() << libRoot;

		QDir dir(libRoot);
		QStringList dirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
		qDebug() << dirs;

		collection->clear();
		collection->addItem("All");
		collection->addItems(dirs);
		collection->setCurrentIndex(0);
	}
}

