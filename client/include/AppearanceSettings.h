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

#ifndef APPEARANCESETTINGS_H
#define APPEARANCESETTINGS_H

#include <QWidget>

class QLineEdit;
class QSettings;

namespace vaultaire
{
	/**
	 * Appearance settings panel.
	 *
	 * @author Kyle Treubig <kyle@vimofthevine.com>
	 */
	class AppearanceSettings : public QWidget
	{
		Q_OBJECT

		public:
			/**
			 * Constructs a new appearance settings panel.
			 *
			 * @param parent parent widget
			 */
			AppearanceSettings(QWidget* parent = 0);

		private slots:
			void iconThemeChanged(const QString& newTheme);

		private:
			/** User settings */
			QSettings* settings;
			/** Icon theme field */
			QLineEdit* iconTheme;
	};
}

#endif // APPEARANCESETTINGS_H
