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
class QSettings;
class QStackedWidget;

namespace vaultaire
{
	// Forward declarations
	class LibraryBrowser;
	class MainMenu;
	class Scanner;
	class ScanView;
	class SearchEngine;
	class SearchView;
	class SettingsDialog;
	class StatusBar;

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
			void showScanningMessage();

		private:
			void writeSettings();
			void readSettings();

			QSettings* settings;
			Scanner* scanner;
			SearchEngine* engine;
			MainMenu* mainMenu;
			StatusBar* status;
			SettingsDialog* settingsDialog;
			QStackedWidget* stack;
			ScanView* scanView;
			LibraryBrowser* browser;
			SearchView* search;
	};
}

#endif
