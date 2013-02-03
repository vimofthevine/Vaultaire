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

#ifndef GENERALSETTINGS_H
#define GENERALSETTINGS_H

#include <QWidget>

// Forward declaration(s)
class QCheckBox;

namespace vaultaire
{
	// Forward declaration(s)
	class Settings;

	/**
	 * General settings widget.
	 *
	 * @author Kyle Treubig <kyle@vimofthevine.com>
	 */
	class GeneralSettings : public QWidget
	{
		Q_OBJECT

		public:
			/**
			 * Constructs a general settings widget.
			 *
			 * @param settings application settings
			 * @param parent   parent widget
			 */
			GeneralSettings(Settings* settings, QWidget* parent = 0);

		private slots:
			/**
			 * Saves the system-vs-user settings option.
			 *
			 * @param useSystem new system-vs-user value
			 */
			void useSystemChanged(bool useSystem);

		private:
			// Settings
			Settings* settings;

			// Use system-wide settings field
			QCheckBox* useSystemSettings;
	};
}

#endif // GENERALSETTINGS_H
