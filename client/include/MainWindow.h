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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Forward declarations
class QStackedWidget;

namespace vaultaire
{
	// Forward declarations
	class LibraryBrowser;
	class MainMenu;
	class ScanForm;
	class SearchView;
	class SettingsDialog;

	/**
	 * The application's main, primary window.
	 *
	 * @author Kyle Treubig <kyle@vimofthevine.com>
	 */
	class MainWindow : public QMainWindow
	{
		Q_OBJECT

		public:
			MainWindow();

		protected:
			void closeEvent(QCloseEvent* event);

		private slots:
			void showScanForm();
			void showFileBrowser();
			void showSearchForm();
			void about();

		private:
			void writeSettings();
			void readSettings();

			MainMenu* mainMenu;
			SettingsDialog* settingsDialog;
			QStackedWidget* stack;
			ScanForm* scanForm;
			LibraryBrowser* browser;
			SearchView* search;
	};
}

#endif
