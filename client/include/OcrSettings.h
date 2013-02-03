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

#ifndef OCRSETTINGS_H
#define OCRSETTINGS_H

#include <QWidget>

// Forward declaration(s)
class QCheckBox;
class QSettings;
class QTextEdit;

namespace vaultaire
{
	// Forward declaration(s)
	class Settings;

	/**
	 * OCR settings widget.
	 *
	 * @author Kyle Treubig <kyle@vimofthevine.com>
	 */
	class OcrSettings : public QWidget
	{
		Q_OBJECT

		public:
			/**
			 * Constructs a OCR settings widget.
			 *
			 * @param settings application settings
			 * @param parent   parent widget
			 */
			OcrSettings(Settings* settings, QWidget* parent = 0);

		private slots:
			/**
			 * Saves the new perform-OCR setting.
			 *
			 * @param doOcr new perform-OCR value
			 */
			void doOcrChanged(bool doOcr);

			/**
			 * Saves the new OCR command setting.
			 */
			void ocrCommandChanged();

			/**
			 * Reload setting values if the system-vs-user
			 * setting has changed.
			 *
			 * @param key setting key of the modified setting
			 */
			void reload(const QString& key);

		private:
			// Settings
			Settings* settings;

			// Perform-OCR field
			QCheckBox* doOcr;
			// OCR command field
			QTextEdit* ocrCommand;
	};
}

#endif
