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

#include "SearchEngine.h"
#include "SettingKeys.h"

namespace vaultaire
{
	/** Constructor */
	SearchEngine::SearchEngine(QSettings* settings, QObject* parent) :
		QObject(parent), settings(settings)
	{
		process = new QProcess(this);
		connect(process, SIGNAL(error(QProcess::ProcessError)),
			this, SLOT(error(QProcess::ProcessError)));
		connect(process, SIGNAL(finished(int, QProcess::ExitStatus)),
			this, SLOT(finished(int, QProcess::ExitStatus)));
		connect(process, SIGNAL(started()), this, SIGNAL(started()));
	}

	/** Search */
	void SearchEngine::search(int year, int month, int date,
		const QString& collection, const QString& field,
		const QString& parameter, bool insensitive)
	{
		QString searchDirectory = settings->value(LIB_ROOT_KEY,
			DEFAULT_LIB_ROOT).toString();
		QString searchPath(searchDirectory + "/");
		QString switches("-l");
		QString searchQuery;

		// Add collection to search path
		searchPath.append(collection.isEmpty() ? "*/"
			: collection + "/");

		// Add year to search path
		searchPath.append((year <= 0) ? "*/"
			: QString("%1/").arg(year));

		// Add month to search path
		searchPath.append((month <= 0) ? "*/"
			: QString("%1/").arg(month, 2, 10, QChar('0')));

		// Add date to search path
		searchPath.append((date <= 0) ? "*/"
			: QString("%1/").arg(date, 2, 10, QChar('0')));

		if (field == "OCR")
		{
			searchPath.append(".*.ocr*");
		}
		else
		{
			searchPath.append("*.meta");

			// Add meta data field (if any)
			if ( ! field.isEmpty())
			{
				searchQuery.append(QString("^%1: *").arg(field));
			}
		}

		// Add search parameter
		searchQuery.append(parameter);

		// Case sensitivity
		if (insensitive)
		{
			switches.append("i");
		}

		qDebug() << "Searching for " << searchQuery
			<< " in " << searchDirectory
			<< " named " << searchPath;

		// Put it all together
		QStringList args;
		args << searchDirectory << "-path" << searchPath
			<< "-exec" << "grep" << switches << searchQuery << "{}" << ";";
		qDebug() << "args: " << args;
		process->start("find", args);
	}

	/** Is-searching */
	bool SearchEngine::isSearching() const
	{
		return (process->state() != QProcess::NotRunning);
	}

	/** Cancel */
	void SearchEngine::cancel()
	{
		if (isSearching())
		{
			qDebug() << "Terminating search process";
			process->terminate();
		}
	}

	/** Finished slot */
	void SearchEngine::finished(int exitCode, QProcess::ExitStatus exitStatus)
	{
		if (exitStatus == QProcess::NormalExit)
		{
			qDebug() << "Search process normal exit";

			QString out(process->readAllStandardOutput());
			qDebug() << "stdout: " << out;
			qDebug() << "stderr: " << process->readAllStandardError();

			QStringList results = out.split("\n", QString::SkipEmptyParts);
			qDebug() << "results: " << results;
			emit finished(results);
		}
		else
		{
			qDebug() << "Scan process crash exit";
		}
	}

	/** Error slot */
	void SearchEngine::error(QProcess::ProcessError error)
	{
		qDebug() << "Search process error: " << error;
		QStringList noResults;
		emit finished(noResults);
		emit failed();
	}
}

