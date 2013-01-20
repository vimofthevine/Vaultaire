/*
 * Copyright 2012 Kyle Treubig
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

#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMenuBar>

namespace vaultaire
{
	/**
	 * Main menu for the application.
	 *
	 * @author Kyle Treubig <kyle@vimofthevine.com>
	 */
	class MainMenu : public QMenuBar
	{
		Q_OBJECT

		public:
			MainMenu(QWidget* parent = 0);

		signals:
			/** Scan new file */
			void scanNewFile();
			/** Browse files */
			void browseFiles();
			/** Find file */
			void findFile();
			/** Quit application */
			void quit();
			/** Edit settings */
			void editSettings();
			/** About */
			void showAboutInfo();

		private:
			/** Creates all action instances */
			void createActions();
			/** Creates all menus */
			void createMenus();

			QMenu* fileMenu;
			QMenu* editMenu;
			QMenu* helpMenu;

			QAction* scanFileAction;
			QAction* browseFilesAction;
			QAction* findFileAction;
			QAction* quitAction;
			QAction* settingsAction;
			QAction* aboutAction;
	};
}

#endif
