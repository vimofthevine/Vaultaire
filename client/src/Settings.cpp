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

#include <QtCore>

#include "Settings.h"
#include "SettingKeys.h"

namespace vaultaire
{
	//--------------------------------------------------------------------------
	bool Settings::useSystemSettings = false;

	//--------------------------------------------------------------------------
	Settings::Settings(QObject* parent) : QObject(parent)
	{
		systemSettings = new QSettings(QSettings::SystemScope,
			qApp->organizationName(), qApp->applicationName(), this);
		userSettings = new QSettings(QSettings::UserScope,
			qApp->organizationName(), qApp->applicationName(), this);
		useSystemSettings = userSettings->value(SYSTEM_SETTINGS_KEY,
			false).toBool();
	}

	//--------------------------------------------------------------------------
	QVariant Settings::value(const QString& key,
		const QVariant& defaultValue) const
	{
		QVariant value;

		if (useSystemSettings && key != SYSTEM_SETTINGS_KEY)
		{
			qDebug() << "Using system settings: " << key << " " << defaultValue;
			value = systemSettings->value(key, defaultValue);
		}
		else
		{
			qDebug() << "Using user settings: " << key << " " << defaultValue;
			// Use system value as the default if no user value set
			QVariant systemValue = systemSettings->value(key, defaultValue);
			qDebug() << "  default value: " << systemValue;
			value = userSettings->value(key, systemValue);
		}

		qDebug() << "Returning " << value;
		return value;
	}

	//--------------------------------------------------------------------------
	void Settings::setValue(const QString& key, const QVariant& value)
	{
		if (key == SYSTEM_SETTINGS_KEY)
		{
			useSystemSettings = value.toBool();
			userSettings->setValue(key, value);
		}
		else if (useSystemSettings)
		{
			systemSettings->setValue(key, value);
		}
		else
		{
			userSettings->setValue(key, value);
		}

		emit settingModified(key);
	}

	//--------------------------------------------------------------------------
	bool Settings::isWritable() const
	{
		if (useSystemSettings)
		{
			return systemSettings->isWritable();
		}
		else
		{
			return userSettings->isWritable();
		}
	}
}
