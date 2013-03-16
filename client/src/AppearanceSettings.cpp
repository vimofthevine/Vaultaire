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

#include <QtWidgets>

#include "AppearanceSettings.h"
#include "SettingKeys.h"

namespace vaultaire
{
	static const QString ICON_THEME_HELP = "<p>Name of the icon theme to use</p>"
		"<p><b>Note:</b> application must be restarted to take affect</p>";

	/** Constructor */
	AppearanceSettings::AppearanceSettings(QWidget* parent)
		: QWidget(parent)
	{
		settings = new QSettings(this);

		// Icon theme field
		QString currentIconTheme = settings->value(ICON_THEME_KEY,
			DEFAULT_ICON_THEME).toString();
		iconTheme = new QLineEdit(currentIconTheme, this);
		iconTheme->setToolTip(ICON_THEME_HELP);
		connect(iconTheme, SIGNAL(textEdited(QString)),
			this, SLOT(iconThemeChanged(QString)));

		// Create form
		QFormLayout* form = new QFormLayout;
		setLayout(form);
		form->addRow(tr("Icon Theme"), iconTheme);

		// Disable fields if not writable
		iconTheme->setEnabled(settings->isWritable());
	}

	/** Store change to icon theme */
	void AppearanceSettings::iconThemeChanged(const QString& newTheme)
	{
		settings->setValue(ICON_THEME_KEY, newTheme);

		if ( ! newTheme.isEmpty())
		{
			QIcon::setThemeName(newTheme);
		}
	}

}

