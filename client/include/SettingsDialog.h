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

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

// Forward declarations
class QListWidget;
class QStackedWidget;

namespace vaultaire
{
	/**
	 * Application settings and preferences dialog.
	 *
	 * @author Kyle Treubig <kyle@vimofthevine.com>
	 */
	class SettingsDialog : public QDialog
	{
		Q_OBJECT

		public:
			/**
			 * Constructs a new settings dialog.
			 */
			SettingsDialog(QWidget* parent = 0);

			/**
			 * Adds a new settings page to the
			 * settings dialog.
			 *
			 * @param label settings category label
			 * @param page  settings widget
			 */
			void add(const QString& label, QWidget* page);

		private:
			QListWidget* selection;
			QStackedWidget* pages;
	};
}

#endif
