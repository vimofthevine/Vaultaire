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

#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>

// Forward declaration
class QAction;
class QLabel;
class QScrollArea;
class QScrollBar;

namespace vaultaire
{
	/**
	 * A widget for displaying an image.
	 *
	 * @author Kyle Treubig <kyle@vimofthevine.com>
	 */
	class ImageViewer : public QWidget
	{
		Q_OBJECT

		public:
			/**
			 * Constructs a new image viewer widget.
			 *
			 * @param parent parent widget
			 */
			ImageViewer(QWidget* parent = 0);

		public slots:
			/**
			 * Opens and displays the given image.
			 *
			 * @param filename path to the image file
			 */
			void open(QString filename);

			/**
			 * Clears the displayed image.
			 */
			void clear();

		private slots:
			/**
			 * Zooms in
			 */
			void zoomIn();

			/**
			 * Zooms out
			 */
			void zoomOut();

			/**
			 * Resets to normal size
			 */
			void normalSize();

			/**
			 * Resizes to fit in the window
			 */
			void fitToWindow();

		private:
			/** Creates actions */
			void createActions();
			/** Creates context menu */
			void createMenu();
			/** Updates actions */
			void updateActions();
			/** Scales the displayed image */
			void scaleImage(double factor);
			/** Adjusts the scrollbar to fit the image */
			void adjustScrollBar(QScrollBar* scrollBar, double factor);

			QLabel* imageLabel;
			QScrollArea* scrollArea;
			double scaleFactor;

			QAction* zoomInAction;
			QAction* zoomOutAction;
			QAction* normalSizeAction;
			QAction* fitToWindowAction;
	};
}

#endif
