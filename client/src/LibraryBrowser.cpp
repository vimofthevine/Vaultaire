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

#include <QtGui>

#include "FileBrowser.h"
#include "ImageViewer.h"
#include "LibraryBrowser.h"

namespace vaultaire
{
	/** Constructor */
	LibraryBrowser::LibraryBrowser(QWidget* parent) : QSplitter(parent)
	{
		fileBrowser = new FileBrowser(this);
		connect(fileBrowser, SIGNAL(directoryChanged(QString)),
			this, SLOT(handleDirectoryChange()));
		connect(fileBrowser, SIGNAL(fileSelected(QString)),
			this, SLOT(handleFileSelection(QString)));

		imageViewer = new ImageViewer(this);

		addWidget(fileBrowser);
		addWidget(imageViewer);
		setStretchFactor(1, 2); // Give more weight to the viewer
}

	/** Directory-change */
	void LibraryBrowser::handleDirectoryChange()
	{
		imageViewer->clear();
	}

	/** File-selected */
	void LibraryBrowser::handleFileSelection(const QString& filepath)
	{
		if ( ! QImageReader::imageFormat(filepath).isEmpty())
		{
			imageViewer->open(filepath);
		}
	}
}

