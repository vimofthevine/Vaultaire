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

#include "ImageViewer.h"
#include "Library.h"
#include "ScanForm.h"
#include "SettingKeys.h"

namespace vaultaire
{
	ScanForm::ScanForm(QWidget* parent) : QSplitter(parent)
	{
		settings = new QSettings(QSettings::SystemScope,
			qApp->organizationName(),
			qApp->applicationName(),
			this);

		scanner = new Scanner(settings, this);
		connect(scanner, SIGNAL(started()), this, SLOT(scanStarted()));
		connect(scanner, SIGNAL(finished(Scanner::ScanResult)),
			this, SLOT(scanFinished(Scanner::ScanResult)));

		library = new Library(this);

		createButtons();
		createFields();
		updateCollectionAutoCompletion();
		createFSWatcher();

		QFormLayout* formLayout = new QFormLayout;
		formLayout->addRow(tr("Date"), date);
		formLayout->addRow(tr("Collection"), collection);
		formLayout->addRow(tr("Category"), category);
		formLayout->addRow(tr("Title"), title);
		formLayout->addRow(tr("Tags"), tags);

		QHBoxLayout* buttonsLayout = new QHBoxLayout;
		buttonsLayout->addWidget(scanPreviewButton);
		buttonsLayout->addWidget(cancelButton);
		buttonsLayout->addWidget(acceptScanButton);
		buttonsLayout->addWidget(rejectScanButton);
		buttonsLayout->addWidget(resetButton);

		QVBoxLayout* leftLayout = new QVBoxLayout;
		leftLayout->addLayout(formLayout);
		leftLayout->addLayout(buttonsLayout);

		QWidget* leftWidget = new QWidget(this);
		leftWidget->setLayout(leftLayout);

		imageViewer = new ImageViewer(this);
		imageViewer->clear();

		addWidget(leftWidget);
		addWidget(imageViewer);
		setStretchFactor(1, 2);
	}

	/* Scan button hit */
	void ScanForm::scan()
	{
		QString userTitle = title->text();
		qDebug() << "User title: " << userTitle;
		filename = "/tmp/" + Library::sanitize(userTitle);
		qDebug() << "Filename: " << filename;
		scanner->scan(filename);
	}

	/* Save button hit */
	void ScanForm::save()
	{
		QDate docDate = date->date();
		QString docColl = collection->text();
		QString docCat = category->text();
		QString docTitle = title->text();
		QString docTags = tags->text();

		qDebug() << "Saving " << filename
			<< " with date=" << docDate
			<< ", collection=" << docColl
			<< ", category=" << docCat
			<< ", title=" << docTitle
			<< ", & tags=" << docTags;

		if ( ! library->add(filename, docDate,
			docColl, docCat, docTitle, docTags))
		{
			QMessageBox::warning(this, "Save File Error",
				"An error occured adding the document to the library");
		}
		else
		{
			reset();
			imageViewer->clear();
		}

		enable(true);
		cancelButton->setEnabled(false);
		acceptScanButton->setEnabled(false);
		rejectScanButton->setEnabled(false);

		// Clean up the temporary file
		QFile file(filename);
		if (file.exists())
		{
			file.remove();
		}
	}

	/* Redo button hit */
	void ScanForm::redo()
	{
		qDebug() << "re-performing scan";
		acceptScanButton->setEnabled(false);
		rejectScanButton->setEnabled(false);
		imageViewer->clear();
		scan();
	}

	/* Reset button hit */
	void ScanForm::reset()
	{
		date->setDate(QDate::currentDate());
		collection->setText("");
		category->setText("");
		title->setText("");
		tags->setText("");
		updateButtons();
	}

	/* Cancel button hit */
	void ScanForm::cancel()
	{
		if (scanner->isScanning())
		{
			qDebug() << "User cancelled scan";
			scanner->cancel();
		}
		else
		{
			qDebug() << "User cancelled post-scan";
			imageViewer->clear();
			cancelButton->setEnabled(false);
			acceptScanButton->setEnabled(false);
			rejectScanButton->setEnabled(false);
			enable(true);
			updateButtons();
		}

		QFile file(filename);
		if (file.exists())
		{
			file.remove();
		}
	}

