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

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QVariant>

// Forward declaration(s)
class QSettings;

namespace vaultaire
{
	/**
	 * Application settings model. All settings accessed or set
	 * using this class, rather than the QSettings class, are
	 * dictated as system-wide or user-specific according to the
	 * value of a user-specific system-or-user setting. The value
	 * of the boolean setting, vaultaire::SYSTEM_SETTINGS_KEY,
	 * indicates whether user-specific or system-wide settings are
	 * to be used.
	 *
	 * @author Kyle Treubig <kyle@vimofthevine.com>
	 */
	class Settings : public QObject
	{
		Q_OBJECT

		public:
			/**
			 * Constructs an application settings instance.
			 *
			 * @param parent parent object
			 */
			Settings(QObject* parent = 0);

			/**
			 * Returns the requested seting value. If the setting
			 * does not exist, the default value is returned.
			 *
			 * @param key          setting key
			 * @param defaultValue default setting value
			 */
			QVariant value(const QString& key,
				const QVariant& defaultValue = QVariant()) const;

			/**
			 * Sets the value of the specified setting.
			 *
			 * @param key   setting key
			 * @param value setting value
			 */
			void setValue(const QString& key, const QVariant& value);

			/**
			 * Checks if the current settings (system-wide or user-specific)
			 * can be written.
			 *
			 * @return true if settings can be written
			 */
			bool isWritable() const;

		signals:
			/**
			 * Indicates that an application setting has been
			 * modified.
			 *
			 * @param key setting key of the modified setting
			 */
			void settingModified(QString key);

		private:
			// Flag indicating whether using system-wide or user-specific
			bool useSystemSettings;

			// System-wide settings
			QSettings* systemSettings;
			// User-specific settings
			QSettings* userSettings;
	};
}

#endif // SETTINGS_H
