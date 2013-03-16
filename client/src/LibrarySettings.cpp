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

#include "LibrarySettings.h"
#include "SettingKeys.h"
#include "Settings.h"

namespace vaultaire
{
	// Field help text(s)
	static const QString& LIB_ROOT_HELP = "Root directory in which all library documents are found";

	//--------------------------------------------------------------------------
	LibrarySettings::LibrarySettings(Settings* settings, QWidget* parent) :
		QWidget(parent), settings(settings)
	{
		connect(settings, SIGNAL(settingModified(QString)),
			this, SLOT(reload(QString)));

		// Library root directory field
		libRoot = new QLineEdit(this);
		libRoot->setToolTip(LIB_ROOT_HELP);
		connect(libRoot, SIGNAL(textEdited(QString)),
			this, SLOT(libRootChanged(QString)));

		// Create form
		QFormLayout* form = new QFormLayout;
		setLayout(form);
		form->addRow(tr("Library Root"), libRoot);

		// Initialize field
		reload(SYSTEM_SETTINGS_KEY);
	}

	//--------------------------------------------------------------------------
	void LibrarySettings::libRootChanged(const QString& newLibRoot)
	{
		settings->setValue(LIB_ROOT_KEY, newLibRoot);
	}

	//--------------------------------------------------------------------------
	void LibrarySettings::reload(const QString& key)
	{
		if (key == SYSTEM_SETTINGS_KEY)
		{
			QString currentLibRoot = settings->value(LIB_ROOT_KEY,
				DEFAULT_LIB_ROOT).toString();
			libRoot->setText(currentLibRoot);

			// Disable fields if not writable (i.e., no permission
			// to modify system-level settings
			libRoot->setEnabled(settings->isWritable());
		}
	}
}

