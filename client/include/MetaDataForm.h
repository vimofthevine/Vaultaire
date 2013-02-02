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

#ifndef METADATAFORM_H
#define METADATAFORM_H

#include <QWidget>

// Forward declaration(s)
class QDate;
class QDateEdit;
class QFileSystemWatcher;
class QLineEdit;
class QSettings;

namespace vaultaire
{
	/**
	 * Widget that provides a form allowing users to
	 * specify or modify document meta-data.
	 *
	 * @author Kyle Treubig <kyle@vimofthevine.com>
	 */
	class MetaDataForm : public QWidget
	{
		Q_OBJECT

		public:
			/**
			 * Constructs a meta-data editing form widget.
			 *
			 * @param settings application settings
			 * @param parent   parent widget
			 */
			MetaDataForm(QSettings* settings, QWidget* parent = 0);

			/**
			 * Retrieves the user-specified document date.
			 *
			 * @return document date
			 */
			QDate date() const;

			/**
			 * Retrieves the user-specified library collection.
			 *
			 * @return library collection
			 */
			QString collection() const;

			/**
			 * Retrieves the user-specified document category.
			 *
			 * @return document category
			 */
			QString category() const;

			/**
			 * Retrieves the user-specified document title.
			 *
			 * @return document title
			 */
			QString title() const;

			/**
			 * Retrieves the user-specified document tags.
			 *
			 * @return document tags
			 */
			QString tags() const;

		public slots:
			/**
			 * Resets all fields of the form.
			 */
			void reset();

			/**
			 * Enables or disables all fields of the form.
			 *
			 * @param enabled true to enable fields
			 */
			void enable(bool enabled);

		private slots:
			/**
			 * Updates the available values in the collection field.
			 * Triggered as a response to a detected change in the
			 * document library root directory.
			 */
			void updateCollectionAutoCompletion();

			/**
			 * Updates the validity state of the form. If all required
			 * fields have been specified, the form is ready/valid.
			 */
			void updateState();

		signals:
			/**
			 * Indicates whether all required fields have been
			 * supplied.
			 *
			 * @param valid true if all required fields are supplied
			 */
			void isValid(bool valid);

			/**
			 * Indicates whether the form fields are all empty.
			 *
			 * @param empty true if all fields are empty
			 */
			void isEmpty(bool empty);

		private:
			// Meta-data fields
			QDateEdit* dateField;
			QLineEdit* collectionField;
			QLineEdit* categoryField;
			QLineEdit* titleField;
			QLineEdit* tagsField;

			// Application settings (for library root)
			QSettings* settings;

			// File-system watcher
			QFileSystemWatcher* watcher;

			/**
			 * Initializes all field widgets.
			 */
			void createFields();

			/**
			 * Installs a file system watcher to detect changes to
			 * the document library root directory. All immediate
			 * child directories in the root directory are used
			 * as available existing values for the library collection
			 * field.
			 */
			void createFileSystemWatcher();
	};
}

#endif // METADATAFORM_H
