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

#include "ImageViewer.h"

namespace vaultaire
{
	/** Constructor */
	ImageViewer::ImageViewer(QWidget* parent) : QWidget(parent)
	{
		imageLabel = new QLabel;
		imageLabel->setBackgroundRole(QPalette::Base);
		imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
		imageLabel->setScaledContents(true);

		scrollArea = new QScrollArea;
		scrollArea->setBackgroundRole(QPalette::Base);
		scrollArea->setWidget(imageLabel);

		QHBoxLayout* layout = new QHBoxLayout;
		layout->addWidget(scrollArea);
		setLayout(layout);

		createActions();
		createMenu();

		clear();
	}

	/** Open */
	void ImageViewer::open(QString filename)
	{
		if ( ! filename.isEmpty())
		{
			QImage image(filename);
			if ( ! image.isNull())
			{
				imageLabel->setPixmap(QPixmap::fromImage(image));
				scaleFactor = 1.0;

				fitToWindowAction->setEnabled(true);
				updateActions();

				if ( ! fitToWindowAction->isChecked())
				{
					imageLabel->adjustSize();
				}

				scrollArea->setEnabled(true);
			}
			else
			{
				clear();
			}
		}
		else
		{
			clear();
		}
	}

	/** Clear */
	void ImageViewer::clear()
	{
		QPixmap cleared;
		imageLabel->setPixmap(cleared);
		fitToWindow();
		scrollArea->setEnabled(false);
	}

	/** Zoom in */
	void ImageViewer::zoomIn()
	{
		scaleImage(1.25);
	}

	/** Zoom out */
	void ImageViewer::zoomOut()
	{
		scaleImage(0.8);
	}

	/** Normal-size reset */
	void ImageViewer::normalSize()
	{
		imageLabel->adjustSize();
		scaleFactor = 1.0;
		scaleImage(1);
	}

	/** Fit-to-window */
	void ImageViewer::fitToWindow()
	{
		bool fitToWindow = fitToWindowAction->isChecked();
		scrollArea->setWidgetResizable(fitToWindow);
		if ( ! fitToWindow)
		{
			normalSize();
		}
		updateActions();
	}

	/** Scale */
	void ImageViewer::scaleImage(double factor)
	{
		Q_ASSERT(imageLabel->pixmap());
		scaleFactor *= factor;
		imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

		adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
		adjustScrollBar(scrollArea->verticalScrollBar(), factor);

		zoomInAction->setEnabled(scaleFactor < 3.0);
		zoomOutAction->setEnabled(scaleFactor > 0.333);
	}

	/** Adjust scrollbar */
	void ImageViewer::adjustScrollBar(QScrollBar* scrollBar, double factor)
	{
		scrollBar->setValue(int(factor * scrollBar->value()
			+ ((factor - 1) * scrollBar->pageStep() / 2)));
	}

	/** Update actions */
	void ImageViewer::updateActions()
	{
		bool fitToWindow = fitToWindowAction->isChecked();
		zoomInAction->setEnabled( ! fitToWindow);
		zoomOutAction->setEnabled( ! fitToWindow);
		normalSizeAction->setEnabled( ! fitToWindow);
	}

	/** Create actions */
	void ImageViewer::createActions()
	{
		zoomInAction = new QAction(tr("Zoom &In (25%)"), this);
		zoomInAction->setShortcut(tr("Ctrl++"));
		zoomInAction->setEnabled(false);
		connect(zoomInAction, SIGNAL(triggered()), this, SLOT(zoomIn()));

		zoomOutAction = new QAction(tr("Zoom &Out (25%)"), this);
		zoomOutAction->setShortcut(tr("Ctrl+-"));
		zoomOutAction->setEnabled(false);
		connect(zoomOutAction, SIGNAL(triggered()), this, SLOT(zoomOut()));

		normalSizeAction = new QAction(tr("&Normal Size"), this);
		normalSizeAction->setShortcut(tr("Ctrl+S"));
		normalSizeAction->setEnabled(false);
		connect(normalSizeAction, SIGNAL(triggered()), this, SLOT(normalSize()));

		fitToWindowAction = new QAction(tr("&Fit to Window"), this);
		fitToWindowAction->setEnabled(false);
		fitToWindowAction->setCheckable(true);
		fitToWindowAction->setShortcut(tr("/"));
		fitToWindowAction->setChecked(true);
		connect(fitToWindowAction, SIGNAL(triggered()),
			this, SLOT(fitToWindow()));
	}

	/** Create menu */
	void ImageViewer::createMenu()
	{
		addAction(zoomInAction);
		addAction(zoomOutAction);
		addAction(normalSizeAction);
		addAction(fitToWindowAction);

		setContextMenuPolicy(Qt::ActionsContextMenu);
	}

}

