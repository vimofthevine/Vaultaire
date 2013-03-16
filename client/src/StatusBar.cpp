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

#include <QtWidgets>

#include "StatusBar.h"

namespace vaultaire
{
	//--------------------------------------------------------------------------
	StatusBar::StatusBar(QWidget* parent) :
		QStatusBar(parent), progress(new QProgressBar(this))
	{
		// Get progress bar ready
		progress->setMaximumSize(170, 19);
		progress->setTextVisible(false);
		progress->setEnabled(false);
		progress->setMinimum(0);
		progress->setMaximum(100);
		progress->setValue(100);

		// Initially not part of status bar
		addPermanentWidget(progress);
		progress->setVisible(false);
	}

	//--------------------------------------------------------------------------
	void StatusBar::startBusyIndicator()
	{
		if ( ! progress->isVisible())
		{
			progress->setVisible(true);
		}

		// Busy when min=0, max=0, value=0
		progress->setMinimum(0);
		progress->setMaximum(0);
		progress->setValue(0);
	}

	//--------------------------------------------------------------------------
	void StatusBar::stopBusyIndicator()
	{
		if (progress->isVisible())
		{
			progress->setVisible(false);
		}

		// Stop animations
		progress->setMinimum(0);
		progress->setMaximum(100);
		progress->setValue(0);
	}

	//--------------------------------------------------------------------------
	void StatusBar::showProgress(int value, int max)
	{
		// If finished (i.e., 100%)
		if (value == max && progress->isVisible())
		{
			progress->setVisible(false);
		}
		// Else in-progress (0 <= % < 100)
		else if (value != max && ! progress->isVisible())
		{
			progress->setVisible(true);
		}

		progress->setMinimum(0);
		progress->setMaximum(max);
		progress->setValue(value);
	}
}

