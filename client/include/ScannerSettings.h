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

class QCheckBox;
class QLineEdit;
class QPushButton;
class QSettings;
class QTextEdit;

namespace vaultaire
{
	/**
	 * Scanner settings panel.
	 *
	 * @author Kyle Treubig <kyle@vimofthevine.com>
	 */
	class ScannerSettings : public QWidget
	{
		Q_OBJECT

		public:
			/**
			 * Constructs a new scanner settings panel.
			 *
			 * @param parent parent widget
			 */
			ScannerSettings(QWidget* parent = 0);

		private slots:
			void deviceNameChanged(const QString& newDevice);
			void scanCommandChanged();
			void scanSuffixChanged(const QString& newSuffix);
			void doConversionChanged(bool doConvert);
			void convertCommandChanged();
			void convertSuffixChanged(const QString& newSuffix);

		private:
			/** System-wide settings */
			QSettings* settings;
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
