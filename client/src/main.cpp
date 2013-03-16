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

#include <QApplication>
#include <QIcon>
#include <QSettings>

#include "MainWindow.h"
#include "SettingKeys.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	app.setOrganizationName("vimofthevine");
	app.setOrganizationDomain("vautlaire.vimofthevine.com");
	app.setApplicationName("Vaultaire");
	app.setApplicationVersion("1.1rc1");

	// Do this here before any graphical elements have been created
	QSettings settings;
	QString iconTheme = settings.value(vaultaire::ICON_THEME_KEY,
		vaultaire::DEFAULT_ICON_THEME).toString();
	if ( ! iconTheme.isEmpty())
	{
		QIcon::setThemeName(iconTheme);
	}

	vaultaire::MainWindow* mainWindow = new vaultaire::MainWindow();
	mainWindow->show();

	return app.exec();
}
