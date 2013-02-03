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
#include "Settings.h"

namespace vaultaire
{
	//--------------------------------------------------------------------------
	MetaDataForm::MetaDataForm(QWidget* parent)
		: QWidget(parent), settings(new Settings(this))
	{
		createFields();
		updateCollectionAutoCompletion();
		createFileSystemWatcher();

		QFormLayout* form = new QFormLayout;
		form->addRow(tr("Date"), dateField);
		form->addRow(tr("Collection"), collectionField);
		form->addRow(tr("Category"), categoryField);
		form->addRow(tr("Title"), titleField);
		form->addRow(tr("Tags"), tagsField);
		setLayout(form);
	}

	//--------------------------------------------------------------------------
	QDate MetaDataForm::date() const
	{
		return dateField->date();
	}

	//--------------------------------------------------------------------------
	QString MetaDataForm::collection() const
	{
		return collectionField->text();
	}

	//--------------------------------------------------------------------------
	QString MetaDataForm::category() const
	{
		return categoryField->text();
	}

	//--------------------------------------------------------------------------
	QString MetaDataForm::title() const
	{
		return titleField->text();
	}

	//--------------------------------------------------------------------------
	QString MetaDataForm::tags() const
	{
		return tagsField->text();
	}

	//--------------------------------------------------------------------------
	void MetaDataForm::reset()
	{
		dateField->setDate(QDate::currentDate());
		collectionField->setText("");
		categoryField->setText("");
		titleField->setText("");
		tagsField->setText("");
		updateState();
	}

	//--------------------------------------------------------------------------
	void MetaDataForm::enable(bool enabled)
	{
		dateField->setEnabled(enabled);
		collectionField->setEnabled(enabled);
		categoryField->setEnabled(enabled);
		titleField->setEnabled(enabled);
		tagsField->setEnabled(enabled);
		updateState();
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
		collectionField->setCompleter(completer);
	}

	//--------------------------------------------------------------------------
	void MetaDataForm::updateState()
	{
		bool dateIsValid = dateField->date().isValid();
		bool collectionIsEmpty = collectionField->text().isEmpty();
		bool categoryIsEmpty = categoryField->text().isEmpty();
		bool titleIsEmpty = titleField->text().isEmpty();
		bool tagIsEmpty = tagsField->text().isEmpty();

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
		dateField = new QDateEdit(QDate::currentDate(), this);
		dateField->setCalendarPopup(true);

		collectionField = new QLineEdit("", this);
		connect(collectionField, SIGNAL(textEdited(QString)),
			this, SLOT(updateState()));

		categoryField = new QLineEdit("", this);
		connect(categoryField, SIGNAL(textEdited(QString)),
			this, SLOT(updateState()));

		titleField = new QLineEdit("", this);
		connect(titleField, SIGNAL(textEdited(QString)),
			this, SLOT(updateState()));

		tagsField = new QLineEdit("", this);
		connect(tagsField, SIGNAL(textEdited(QString)),
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
