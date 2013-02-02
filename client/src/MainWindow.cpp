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

#include "AppearanceSettings.h"
#include "LibraryBrowser.h"
#include "LibrarySettings.h"
#include "MainMenu.h"
#include "MainWindow.h"
#include "OcrSettings.h"
#include "ScanView.h"
#include "ScannerSettings.h"
#include "SearchView.h"
#include "SettingsDialog.h"

namespace vaultaire
{
	/** Constructor */
	MainWindow::MainWindow()
	{
		settingsDialog = new SettingsDialog(this);

		LibrarySettings* libSettings = new LibrarySettings;
		settingsDialog->add(tr("Library"), libSettings);

		ScannerSettings* scannerSettings = new ScannerSettings;
		settingsDialog->add(tr("Scanner"), scannerSettings);

		OcrSettings* ocrSettings = new OcrSettings;
		settingsDialog->add(tr("OCR"), ocrSettings);

		AppearanceSettings* appearanceSettings = new AppearanceSettings;
		settingsDialog->add(tr("Appearance"), appearanceSettings);

		scanView = new ScanView(this);
		browser = new LibraryBrowser(this);
		search = new SearchView(this);

		stack = new QStackedWidget(this);
		stack->addWidget(scanView);
		stack->addWidget(browser);
		stack->addWidget(search);

		mainMenu = new MainMenu(this);
		setMenuBar(mainMenu);
		connect(mainMenu, SIGNAL(scanNewFile()), this, SLOT(showScanForm()));
		connect(mainMenu, SIGNAL(browseFiles()), this, SLOT(showFileBrowser()));
		connect(mainMenu, SIGNAL(findFile()), this, SLOT(showSearchForm()));
		connect(mainMenu, SIGNAL(showAboutInfo()), this, SLOT(about()));
		connect(mainMenu, SIGNAL(quit()), this, SLOT(close()));
		connect(mainMenu, SIGNAL(editSettings()), settingsDialog, SLOT(show()));

		setWindowTitle(tr("Vaultaire"));
		setCentralWidget(stack);
		setWindowIcon(QIcon(":/vaultaire.svg"));

		readSettings();
	}

	/** Read settings */
	void MainWindow::readSettings()
	{
		QSettings settings(qApp->organizationName(),
			qApp->applicationName());
		QSize size = settings.value("MainWindowSize", QSize(600, 500)).toSize();
		QByteArray state = settings.value("MainWindowState", QByteArray()).toByteArray();
		restoreState(state);
		resize(size);
	}

	/** Write settings */
	void MainWindow::writeSettings()
	{
		QSettings settings(qApp->organizationName(),
			qApp->applicationName());
		settings.setValue("MainWindowSize", size());
		settings.setValue("MainWindowState", saveState());
	}

	/** Close event */
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

	/** Scan form */
	void MainWindow::showScanForm()
	{
		stack->setCurrentWidget(scanView);
	}

	/** File browser */
	void MainWindow::showFileBrowser()
	{
		stack->setCurrentWidget(browser);
	}

	/** Search form */
	void MainWindow::showSearchForm()
	{
		stack->setCurrentWidget(search);
	}

	/** About */
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

