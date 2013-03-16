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

#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QStatusBar>

// Forward declaration(s)
class QProgressBar;

namespace vaultaire
{
	/**
	 * Main window status bar widget.
	 *
	 * @author Kyle Treubig <kyle@vimofthevine.com>
	 */
	class StatusBar : public QStatusBar
	{
		Q_OBJECT

		public:
			/**
			 * Constructs a status bar widget.
			 *
			 * @param parent parent widget
			 */
			StatusBar(QWidget* parent = 0);

		public slots:
			/**
			 * Sets the progress bar to indeterminate, or
			 * busy mode.
			 */
			void startBusyIndicator();

			/**
			 * Resets the progress bar.
			 */
			void stopBusyIndicator();

			/**
			 * Sets the progress bar to the given value
			 * out of the overall maximum value.
			 *
			 * @param value current progress value
			 * @param max   maximum progress value
			 */
			void showProgress(int value, int max);

		private:
			// Progress bar
			QProgressBar* progress;
	};
}

#endif // STATUSBAR_H
