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

#include <QApplication>
#include <QtCore>

#include "Library.h"
#include "SettingKeys.h"

namespace vaultaire
{
	/** Static sanitize */
	QString Library::sanitize(const QString& orig)
	{
		QRegExp regex("[\\ <>,.\\/?:;'\"\\[\\{\\]\\}\\|\\\\`~!@#$%^&*\\(\\)+=]");
		QString sanitized = orig;
		int pos = 0;
		while ((pos = regex.indexIn(sanitized)) != -1)
		{
			sanitized = sanitized.replace(pos, regex.matchedLength(), "_");
		}
		qDebug() << "Sanitized: " << sanitized;
		return sanitized;
	}

	/** Constructor */
	Library::Library(QObject* parent) : QObject(parent)
	{
		settings = new QSettings(QSettings::SystemScope,
			qApp->organizationName(), qApp->applicationName(), this);

		process = new QProcess(this);
	}

	/** Add document */
	bool Library::add(const QString& tmpFile,
		const QDate& date, const QString& collection,
		const QString& category, const QString& title,
		const QString& tags)
	{
		QString libRoot = settings->value(LIB_ROOT_KEY,
			DEFAULT_LIB_ROOT).toString();
		qDebug() << "Libroot=" << libRoot;

		// Construct destination path and filenames
		QString pattern("%1/%2/%3/%4/%5");
		QString path = pattern.arg(libRoot)
			.arg(collection)
			.arg(date.year())
			.arg(date.month(), 2, 10, QChar('0'))
			.arg(date.day(), 2, 10, QChar('0'));
		QString sanitizedTitle = sanitize(title);
		QString imgFile = (path + "/%1").arg(sanitizedTitle);
		QString ocrFile = (path + "/.%1.ocr").arg(sanitizedTitle);
		QString metaFile = (path + "/.%1.meta").arg(sanitizedTitle);

		qDebug() << "Image file: " << imgFile;
		qDebug() << "OCR file: " << ocrFile;
		qDebug() << "Meta file: " << metaFile;

		// Create directory
		QDir libRootDir(libRoot);
		if ( ! libRootDir.exists() || ! libRootDir.mkpath(path))
			return false;

		// Copy/convert image file
		if ( ! copyOrConvert(tmpFile, imgFile))
			return false;

		// Extract OCR from image file
		if ( ! extractOcr(tmpFile, ocrFile))
			return false;

		// Store meta data
		return createMetaFile(metaFile, date, category, title, tags);
	}

	/** Copy or convert image file into destination location */
	bool Library::copyOrConvert(const QString& src, const QString& dest)
	{
		QFile srcFile(src);
		if ( ! srcFile.exists())
			return false;

		// Copy/convert to destination file
		if (settings->value(DO_CONVERT_KEY, false).toBool())
		{
			QString command = settings->value(CONVERT_CMD_KEY,
				DEFAULT_CONVERT_CMD).toString();
			qDebug() << "Convert command: " << command;

			QString ext = settings->value(CONVERTED_SUFFIX_KEY,
				DEFAULT_CONVERTED_SUFFIX).toString();

			QString cmd = command.replace("%in%", src)
				.replace("%out%", dest + ext);
			qDebug() << "Command: " << cmd;

			return exec(cmd);
		}
		else
		{
			QString ext = settings->value(SCANNED_SUFFIX_KEY,
				DEFAULT_SCANNED_SUFFIX).toString();
			QString destname = dest + ext;

			qDebug() << "Copying to " << destname;
			return srcFile.copy(destname);
		}
	}

	/** Perform OCR */
	bool Library::extractOcr(const QString& src, const QString& dest)
	{
		if (settings->value(DO_OCR_KEY, false).toBool())
		{
			QString command = settings->value(OCR_CMD_KEY,
				DEFAULT_OCR_CMD).toString();
			qDebug() << "OCR command: " << command;

			QString cmd = command.replace("%in%", src).replace("%out%", dest);
			qDebug() << "Command: " << cmd;

			return exec(cmd);
		}
		else
		{
			return true;
		}
	}

	/** Create meta file */
	bool Library::createMetaFile(const QString& filename, const QDate& date,
		const QString& category, const QString& title, const QString& tags)
	{
		QString metaData = QString("Date: %1\nCategory: %2\nTitle: %3\nTags: %4")
			.arg(date.toString())
			.arg(category)
			.arg(title)
			.arg(tags);
		qDebug() << "meta file: " << filename;
		qDebug() << "meta data: " << metaData;

		QFile metaFile(filename);
		metaFile.open(QIODevice::WriteOnly | QIODevice::Text);
		qint64 bytesWritten = metaFile.write(metaData.toUtf8());
		metaFile.close();

		return (bytesWritten > 0);
	}

	/** Execute command */
	bool Library::exec(const QString& command)
	{
		if (process->state() == QProcess::NotRunning)
		{
			qDebug() << "Executing " << command;
			process->start(command);
			process->waitForFinished();
			return (process->exitStatus() == QProcess::NormalExit);
		}
		else
		{
			qDebug() << "Process already in progress";
			return false;
		}
	}
}

