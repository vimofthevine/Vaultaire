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

#ifndef SEARCHFORM_H
#define SEARCHFORM_H

#include <QWidget>

// Forward declarations
class QCheckBox;
class QComboBox;
class QDateEdit;
class QFileSystemWatcher;
class QLineEdit;
class QPushButton;

namespace vaultaire
{
	// Forward declarations
	class SearchEngine;
	class Settings;

	class SearchForm : public QWidget
	{
		Q_OBJECT

		public:
			/**
			 * Constructs a new search form widget.
			 *
			 * @param engine search engine
			 * @param parent parent widget
			 */
			SearchForm(SearchEngine* engine, QWidget* parent = 0);

		private slots:
			void reset();
			void search();
			void updateButtons();
			void updateCollectionAutoCompletion();
			void searchStarted();
			void searchFailed();
			void searchFinished(const QStringList& results);

		private:
			void createButtons();
			void createFields();
			void createFSWatcher();
			void enableFields(bool enabled);

			// Search parameters
			QComboBox* year;
			QComboBox* month;
			QComboBox* date;
			QComboBox* collection;
			QComboBox* field;
			QLineEdit* parameter;
			QCheckBox* caseSensitivity;

			// Buttons
			QPushButton* searchButton;
			QPushButton* resetButton;
			QPushButton* cancelButton;

			// Settings
			Settings* settings;
			// Library root watcher
			QFileSystemWatcher* watcher;
			// Search engine
			SearchEngine* engine;
	};
}

#endif
