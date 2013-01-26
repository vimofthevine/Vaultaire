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

#include "LibraryEntry.h"

namespace vaultaire
{
	//--------------------------------------------------------------------------
	LibraryEntry::LibraryEntry(QString dir, QString base, QObject* parent)
		: QObject(parent), dir(dir), base(base),
		full(dir + "/" + base),
		meta(QString(".%1.meta").arg(base)),
		ocr(QString(".%1.ocr").arg(base))
	{ }

	//--------------------------------------------------------------------------
	const QString& LibraryEntry::directory()
	{
		return dir;
	}

	//--------------------------------------------------------------------------
	const QString& LibraryEntry::imageFile()
	{
		return base;
	}

	//--------------------------------------------------------------------------
	const QString& LibraryEntry::fullImagePath()
	{
		return full;
	}

	//--------------------------------------------------------------------------
	const QString& LibraryEntry::metaFile()
	{
		return meta;
	}

	//--------------------------------------------------------------------------
	const QString& LibraryEntry::ocrFile()
	{
		return ocr;
	}

	//--------------------------------------------------------------------------
	LibraryEntry* LibraryEntry::fromMeta(const QString& metafile,
		QObject* parent)
	{
		QFileInfo fileInfo(metafile);
		QString metaFileName(fileInfo.fileName());
		QRegExp firstDecimal("^\\.");
		QRegExp metaExtension("\\.meta$");
		QString baseFileName(metaFileName.replace(firstDecimal,"")
			.replace(metaExtension,""));

		return new LibraryEntry(fileInfo.dir().absolutePath(),
			baseFileName, parent);
	}

	//--------------------------------------------------------------------------
	LibraryEntry* LibraryEntry::fromOcr(const QString& ocrfile,
		QObject* parent)
	{
		QFileInfo fileInfo(ocrfile);
		QString ocrFileName(fileInfo.fileName());
		QRegExp firstDecimal("^\\.");
		QRegExp ocrExtension("\\.ocr*$");
		QString baseFileName(ocrFileName.replace(firstDecimal,"")
			.replace(ocrExtension,""));

		return new LibraryEntry(fileInfo.dir().absolutePath(),
			baseFileName, parent);
	}

}

