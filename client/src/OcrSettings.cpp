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

#include "OcrSettings.h"
#include "SettingKeys.h"

namespace vaultaire
{
	static const QString OCR_COMMAND_HELP = "Command to be executed to perform optical character recognition.\n"
		"\n"
		"The following values in the command are automatically replaced:\n"
		"  %in% : image file to be processed\n"
		"  %out% : output file for OCR text";

	/** Constructor */
	OcrSettings::OcrSettings(QWidget* parent)
		: QWidget(parent)
	{
		settings = new QSettings(QSettings::SystemScope,
			qApp->organizationName(), qApp->applicationName(), this);

		bool currentDoOcr = settings->value(DO_OCR_KEY, false).toBool();

		// OCR command field
		QString currentOcrCmd = settings->value(OCR_CMD_KEY,
			DEFAULT_OCR_CMD).toString();
		ocrCommand = new QTextEdit(currentOcrCmd, this);
		ocrCommand->setToolTip(OCR_COMMAND_HELP);
		ocrCommand->setTabChangesFocus(true);
		ocrCommand->setMaximumHeight(100);
		connect(ocrCommand, SIGNAL(textChanged()),
			this, SLOT(ocrCommandChanged()));

		// Do-OCR field
		doOcr = new QCheckBox(this);
		doOcr->setChecked(currentDoOcr);
		connect(doOcr, SIGNAL(clicked(bool)),
			this, SLOT(doOcrChanged(bool)));
		connect(doOcr, SIGNAL(clicked(bool)),
			ocrCommand, SLOT(setEnabled(bool)));

		// Create form
		QFormLayout* form = new QFormLayout;
		setLayout(form);
		form->addRow(tr("Perform OCR?"), doOcr);
		form->addRow(tr("OCR Command"), ocrCommand);

		// Disable field if not writable (i.e., no permission
		// to modify system-level settings)
		doOcr->setEnabled(settings->isWritable());
		ocrCommand->setEnabled(currentDoOcr && settings->isWritable());
	}

	/** Store change to do-OCR */
	void OcrSettings::doOcrChanged(bool doOcr)
	{
		settings->setValue(DO_OCR_KEY, doOcr);
	}

	/** Store change to OCR command */
	void OcrSettings::ocrCommandChanged()
	{
		settings->setValue(OCR_CMD_KEY, ocrCommand->toPlainText());
	}
}

