/*
 * Copyright 2012 Kyle Treubig
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

// Forward declaration
class QDate;
class QString;

namespace vaultaire
{
	class Library
	{
		public:
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
			static bool add(const QString& tmpfile, const QDate& date,
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
	};
}

#endif
