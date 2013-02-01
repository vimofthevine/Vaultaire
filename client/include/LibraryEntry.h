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

#ifndef LIBRARYENTRY_H
#define LIBRARYENTRY_H

#include <QtCore>

namespace vaultaire
{
	class LibraryEntry : QObject
	{
		Q_OBJECT

		public:
			/**
			 * Constructs a new library entry.
			 *
			 * @param dir    directory location of the library entry
			 * @param base   base filename of the library entry
			 * @param parent parent object
			 */
			LibraryEntry(QString dir, QString base, QObject* parent = 0);

			/**
			 * Returns the directory location for this entry.
			 *
			 * @return directory location
			 */
			const QString& directory();

			/**
			 * Returns the name of the image file for this entry.
			 *
			 * @return image filename
			 */
			const QString& imageFile();

			/**
			 * Returns the full path to the image file for this entry.
			 *
			 * @return full image filepath
			 */
			const QString& fullImagePath();

			/**
			 * Returns the name of the meta-data file for this entry.
			 *
			 * @return meta-data filename
			 */
			const QString& metaFile();

			/**
			 * Returns the name of the OCR file for this entry.
			 *
			 * @return OCR filename
			 */
			const QString& ocrFile();

			/**
			 * Constructs a new library entry represented by the
			 * given meta filename.
			 *
			 * @param metafile meta filename
			 * @param parent   parent object
			 */
			static LibraryEntry* fromMeta(const QString& metafile,
				QObject* parent = 0);

			/**
			 * Constructs a new library entry represented by the
			 * given OCR filename.
			 *
			 * @param ocrfile  OCR filename
			 * @param parent   parent object
			 */
			static LibraryEntry* fromOcr(const QString& ocrfile,
				QObject* parent = 0);

		private:
			const QString dir, base, full, meta, ocr;
	};
}

#endif // LIBRARYENTRY_H