	/* Scan started */
	void ScanForm::scanStarted()
	{
		qDebug() << "scanning started...";
		enable(false);
		cancelButton->setEnabled(true);
	}

	/* Scan finished */
	void ScanForm::scanFinished(Scanner::ScanResult result)
	{
		qDebug() << "Scanning finished " << result;

		if (result == Scanner::ScanCancelled)
		{
			QMessageBox::information(this, "Scan Cancelled",
				"Scan has been cancelled");
			cancelButton->setEnabled(false);
			enable(true);
			updateButtons();
		}
		else if (result == Scanner::ScanComplete)
		{
			cancelButton->setEnabled(true);
			acceptScanButton->setEnabled(true);
			rejectScanButton->setEnabled(true);
			imageViewer->open(filename);
		}
		else
		{
			QMessageBox::warning(this, "Scan Error",
				"An error occured scanning the document");
			cancelButton->setEnabled(false);
			enable(true);
			updateButtons();
		}
	}

	/** Enable form */
	void ScanForm::enable(bool enabled)
	{
		date->setEnabled(enabled);
		collection->setEnabled(enabled);
		category->setEnabled(enabled);
		title->setEnabled(enabled);
		tags->setEnabled(enabled);

		if (enabled)
		{
			updateButtons();
		}
		else
		{
			scanPreviewButton->setEnabled(false);
			resetButton->setEnabled(false);
		}
	}

	void ScanForm::updateButtons()
	{
		bool dateIsValid = date->date().isValid();
		bool collectionIsEmpty = collection->text().isEmpty();
		bool categoryIsEmpty = category->text().isEmpty();
		bool titleIsEmpty = title->text().isEmpty();
		bool tagIsEmpty = tags->text().isEmpty();

		bool readyToScan = dateIsValid && ( ! collectionIsEmpty)
			&& ( ! titleIsEmpty);
		bool formIsEmpty = collectionIsEmpty
			&& categoryIsEmpty && titleIsEmpty && tagIsEmpty;

		scanPreviewButton->setEnabled(readyToScan);
		resetButton->setEnabled( ! formIsEmpty);
	}

	void ScanForm::createButtons()
	{
		scanPreviewButton = new QPushButton(tr("&Scan"), this);
		scanPreviewButton->setEnabled(false);
		connect(scanPreviewButton, SIGNAL(clicked()),
			this, SLOT(scan()));

		cancelButton = new QPushButton(tr("&Cancel"), this);
		cancelButton->setEnabled(false);
		connect(cancelButton, SIGNAL(clicked()),
			this, SLOT(cancel()));

		acceptScanButton = new QPushButton(tr("Sa&ve"), this);
		acceptScanButton->setEnabled(false);
		connect(acceptScanButton, SIGNAL(clicked()),
			this, SLOT(save()));

		rejectScanButton = new QPushButton(tr("R&e-scan"), this);
		rejectScanButton->setEnabled(false);
		connect(rejectScanButton, SIGNAL(clicked()),
			this, SLOT(redo()));

		resetButton = new QPushButton(tr("&Reset"), this);
		resetButton->setEnabled(false);
		connect(resetButton, SIGNAL(clicked()),
			this, SLOT(reset()));
	}

	void ScanForm::updateCollectionAutoCompletion()
	{
		qDebug() << "updating auto-complete";
		QString libRoot = settings->value(LIB_ROOT_KEY,
			DEFAULT_LIB_ROOT).toString();
		qDebug() << libRoot;

		QDir dir(libRoot);
		QStringList dirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
		qDebug() << dirs;

		QCompleter* completer = new QCompleter(dirs, this);
		collection->setCompleter(completer);
	}

	void ScanForm::createFields()
	{
		collection = new QLineEdit("", this);
		connect(collection, SIGNAL(textEdited(QString)),
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

		date = new QDateEdit(QDate::currentDate(), this);
		date->setCalendarPopup(true);
	}

	void ScanForm::createFSWatcher()
	{
		QString libRoot = settings->value(LIB_ROOT_KEY,
			DEFAULT_LIB_ROOT).toString();
		watcher = new QFileSystemWatcher;
		watcher->addPath(libRoot);
		connect(watcher, SIGNAL(directoryChanged(QString)),
			this, SLOT(updateCollectionAutoCompletion()));
	}

}

