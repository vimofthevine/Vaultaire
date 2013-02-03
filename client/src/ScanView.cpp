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

#include "ImageViewer.h"
#include "Library.h"
#include "MetaDataForm.h"
#include "Scanner.h"
#include "ScanView.h"
#include "SettingKeys.h"

namespace vaultaire
{
	//--------------------------------------------------------------------------
	ScanView::ScanView(Scanner* scanner, QWidget* parent) :
		QSplitter(parent),
		scanner(scanner),
		library(new Library(this)),
		metaForm(new MetaDataForm(this)),
		imageViewer(new ImageViewer(this))
	{
		// Connect signals for scan progress
		connect(scanner, SIGNAL(started()), this, SLOT(scanStarted()));
		connect(scanner, SIGNAL(finished(Scanner::ScanResult)),
			this, SLOT(scanFinished(Scanner::ScanResult)));

		createButtons();
		QHBoxLayout* buttonsLayout = new QHBoxLayout;
		buttonsLayout->addWidget(scanPreviewButton);
		buttonsLayout->addWidget(cancelButton);
		buttonsLayout->addWidget(acceptScanButton);
		buttonsLayout->addWidget(rejectScanButton);
		buttonsLayout->addWidget(resetButton);

		// Connect signals for form states
		connect(metaForm, SIGNAL(isEmpty(bool)), this, SLOT(formIsEmpty(bool)));
		connect(metaForm, SIGNAL(isValid(bool)),
			scanPreviewButton, SLOT(setEnabled(bool)));

		QVBoxLayout* leftLayout = new QVBoxLayout;
		leftLayout->addWidget(metaForm);
		leftLayout->addLayout(buttonsLayout);

		QWidget* leftWidget = new QWidget(this);
		leftWidget->setLayout(leftLayout);

		addWidget(leftWidget);
		addWidget(imageViewer);
		setStretchFactor(1, 2); // Give more weight to the viewer
	}

	//--------------------------------------------------------------------------
	void ScanView::formIsEmpty(bool empty)
	{
		// Can't reset if already empty
		resetButton->setEnabled( ! empty);
	}

	//--------------------------------------------------------------------------
	void ScanView::scan()
	{
		QString title = metaForm->title();
		qDebug() << "User title: " << title;
		filename = "/tmp/" + Library::sanitize(title);
		qDebug() << "Filename: " << filename;
		scanner->scan(filename);
	}

	//--------------------------------------------------------------------------
	void ScanView::save()
	{
		// Get meta-data from form
		QDate date = metaForm->date();
		QString collection = metaForm->collection();
		QString category = metaForm->category();
		QString title = metaForm->title();
		QString tags = metaForm->tags();

		qDebug() << "Saving " << filename
			<< " with date=" << date
			<< ", collection=" << collection
			<< ", category=" << category
			<< ", title=" << title
			<< ", & tags=" << tags;

		if ( ! library->add(filename, date, collection,
			category, title, tags))
		{
			QMessageBox::warning(this, "Save File Error",
				"An error occured adding the document to the library");
			state = WaitingForAccept;
		}
		else
		{
			state = WaitingForInput;
			metaForm->reset();
			imageViewer->clear();

			// Clean up the temporary file (if it exists)
			QFile file(filename);
			if (file.exists())
			{
				file.remove();
			}
		}

		update();
	}

	//--------------------------------------------------------------------------
	void ScanView::redo()
	{
		qDebug() << "re-performing scan";
		imageViewer->clear();
		scan();
	}

	//--------------------------------------------------------------------------
	void ScanView::cancel()
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
			state = WaitingForInput;

			// Clean up the temporary file (if it exists)
			QFile file(filename);
			if (file.exists())
			{
				file.remove();
			}

			update();
		}
	}

	//--------------------------------------------------------------------------
	void ScanView::scanStarted()
	{
		qDebug() << "scanning started...";
		state = Scanning;
		update();
	}

	//--------------------------------------------------------------------------
	void ScanView::scanFinished(Scanner::ScanResult result)
	{
		qDebug() << "Scanning finished " << result;

		if (result == Scanner::ScanCancelled)
		{
			QMessageBox::information(this, "Scan Cancelled",
				"Scan has been cancelled");
			state = WaitingForInput;
		}
		else if (result == Scanner::ScanComplete)
		{
			state = WaitingForAccept;
			imageViewer->open(filename);
		}
		else
		{
			QMessageBox::warning(this, "Scan Error",
				"An error occured scanning the document");
			state = WaitingForInput;
		}

		update();
	}

	//--------------------------------------------------------------------------
	void ScanView::createButtons()
	{
		scanPreviewButton = new QPushButton(QIcon::fromTheme("scanner"),
			tr("&Scan"), this);
		scanPreviewButton->setEnabled(false);
		connect(scanPreviewButton, SIGNAL(clicked()),
			this, SLOT(scan()));

		cancelButton = new QPushButton(QIcon::fromTheme("edit-delete"),
			tr("&Cancel"), this);
		cancelButton->setEnabled(false);
		connect(cancelButton, SIGNAL(clicked()),
			this, SLOT(cancel()));

		acceptScanButton = new QPushButton(QIcon::fromTheme("document-save"),
			tr("Sa&ve"), this);
		acceptScanButton->setEnabled(false);
		connect(acceptScanButton, SIGNAL(clicked()),
			this, SLOT(save()));

		rejectScanButton = new QPushButton(QIcon::fromTheme("edit-redo"),
			tr("R&e-scan"), this);
		rejectScanButton->setEnabled(false);
		connect(rejectScanButton, SIGNAL(clicked()),
			this, SLOT(redo()));

		resetButton = new QPushButton(QIcon::fromTheme("edit-clear"),
			tr("&Reset"), this);
		resetButton->setEnabled(false);
		connect(resetButton, SIGNAL(clicked()),
			metaForm, SLOT(reset()));
	}

	//--------------------------------------------------------------------------
	void ScanView::update()
	{
		switch (state)
		{
			case WaitingForInput:
				// Reset buttons first
				scanPreviewButton->setEnabled(false);
				resetButton->setEnabled(false);
				// Then form will re-enable them if needed
				metaForm->enable(true);

				cancelButton->setEnabled(false);
				acceptScanButton->setEnabled(false);
				rejectScanButton->setEnabled(false);
				break;

			case Scanning:
				// Reset form first
				metaForm->enable(false);
				// Then make sure buttons are disabled
				scanPreviewButton->setEnabled(false);
				resetButton->setEnabled(false);

				cancelButton->setEnabled(true);
				acceptScanButton->setEnabled(false);
				rejectScanButton->setEnabled(false);
				break;

			case WaitingForAccept:
				// Reset form first
				metaForm->enable(false);
				// Then make sure buttons are disabled
				scanPreviewButton->setEnabled(false);
				resetButton->setEnabled(false);

				cancelButton->setEnabled(true);
				acceptScanButton->setEnabled(true);
				rejectScanButton->setEnabled(true);
				break;
		}
	}
}

