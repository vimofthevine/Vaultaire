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

#ifndef LIBRARY_H
#define LIBRARY_H

#include <QtCore>

namespace vaultaire
{
	// Forward declaration
	class Settings;

	/**
	 * Model of the document library.
	 *
	 * @author Kyle Treubig <kyle@vimofthevine.com>
	 */
	class Library : QObject
	{
		Q_OBJECT

		public:
			/**
			 * Constructs a new document library model.
			 *
			 * @param parent parent object
			 */
			Library(QObject* parent = 0);

			/**
			 * Adds the specified file to the document library
			 * with the given parameters.
			 *
			 * @param tmpfile    temporary file location
			 * @param date       document date
			 * @param collection library collection
			 * @param category   document category
			 * @param title      document title
			 * @param tags       document tags
			 * @return true if the document was successfully added
			 *         to the document library
			 */
			bool add(const QString& tmpfile, const QDate& date,
				const QString& collection, const QString& category,
				const QString& title, const QString& tags);

			/**
			 * Creates a sanitized (i.e., filename-friendly)
			 * copy of the given string.
			 *
			 * @param orig original file name
			 * @return sanitized file name
			 */
			static QString sanitize(const QString& orig);

		private:
			// Settings
			Settings* settings;
			// External process
			QProcess* process;

			/**
			 * Copies the source file to the destination location. If
			 * configured to perform conversion, the file is converted
			 * using the configured conversion command.
			 *
			 * @param src  source image file
			 * @param dest destination image file
			 */
			bool copyOrConvert(const QString& src, const QString& dest);

			/**
			 * Extracts the contents from the given file to the destination
			 * text file, if optical character recognition is configured.
			 *
			 * @param src  source image file
			 * @param dest destination text file
			 */
			bool extractOcr(const QString& src, const QString& dest);

			/**
			 * Creates a meta-data file to hold the given meta information.
			 *
			 * @param filename image file name
			 * @param date     document date
			 * @param category document category
			 * @param tile     document title
			 * @param tags     document tags
			 */
			bool createMetaFile(const QString& filename, const QDate& date,
				const QString& category, const QString& title, const QString& tags);

			/**
			 * Execute the given command as an external process.
			 *
			 * @param command external command
			 */
			bool exec(const QString& command);
	};
}

#endif
