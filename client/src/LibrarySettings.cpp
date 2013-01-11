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

#include <QtGui>

#include "LibrarySettings.h"

namespace vaultaire
{
	// Library root
	static const QString& LIB_ROOT_KEY = "LibraryRootDirectory";
	static const QString& DEFAULT_LIB_ROOT = "~/Documents/Library";
	static const QString& LIB_ROOT_HELP = "Root directory in which all library documents are found";

	/** Constructor */
	LibrarySettings::LibrarySettings(QWidget* parent)
		: QWidget(parent)
	{
		settings = new QSettings(QSettings::SystemScope,
			QApplication::organizationName(),
			QApplication::applicationName(),
			this);

		// Library root directory field
		QString currentLibRoot = settings->value(LIB_ROOT_KEY,
			DEFAULT_LIB_ROOT).toString();
		libRoot = new QLineEdit(currentLibRoot, this);
		libRoot->setToolTip(LIB_ROOT_HELP);
		connect(libRoot, SIGNAL(textEdited(QString)),
			this, SLOT(libRootChanged(QString)));

		// Create form
		QFormLayout* form = new QFormLayout;
		setLayout(form);
		form->addRow(tr("Library Root"), libRoot);

		// Disable fields if not writable (i.e., no permission
		// to modify system-level settings
		libRoot->setEnabled(settings->isWritable());
	}

	/** Store change to library root directory */
	void LibrarySettings::libRootChanged(const QString& newLibRoot)
	{
		settings->setValue(LIB_ROOT_KEY, newLibRoot);
	}

}

