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

// Forward declaration(s)
class QSettings;
class QStackedWidget;

namespace vaultaire
{
	// Forward declaration(s)
	class LibraryBrowser;
	class MainMenu;
	class Scanner;
	class ScanView;
	class SearchEngine;
	class SearchView;
	class Settings;
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
			/**
			 * Constructs the main application window.
			 */
			MainWindow();

		protected:
			/**
			 * Prompts the user to finalize any pending
			 * operations before closing the application.
			 *
			 * @param event window close event
			 */
			void closeEvent(QCloseEvent* event);

		private slots:
			/**
			 * Displays the scan-document widget.
			 */
			void showScanForm();

			/**
			 * Displays the browse-library widget.
			 */
			void showFileBrowser();

			/**
			 * Displays the search-library widget.
			 */
			void showSearchForm();

			/**
			 * Displays the about-application dialog.
			 */
			void about();

			/**
			 * Displays a message in the status bar
			 * indicating that a scan is in progress.
			 */
			void showScanningMessage();

		private:
			// Application settings
			Settings* settings;
			// Scanner device model
			Scanner* scanner;
			// Search engine
			SearchEngine* engine;

			// Menu widget
			MainMenu* mainMenu;
			// Status bar widget
			StatusBar* status;
			// Widget stack
			QStackedWidget* stack;

			// Settings dialog
			SettingsDialog* settingsDialog;
			// Scan-document widget
			ScanView* scanView;
			// Search-library widget
			LibraryBrowser* browser;
			// Search-library widget
			SearchView* search;

			/**
			 * Store window settings such as size, geometry, etc.
			 */
			void writeSettings();

			/**
			 * Restore saved window settings.
			 */
			void readSettings();
	};
}

#endif
