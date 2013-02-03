#-------------------------------------------------
# Vaultaire Client project file
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = vaultaire
TEMPLATE = app

SOURCES += src/main.cpp \
           src/Settings.cpp \
           src/MainWindow.cpp \
           src/MainMenu.cpp \
           src/StatusBar.cpp \
           src/MetaDataForm.cpp \
           src/ScanView.cpp \
           src/SearchForm.cpp \
           src/SearchView.cpp \
           src/LibraryEntry.cpp \
           src/LibraryBrowser.cpp \
           src/FileBrowser.cpp \
           src/ImageViewer.cpp \
           src/Scanner.cpp \
           src/Library.cpp \
           src/SearchEngine.cpp \
           src/GeneralSettings.cpp \
           src/LibrarySettings.cpp \
           src/ScannerSettings.cpp \
           src/OcrSettings.cpp \
           src/AppearanceSettings.cpp \
           src/SettingsDialog.cpp

HEADERS  += include/Settings.h \
            include/MainWindow.h \
            include/MainMenu.h \
            include/StatusBar.h \
            include/MetaDataForm.h \
            include/ScanView.h \
            include/SearchForm.h \
            include/SearchView.h \
            include/LibraryEntry.h \
            include/LibraryBrowser.h \
            include/FileBrowser.h \
            include/ImageViewer.h \
            include/Scanner.h \
            include/Library.h \
            include/SearchEngine.h \
            include/GeneralSettings.h \
            include/LibrarySettings.h \
            include/ScannerSettings.h \
            include/OcrSettings.h \
            include/AppearanceSettings.h \
            include/SettingsDialog.h

RESOURCES += vaultaire.qrc

INCLUDEPATH += ./include

DESTDIR = bin
OBJECTS_DIR = build/objs
MOC_DIR = build/moc
RCC_DIR = build/rcc
UI_DIR = build/ui

#QMAKE_CXXFLAGS +=-ggdb

