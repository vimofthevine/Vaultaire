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

#ifndef LIBRARYSETTINGS_H
#define LIBRARYSETTINGS_H

#include <QWidget>

// Forward declaration(s)
class QLineEdit;

namespace vaultaire
{
	// Forward declaration(s)
	class Settings;

	/**
	 * Library settings widget.
	 *
	 * @author Kyle Treubig <kyle@vimofthevine.com>
	 */
	class LibrarySettings : public QWidget
	{
		Q_OBJECT

		public:
			/**
			 * Constructs a library settings widget.
			 *
			 * @param settings application settings
			 * @param parent   parent widget
			 */
			LibrarySettings(Settings* settings, QWidget* parent = 0);

		private slots:
			/**
			 * Saves the new library root setting.
			 *
			 * @param newLibRoot new library root value
			 */
			void libRootChanged(const QString& newLibRoot);

			/**
			 * Reload setting values if the system-vs-user
			 * setting has changed.
			 *
			 * @param key setting key of the modified setting
			 */
			void reload(const QString& key);

		private:
			// Settings
			Settings* settings;

			// Library root directory field
			QLineEdit* libRoot;
	};
}

#endif
