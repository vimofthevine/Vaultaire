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

#ifndef SCANFORM_H
#define SCANFORM_H

#include <QSplitter>

#include "Scanner.h"

// Forward declarations
class QDateEdit;
class QFileSystemWatcher;
class QLineEdit;
class QPushButton;
class QSettings;

namespace vaultaire
{
	// Forward declarations
	class ImageViewer;
	class Library;

	class ScanForm : public QSplitter
	{
		Q_OBJECT

		public:
			/**
			 * Constructs a new scan form widget.
			 *
			 * @param parent parent widget
			 */
			ScanForm(QWidget* parent = 0);

		private slots:
			void updateButtons();
			void reset();
			void scan();
			void save();
			void redo();
			void cancel();
			void updateCollectionAutoCompletion();
			void scanStarted();
			void scanFinished(Scanner::ScanResult result);

		private:
			void createButtons();
			void createFields();
			void createFSWatcher();
			void enable(bool enabled);

			QSettings* settings;
			QFileSystemWatcher* watcher;

			QLineEdit* collection;
			QLineEdit* category;
			QLineEdit* title;
			QLineEdit* tags;
			QDateEdit* date;

			QPushButton* scanPreviewButton;
			QPushButton* cancelButton;
			QPushButton* acceptScanButton;
			QPushButton* rejectScanButton;
			QPushButton* resetButton;

			ImageViewer* imageViewer;
			Scanner* scanner;
			Library* library;

			// Current file name
			QString filename;
	};
}

#endif
