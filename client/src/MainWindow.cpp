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

#include <QtGui>

#include "LibraryBrowser.h"
#include "MainMenu.h"
#include "MainWindow.h"
#include "ScanView.h"
#include "SearchEngine.h"
#include "SearchView.h"
#include "Settings.h"
#include "SettingsDialog.h"
#include "StatusBar.h"

namespace vaultaire
{
	//--------------------------------------------------------------------------
	MainWindow::MainWindow() :
		settings(new Settings(this)),
		scanner(new Scanner(this)),
		engine(new SearchEngine(this)),
		mainMenu(new MainMenu(this)),
		status(new StatusBar(this)),
		stack(new QStackedWidget(this)),
		settingsDialog(new SettingsDialog(this))
	{
		// Set up window widgets
		setWindowTitle(tr("Vaultaire"));
		setWindowIcon(QIcon(":/vaultaire.svg"));
		setMenuBar(mainMenu);
		setStatusBar(status);
		setCentralWidget(stack);

		// Connect signals to show scanning in-progress in status bar
		connect(scanner, SIGNAL(started()),
			status, SLOT(startBusyIndicator()));
		connect(scanner, SIGNAL(started()),
			this, SLOT(showScanningMessage()));
		connect(scanner, SIGNAL(finished(Scanner::ScanResult)),
			status, SLOT(stopBusyIndicator()));
		connect(scanner, SIGNAL(finished(Scanner::ScanResult)),
			status, SLOT(clearMessage()));

		// Connect signals to show search in-progress in status bar
		connect(engine, SIGNAL(started()),
			status, SLOT(startBusyIndicator()));
		connect(engine, SIGNAL(finished(QStringList)),
			status, SLOT(stopBusyIndicator()));

		// Create application widgets
		scanView = new ScanView(scanner, this);
		browser = new LibraryBrowser(this);
		search = new SearchView(engine, this);
		stack->addWidget(scanView);
		stack->addWidget(browser);
		stack->addWidget(search);

		// Connect menu signals
		connect(mainMenu, SIGNAL(scanNewFile()), this, SLOT(showScanForm()));
		connect(mainMenu, SIGNAL(browseFiles()), this, SLOT(showFileBrowser()));
		connect(mainMenu, SIGNAL(findFile()), this, SLOT(showSearchForm()));
		connect(mainMenu, SIGNAL(showAboutInfo()), this, SLOT(about()));
		connect(mainMenu, SIGNAL(quit()), this, SLOT(close()));
		connect(mainMenu, SIGNAL(editSettings()), settingsDialog, SLOT(show()));

		readSettings();
	}

	//--------------------------------------------------------------------------
	void MainWindow::showScanningMessage()
	{
		status->showMessage(tr("Scanning..."));
	}

	//--------------------------------------------------------------------------
	void MainWindow::readSettings()
	{
		QSettings settings;
		QSize size = settings.value("MainWindowSize", QSize(600, 500)).toSize();
		QByteArray state = settings.value("MainWindowState", QByteArray()).toByteArray();
		restoreState(state);
		resize(size);
	}

	//--------------------------------------------------------------------------
	void MainWindow::writeSettings()
	{
		QSettings settings;
		settings.setValue("MainWindowSize", size());
		settings.setValue("MainWindowState", saveState());
	}

	//--------------------------------------------------------------------------
	void MainWindow::closeEvent(QCloseEvent* event)
	{
		int result = QMessageBox::warning(this, tr("Close?"),
			tr("Close Vaultaire?"), QMessageBox::Yes | QMessageBox::Cancel);

		if (result == QMessageBox::Yes)
		{
			writeSettings();
			event->accept();
		}
		else
		{
			event->ignore();
		}
	}

	//--------------------------------------------------------------------------
	void MainWindow::showScanForm()
	{
		stack->setCurrentWidget(scanView);
	}

	//--------------------------------------------------------------------------
	void MainWindow::showFileBrowser()
	{
		stack->setCurrentWidget(browser);
	}

	//--------------------------------------------------------------------------
	void MainWindow::showSearchForm()
	{
		stack->setCurrentWidget(search);
	}

	//--------------------------------------------------------------------------
	void MainWindow::about()
	{
		QMessageBox::about(this, tr("About"),
			tr(QString("<dl>"
				"<dt>Title</dt><dd>%1</dd>"
				"<dt>Version</dt><dd>%2</dd>"
				"<dt>Copyright</dt><dd>Copyright (C) 2013</dd>"
				"<dt>License</dt><dd>Apache License 2.0</dd>"
				"<dt>Authors</dt><dd>Kyle Treubig</dd>"
				"<dt>URL</dt><dd><a href=\"http://%3\">%3</a></dd>"
				"</dl>")
				.arg(qApp->applicationName())
				.arg(qApp->applicationVersion())
				.arg(qApp->organizationDomain())
				.toUtf8()
			));
	}
}

