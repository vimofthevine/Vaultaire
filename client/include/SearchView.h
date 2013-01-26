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

#ifndef SEARCHVIEW_H
#define SEARCHVIEW_H

#include <QList>
#include <QSplitter>

// Forward declarations
class QListWidget;
class QSettings;

namespace vaultaire
{
	// Forward declarations
	class ImageViewer;
	class LibraryEntry;
	class SearchEngine;
	class SearchForm;

	class SearchView : public QSplitter
	{
		Q_OBJECT

		public:
			/**
			 * Constructs a new search view.
			 *
			 * @param parent parent widget
			 */
			SearchView(QWidget* parent = 0);

			/**
			 * Destructor
			 */
			virtual ~SearchView();

		private slots:
			void searchFinished(const QStringList& results);
			void resultSelected(int row);

		private:
			void deleteFoundEntries();

			QSettings* settings;
			SearchEngine* engine;
			SearchForm* form;
			ImageViewer* viewer;
			QListWidget* resultList;
			QList<LibraryEntry*> libEntries;
	};

}

#endif // SEARCHVIEW_H
