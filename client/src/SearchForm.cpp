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

#include "SearchForm.h"
#include "SettingKeys.h"

namespace vaultaire
{
	/** Constructor */
	SearchForm::SearchForm(QWidget* parent) : QWidget(parent)
	{
		settings = new QSettings(QSettings::SystemScope,
			qApp->organizationName(), qApp->applicationName(), this);

		createButtons();
		createFields();
		updateCollectionAutoCompletion();
		createFSWatcher();

		QHBoxLayout* dateRange = new QHBoxLayout;
		dateRange->addWidget(dateRangeStart);
		dateRange->addWidget(dateRangeEnd);

		QFormLayout* formLayout = new QFormLayout;
		formLayout->addRow(tr("Search Within Date"), useDateRange);
		formLayout->addRow(tr("Date Range"), dateRange);
		formLayout->addRow(tr("Collection"), collection);
		formLayout->addRow(tr("Category"), category);
		formLayout->addRow(tr("Title"), title);
		formLayout->addRow(tr("Tags"), tags);
		formLayout->addRow(tr("Case Insensitive"), caseSensitivity);

		QHBoxLayout* buttonsLayout = new QHBoxLayout;
		buttonsLayout->addWidget(searchButton);
		buttonsLayout->addWidget(resetButton);

		QVBoxLayout* layout = new QVBoxLayout;
		layout->addLayout(formLayout);
		layout->addLayout(buttonsLayout);
		setLayout(layout);
	}

	/* Search button hit */
	void SearchForm::search()
	{
		qDebug() << "search";
	}

	/* Reset button hit */
	void SearchForm::reset()
	{
		dateRangeStart->setDate(QDate::currentDate());
		dateRangeEnd->setDate(QDate::currentDate());
		collection->setCurrentIndex(-1);
		category->setText("");
		title->setText("");
		tags->setText("");
		updateButtons();
	}

	/** Updates buttons to reflect state of form */
	void SearchForm::updateButtons()
	{
		bool useDatesChecked = useDateRange->isChecked();
		bool datesAreValid = (dateRangeStart->date() <= dateRangeEnd->date());
		bool collectionIsEmpty = (collection->currentIndex() >= 0);
		bool categoryIsEmpty = category->text().isEmpty();
		bool titleIsEmpty = title->text().isEmpty();
		bool tagsAreEmpty = tags->text().isEmpty();

		bool datesAreReady = useDatesChecked ? datesAreValid : true;
		bool readyToSearch = datesAreReady && 
			( ! categoryIsEmpty || ! titleIsEmpty || ! tagsAreEmpty);
		bool formIsEmpty = collectionIsEmpty && categoryIsEmpty
			&& titleIsEmpty && tagsAreEmpty;

		searchButton->setEnabled(readyToSearch);
		resetButton->setEnabled( ! formIsEmpty);
	}

	/** Create buttons */
	void SearchForm::createButtons()
	{
		searchButton = new QPushButton(tr("&Search"), this);
		searchButton->setEnabled(false);
		connect(searchButton, SIGNAL(clicked()), this, SLOT(search()));

		resetButton = new QPushButton(tr("&Reset"), this);
		resetButton->setEnabled(false);
		connect(resetButton, SIGNAL(clicked()), this, SLOT(reset()));
	}

	/** Create fields */
	void SearchForm::createFields()
	{
		dateRangeStart = new QDateEdit(QDate::currentDate(), this);
		dateRangeStart->setCalendarPopup(true);
		dateRangeStart->setEnabled(false);
		connect(dateRangeStart, SIGNAL(dateChanged(QDate)),
			this, SLOT(updateButtons()));

		dateRangeEnd = new QDateEdit(QDate::currentDate(), this);
		dateRangeEnd->setCalendarPopup(true);
		dateRangeEnd->setEnabled(false);
		connect(dateRangeEnd, SIGNAL(dateChanged(QDate)),
			this, SLOT(updateButtons()));

		useDateRange = new QCheckBox(this);
		useDateRange->setChecked(false);
		connect(useDateRange, SIGNAL(clicked(bool)),
			this, SLOT(updateButtons()));
		connect(useDateRange, SIGNAL(clicked(bool)),
			dateRangeStart, SLOT(setEnabled(bool)));
		connect(useDateRange, SIGNAL(clicked(bool)),
			dateRangeEnd, SLOT(setEnabled(bool)));

		collection = new QComboBox(this);
		connect(collection, SIGNAL(currentIndexChanged(int)),
			this, SLOT(updateButtons()));

		category = new QLineEdit("", this);
		connect(category, SIGNAL(textEdited(QString)),
			this, SLOT(updateButtons()));

		title = new QLineEdit("", this);
		connect(title, SIGNAL(textEdited(QString)),
			this, SLOT(updateButtons()));

		tags = new QLineEdit("", this);
		connect(tags, SIGNAL(textEdited(QString)),
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
		collection->addItems(dirs);
	}
}

