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

#include "Scanner.h"
#include "SettingKeys.h"
#include "Settings.h"

namespace vaultaire
{
	//--------------------------------------------------------------------------
	Scanner::Scanner(QObject* parent) :
		QObject(parent),
		settings(new Settings(this)),
		process(new QProcess(this))
	{
		connect(process, SIGNAL(error(QProcess::ProcessError)),
			this, SLOT(error(QProcess::ProcessError)));
		connect(process, SIGNAL(finished(int, QProcess::ExitStatus)),
			this, SLOT(finished(int, QProcess::ExitStatus)));
		connect(process, SIGNAL(started()), this, SIGNAL(started()));
	}

	//--------------------------------------------------------------------------
	void Scanner::scan(const QString& filename)
	{
		// Only one scan at a time
		if ( ! isScanning())
		{
			// Re-read settings
			QString command = settings->value(SCAN_COMMAND_KEY,
				DEFAULT_SCAN_COMMAND).toString();
			qDebug() << "Scan command: " << command;

			QString device = settings->value(SCANNER_DEVICE_KEY,
				DEFAULT_SCANNER_DEVICE).toString();
			qDebug() << "Scanner: " << device;

			QString cmd = command.replace("%device%", device);
			qDebug() << "Command: " << cmd;

			process->setStandardOutputFile(filename);
			process->start(cmd);
		}
	}

	//--------------------------------------------------------------------------
	bool Scanner::isScanning() const
	{
		return (process->state() != QProcess::NotRunning);
	}

	//--------------------------------------------------------------------------
	void Scanner::cancel()
	{
		if (isScanning())
		{
			qDebug() << "Terminating scan process";
			process->terminate();
		}
	}

	//--------------------------------------------------------------------------
	void Scanner::finished(int exitCode, QProcess::ExitStatus exitStatus)
	{
		if (exitStatus == QProcess::NormalExit)
		{
			qDebug() << "Scan process normal exit";

			QString err(process->readAllStandardError());
			err = err.toLower();
			qDebug() << "stderr: " << err;

			if (err.contains("cancel"))
			{
				emit finished(ScanCancelled);
			}
			else if (err.contains("error") || err.contains("fail"))
			{
				emit finished(ScanFailed);
			}
			else
			{
				emit finished(ScanComplete);
			}
		}
		else
		{
			qDebug() << "Scan process crash exit";
		}
	}

	//--------------------------------------------------------------------------
	void Scanner::error(QProcess::ProcessError error)
	{
		qDebug() << "Scan process error: " << error;
		switch(error)
		{
			case QProcess::FailedToStart:
				emit finished(ScanNotStarted);
				break;
			default:
				emit finished(ScanFailed);
		}
	}

}

