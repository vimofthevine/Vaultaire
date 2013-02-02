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

#ifndef SCANVIEW_H
#define SCANVIEW_H

#include <QSplitter>

#include "Scanner.h"

// Forward declaration(s)
class QPushButton;
class QSettings;

namespace vaultaire
{
	// Forward declaration(s)
	class ImageViewer;
	class Library;
	class MetaDataForm;

	/**
	 * Widget that encompasses everything required for a scan-and-import
	 * operation, including the meta-data form and image-viewer preview.
	 *
	 * @author Kyle Treubig <kyle@vimofthevine.com>
	 */
	class ScanView : public QSplitter
	{
		Q_OBJECT

		public:
			/**
			 * Constructs a scan-document view widget.
			 *
			 * @param scanner scanner device
			 * @param parent  parent widget
			 */
			ScanView(Scanner* scanner, QWidget* parent = 0);

		private slots:
			/**
			 * Enable or disable the reset button
			 *
			 * @param empty true if the meta-data form is empty
			 */
			void formIsEmpty(bool empty);

			/**
			 * Begin scanning.
			 */
			void scan();

			/**
			 * Save the scanned document.
			 */
			void save();

			/**
			 * Re-scan the document.
			 */
			void redo();

			/**
			 * Cancel the current scan operation.
			 */
			void cancel();

			/**
			 * Once scanning has started, disable the form and buttons.
			 */
			void scanStarted();

			/**
			 * Once scanning has finished, update preview pane with
			 * scanned document, or display error popup if an error
			 * occurred.
			 *
			 * @param result scan operation result
			 */
			void scanFinished(Scanner::ScanResult result);

		private:
			/**
			 * Enumeration for all possible states of the scan operation.
			 */
			enum ScanState {
				WaitingForInput,
				Scanning,
				WaitingForAccept
			};

			// Action buttons
			QPushButton* scanPreviewButton;
			QPushButton* cancelButton;
			QPushButton* acceptScanButton;
			QPushButton* rejectScanButton;
			QPushButton* resetButton;

			// Application settings
			QSettings* settings;
			// Scanner device
			Scanner* scanner;
			// Document library
			Library* library;
			// Meta-data form widget
			MetaDataForm* metaForm;
			// Image viewer widget
			ImageViewer* imageViewer;

			// Current state
			ScanState state;
			// Current file name
			QString filename;

			/**
			 * Initializes all action buttons.
			 */
			void createButtons();

			/**
			 * Updates the buttons and meta-data form according
			 * to the current state.
			 */
			void update();
	};
}

#endif
