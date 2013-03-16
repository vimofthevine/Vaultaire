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

#include "GeneralSettings.h"
#include "SettingKeys.h"
#include "Settings.h"

namespace vaultaire
{
	//--------------------------------------------------------------------------
	GeneralSettings::GeneralSettings(Settings* settings, QWidget* parent) :
		QWidget(parent), settings(settings)
	{
		bool useSystem = settings->value(SYSTEM_SETTINGS_KEY, false).toBool();

		// Use-system-settings field
		useSystemSettings = new QCheckBox(this);
		useSystemSettings->setChecked(useSystem);
		connect(useSystemSettings, SIGNAL(clicked(bool)),
			this, SLOT(useSystemChanged(bool)));

		// Create form
		QFormLayout* form = new QFormLayout;
		setLayout(form);
		form->addRow(tr("Use system-wide settings?"), useSystemSettings);
	}

	//--------------------------------------------------------------------------
	void GeneralSettings::useSystemChanged(bool useSystem)
	{
		settings->setValue(SYSTEM_SETTINGS_KEY, useSystem);

		QMessageBox::information(this, tr("Settings Change"),
			tr("Some settings may not take affect until restarted"));
	}
}
