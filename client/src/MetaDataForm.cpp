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

#include <QtGui>

#include "MetaDataForm.h"
#include "SettingKeys.h"

namespace vaultaire
{
	//--------------------------------------------------------------------------
	MetaDataForm::MetaDataForm(QSettings* settings, QWidget* parent)
		: QWidget(parent), settings(settings)
	{
		createFields();
		updateCollectionAutoCompletion();
		createFileSystemWatcher();

		QFormLayout* form = new QFormLayout;
		form->addRow(tr("Date"), date);
		form->addRow(tr("Collection"), collection);
		form->addRow(tr("Category"), category);
		form->addRow(tr("Title"), title);
		form->addRow(tr("Tags"), tags);
		setLayout(form);
	}

	//--------------------------------------------------------------------------
	void MetaDataForm::reset()
	{
		date->setDate(QDate::currentDate());
		collection->setText("");
		category->setText("");
		title->setText("");
		tags->setText("");
	}

	//--------------------------------------------------------------------------
	void MetaDataForm::enable(bool enabled)
	{
		date->setEnabled(enabled);
		collection->setEnabled(enabled);
		category->setEnabled(enabled);
		title->setEnabled(enabled);
		tags->setEnabled(enabled);
	}

	//--------------------------------------------------------------------------
	void MetaDataForm::updateCollectionAutoCompletion()
	{
		qDebug() << "updating meta-form collection auto-complete";
		QString libRoot = settings->value(LIB_ROOT_KEY,
			DEFAULT_LIB_ROOT).toString();

		QDir dir(libRoot);
		QStringList dirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
		qDebug() << dirs;

		QCompleter* completer = new QCompleter(dirs, this);
		collection->setCompleter(completer);
	}

	//--------------------------------------------------------------------------
	void MetaDataForm::updateState()
	{
		bool dateIsValid = date->date().isValid();
		bool collectionIsEmpty = collection->text().isEmpty();
		bool categoryIsEmpty = category->text().isEmpty();
		bool titleIsEmpty = title->text().isEmpty();
		bool tagIsEmpty = tags->text().isEmpty();

		// Date, collection, and date are required
		bool formIsValid = dateIsValid && ( ! collectionIsEmpty)
			&& ( ! titleIsEmpty);

		bool formIsEmpty = collectionIsEmpty
			&& categoryIsEmpty && titleIsEmpty && tagIsEmpty;

		emit isValid(formIsValid);
		emit isEmpty(formIsEmpty);
	}

	//--------------------------------------------------------------------------
	void MetaDataForm::createFields()
	{
		date = new QDateEdit(QDate::currentDate(), this);
		date->setCalendarPopup(true);

		collection = new QLineEdit("", this);
		connect(collection, SIGNAL(textEdited(QString)),
			this, SLOT(updateState()));

		category = new QLineEdit("", this);
		connect(category, SIGNAL(textEdited(QString)),
			this, SLOT(updateState()));

		title = new QLineEdit("", this);
		connect(title, SIGNAL(textEdited(QString)),
			this, SLOT(updateState()));

		tags = new QLineEdit("", this);
		connect(tags, SIGNAL(textEdited(QString)),
			this, SLOT(updateState()));
	}

	void MetaDataForm::createFileSystemWatcher()
	{
		QString libRoot = settings->value(LIB_ROOT_KEY,
			DEFAULT_LIB_ROOT).toString();
		watcher = new QFileSystemWatcher;
		watcher->addPath(libRoot);
		connect(watcher, SIGNAL(directoryChanged(QString)),
			this, SLOT(updateCollectionAutoCompletion()));
	}
}
