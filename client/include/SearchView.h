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

// Forward declaration(s)
class QListWidget;

namespace vaultaire
{
	// Forward declaration(s)
	class ImageViewer;
	class LibraryEntry;
	class SearchEngine;
	class SearchForm;
	class Settings;

	/**
	 * Widget that encompasses everything required for a library search
	 * operation, including the meta-data form, result list, and image
	 * viewer.
	 *
	 * @author Kyle Treubig <kyle@vimofthevine.com>
	 */
	class SearchView : public QSplitter
	{
		Q_OBJECT

		public:
			/**
			 * Constructs a search view widget.
			 *
			 * @param engine search engine
			 * @param parent parent widget
			 */
			SearchView(SearchEngine* engine, QWidget* parent = 0);

			/**
			 * Free up memory for any search results.
			 */
			~SearchView();

		private slots:
			/**
			 * Once search has finished, update results list with
			 * found results.
			 *
			 * @param results search results
			 */
			void searchFinished(const QStringList& results);

			/**
			 * Displays the image selected from the search results
			 * list.
			 *
			 * @param row row index of the selected entry
			 */
			void resultSelected(int row);

		private:
			// Application settings
			Settings* settings;
			// Search engine
			SearchEngine* engine;
			// Search-parameters form widget
			SearchForm* form;
			// Search results list widget
			QListWidget* resultList;
			// Image viewer widget
			ImageViewer* viewer;

			// Search results list
			QList<LibraryEntry*> libEntries;

			/**
			 * Clears all result entries from the results list.
			 */
			void deleteFoundEntries();
	};

}

#endif // SEARCHVIEW_H
