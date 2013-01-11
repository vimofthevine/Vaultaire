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

#include "ScannerSettings.h"

namespace vaultaire
{
	// Scanner device
	static const QString DEVICE_KEY = "ScannerDevice";
	static const QString DEFAULT_DEVICE = "";
	static const QString DEVICE_HELP = "Unique identifier of the scanner device";

	// Scan command
	static const QString COMMAND_KEY = "ScanCommand";
	static const QString DEFAULT_COMMAND = "scanimage -d \%device\% --format=tiff > \%file\%";
	static const QString COMMAND_HELP = "Command to be executed to perform a scan";
	static const QString COMMAND_VERBOSE_HELP = "Command to be executed to perform a scan operation.\n"
		"\n"
		"The following values in the command are automatically replaced:\n"
		"  %device% : the unique name of the scanner device\n"
		"  %file% : name and location of the output file";

	/** Constructor */
	ScannerSettings::ScannerSettings(QWidget* parent)
		: QWidget(parent)
	{
		settings = new QSettings(QSettings::SystemScope,
			qApp->organizationName(), qApp->applicationName(), this);

		// Scanner device field
		QString currentDevice = settings->value(DEVICE_KEY,
			DEFAULT_DEVICE).toString();
		scannerDevice = new QLineEdit(currentDevice, this);
		scannerDevice->setToolTip(DEVICE_HELP);
		connect(scannerDevice, SIGNAL(textEdited(QString)),
			this, SLOT(deviceNameChanged(QString)));

		// Scan command field
		QString currentCommand = settings->value(COMMAND_KEY,
			DEFAULT_COMMAND).toString();
		scanCommand = new QLineEdit(currentCommand, this);
		scanCommand->setToolTip(COMMAND_HELP);
		connect(scanCommand, SIGNAL(textEdited(QString)),
			this, SLOT(scanCommandChanged(QString)));

		// Scan command help button
		scanHelp = new QPushButton(tr("help"), this);
		connect(scanHelp, SIGNAL(clicked()),
			this, SLOT(showVerboseCommandHelp()));

		// But scan command field and help button together
		QHBoxLayout* commandLayout = new QHBoxLayout;
		commandLayout->addWidget(scanCommand);
		commandLayout->addWidget(scanHelp);

		// Create form
		QFormLayout* form = new QFormLayout;
		setLayout(form);
		form->addRow(tr("Scanner Device"), scannerDevice);
		form->addRow(tr("Scan Command"), commandLayout);

		// Disable field if not writable (i.e., no permission
		// to modify system-level settings
		scannerDevice->setEnabled(settings->isWritable());
		scanCommand->setEnabled(settings->isWritable());
	}

	/** Store change to scanner device */
	void ScannerSettings::deviceNameChanged(const QString& newDevice)
	{
		settings->setValue(DEVICE_KEY, newDevice);
	}

	/** Store change to scan command */
	void ScannerSettings::scanCommandChanged(const QString& newCommand)
	{
		settings->setValue(COMMAND_KEY, newCommand);
	}

	/** Show command help */
	void ScannerSettings::showVerboseCommandHelp()
	{
		QMessageBox::information(this, tr("Scan Command"),
			COMMAND_VERBOSE_HELP);
	}

}

