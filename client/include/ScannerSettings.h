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

#ifndef SCANNERSETTINGS_H
#define SCANNERSETTINGS_H

#include <QWidget>

// Forward declaration(s)
class QCheckBox;
class QLineEdit;
class QPushButton;
class QSettings;
class QTextEdit;

namespace vaultaire
{
	// Forward declaration(s)
	class Settings;

	/**
	 * Scanner settings widget.
	 *
	 * @author Kyle Treubig <kyle@vimofthevine.com>
	 */
	class ScannerSettings : public QWidget
	{
		Q_OBJECT

		public:
			/**
			 * Constructs a scanner settings widget.
			 *
			 * @param settings application settings
			 * @param parent   parent widget
			 */
			ScannerSettings(Settings* settings, QWidget* parent = 0);

		private slots:
			/**
			 * Saves the new device name setting.
			 *
			 * @param newDevice new device name value
			 */
			void deviceNameChanged(const QString& newDevice);

			/**
			 * Saves the new scan command setting.
			 */
			void scanCommandChanged();

			/**
			 * Saves the new scanned file suffix setting.
			 *
			 * @param newSuffix new file suffix value
			 */
			void scanSuffixChanged(const QString& newSuffix);

			/**
			 * Saves the new perform-conversion setting.
			 *
			 * @param doConvert new perform-conversion value
			 */
			void doConversionChanged(bool doConvert);

			/**
			 * Saves the new conversion command setting.
			 */
			void convertCommandChanged();

			/**
			 * Saves the new converted file suffix setting.
			 *
			 * @param newSuffix new file suffix value
			 */
			void convertSuffixChanged(const QString& newSuffix);

			/**
			 * Reload setting values if the system-vs-user
			 * setting has changed.
			 *
			 * @param key setting key of the modified setting
			 */
			void reload(const QString& key);

		private:
			/** Settings */
			Settings* settings;

			/** Scanner device */
			QLineEdit* scannerDevice;
			/** Scan command */
			QTextEdit* scanCommand;
			/** Scanned file suffix */
			QLineEdit* scannedSuffix;
			/** Perform-conversion */
			QCheckBox* doConversion;
			/** Conversion command */
			QTextEdit* convertCommand;
			/** Converted file suffix */
			QLineEdit* convertedSuffix;
	};
}

#endif
