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

#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <QObject>
#include <QProcess>

// Forward declarations
class QDate;
class QProcess;
class QSettings;

namespace vaultaire
{
	/**
	 * Model to represent a search of files.
	 *
	 * @author Kyle Treubig <kyle@vimofthevine.com>
	 */
	class SearchEngine : public QObject
	{
		Q_OBJECT

		public:
			/**
			 * Constructs a new search engine.
			 *
			 * @param settings application settings
			 * @param parent   parent object
			 */
			SearchEngine(QSettings* settings, QObject* parent = 0);

			/**
			 * Checks if the engine is currently
			 * performing a search.
			 *
			 * @return true if currently searching
			 */
			bool isSearching() const;

		public slots:
			/**
			 * Performs a search for files that match the
			 * given search parameters.
			 *
			 * @param year        year date filter parameter
			 * @param month       month date filter parameter
			 * @param date        day date filter parameter
			 * @param collection  library collection to be searched, else if empty a
			 *                    a general library search will be performed
			 * @param field       meta data field to be searched
			 * @param parameter   search parameter
			 * @param insensitive true for a case insensitive search
			 */
			void search(int year, int month, int date,
				const QString& collection, const QString& field,
				const QString& parameter, bool insensitive);

			/**
			 * Cancels a running search operation.
			 */
			void cancel();

		private slots:
			void finished(int exitCode, QProcess::ExitStatus exitStatus);
			void error(QProcess::ProcessError error);

		signals:
			/**
			 * Signals that a search operation has begun.
			 */
			void started();

			/**
			 * Signals that an error occured during the search.
			 */
			void failed();

			/**
			 * Signals that a search operation has finished.
			 *
			 * @param results search results
			 */
			void finished(QStringList results);

		private:
			QSettings* settings;
			QProcess* process;
	};
}

#endif
