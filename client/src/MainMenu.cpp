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

#include <QtGui>

#include "MainMenu.h"

namespace vaultaire
{
	/** Constructor */
	MainMenu::MainMenu(QWidget* parent) : QMenuBar(parent)
	{
		createActions();
		createMenus();
	}

	/** Create actions */
	void MainMenu::createActions()
	{
		// Scan new file
		scanFileAction = new QAction(tr("&New"), this);
		scanFileAction->setIcon(QIcon::fromTheme("scanner"));
		scanFileAction->setShortcut(QKeySequence::New);
		scanFileAction->setStatusTip("Scan a new file into the library");
		connect(scanFileAction, SIGNAL(triggered()), this, SIGNAL(scanNewFile()));

		// Browse files
		browseFilesAction = new QAction(tr("&Browse"), this);
		browseFilesAction->setIcon(QIcon::fromTheme("system-file-manager"));
		browseFilesAction->setShortcut(QKeySequence::Open);
		browseFilesAction->setStatusTip("Browse through files in the library");
		connect(browseFilesAction, SIGNAL(triggered()), this, SIGNAL(browseFiles()));

		// Find file
		findFileAction = new QAction(tr("&Find"), this);
		findFileAction->setIcon(QIcon::fromTheme("edit-find"));
		findFileAction->setShortcut(QKeySequence::Find);
		findFileAction->setStatusTip("Find a file in the library");
		connect(findFileAction, SIGNAL(triggered()), this, SIGNAL(findFile()));

		// Quit
		quitAction = new QAction(tr("E&xit"), this);
		quitAction->setIcon(QIcon::fromTheme("application-exit"));
		quitAction->setShortcut(tr("Ctrl+Q"));
		quitAction->setStatusTip(tr("Exit the application"));
		connect(quitAction, SIGNAL(triggered()), this, SIGNAL(quit()));

		// Settings
		settingsAction = new QAction(tr("&Settings"), this);
		settingsAction->setIcon(QIcon::fromTheme("preferences-system"));
		settingsAction->setShortcut(QKeySequence::Preferences);
		settingsAction->setStatusTip(tr("Edit application settings"));
		connect(settingsAction, SIGNAL(triggered()), this, SIGNAL(editSettings()));

		// About
		aboutAction = new QAction(tr("&About"), this);
		aboutAction->setIcon(QIcon::fromTheme("help-about"));
		aboutAction->setStatusTip(tr("Show the about box"));
		connect(aboutAction, SIGNAL(triggered()), this, SIGNAL(showAboutInfo()));
	}

	/** Create menus */
	void MainMenu::createMenus()
	{
		fileMenu = addMenu(tr("&File"));
		fileMenu->addAction(scanFileAction);
		fileMenu->addAction(browseFilesAction);
		fileMenu->addAction(findFileAction);
		fileMenu->addSeparator();
		fileMenu->addAction(quitAction);

		editMenu = addMenu(tr("&Edit"));
		editMenu->addAction(settingsAction);

		helpMenu = addMenu("&Help");
		helpMenu->addAction(aboutAction);
	}

}

