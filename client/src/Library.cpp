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

#include <QApplication>
#include <QtCore>

#include "Library.h"
#include "SettingKeys.h"

namespace vaultaire
{
	/** Sanitize */
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

	/** Add document */
	bool Library::add(const QString& tmpfile,
		const QDate& date, const QString& collection,
		const QString& category, const QString& title,
		const QString& tags)
	{
		QSettings settings(QSettings::SystemScope,
			QApplication::organizationName(),
			QApplication::applicationName());

		QString libRoot = settings.value(LIB_ROOT_KEY,
			DEFAULT_LIB_ROOT).toString();
		qDebug() << "Libroot=" << libRoot;

		// Construct destination path
		QString pattern("%1/%2/%3/%4/%5");
		QString path = pattern.arg(libRoot)
			.arg(collection)
			.arg(date.year())
			.arg(date.month(), 2, 10, QChar('0'))
			.arg(date.day(), 2, 10, QChar('0'));
		qDebug() << "Filepath: " << path;
		QString sanitizedTitle = sanitize(title);
		QString filename = (path + "/%1")
			.arg(sanitizedTitle);
		qDebug() << "Filename: " << filename;

		// Create directory
		QDir libRootDir(libRoot);
		if ( ! libRootDir.exists() || ! libRootDir.mkpath(path))
			return false;

		QFile srcFile(tmpfile);
		if ( ! srcFile.exists())
			return false;

		// Copy/convert to destination file
		if (settings.value(DO_CONVERT_KEY, false).toBool())
		{
			qDebug() << "perform convert";
		}
		else
		{
			if ( ! srcFile.copy(filename))
				return false;
		}

		if (settings.value(DO_OCR_KEY, false).toBool())
		{
			QString ocrFile = (path + "/.%1.ocr")
				.arg(sanitizedTitle);
			qDebug() << "perform OCR " << ocrFile;
		}

		QString metaFilePath = (path + "/.%1.meta")
			.arg(sanitizedTitle);
		QString metaData = QString("Date: %1\nCategory: %2\nTitle: %3\nTags: %4")
			.arg(date.toString())
			.arg(category)
			.arg(title)
			.arg(tags);
		qDebug() << "meta file: " << metaFilePath;
		qDebug() << "meta data: " << metaData;

		QFile metaFile(metaFilePath);
		metaFile.open(QIODevice::WriteOnly | QIODevice::Text);
		qint64 bytesWritten = metaFile.write(metaData.toUtf8());
		metaFile.close();

		return (bytesWritten > 0);
	}
}

