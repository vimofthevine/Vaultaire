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

#ifndef FILEBROWSER_H
#define FILEBROWSER_H

#include <QTableView>

// Forward declarations
class QFileSystemModel;
class QModelIndex;
class QTreeView;

namespace vaultaire
{
	class FileBrowser : public QTableView
	{
		Q_OBJECT

		public:
			/**
			 * Constructs a new file browser widget.
			 *
			 * @param parent parent widget
			 */
			FileBrowser(QWidget* parent = 0);

		private slots:
			void handleDoubleClick(const QModelIndex& index);
			void handleSelection(const QModelIndex& index, const QModelIndex& prev);

		signals:
			void directoryChanged(const QString& directory);
			void fileSelected(const QString& filepath);

		private:
			QString libRoot;
			QFileSystemModel* fsModel;
	};
}

#endif
