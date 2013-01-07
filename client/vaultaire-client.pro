#-------------------------------------------------
# Vaultaire Client project file
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = vaultaire-client
TEMPLATE = app

SOURCES += src/main.cpp \
           src/MainWindow.cpp \
           src/MainMenu.cpp \
           src/LibrarySettings.cpp \
           src/SettingsDialog.cpp

HEADERS  += include/MainWindow.h \
            include/MainMenu.h \
            include/LibrarySettings.h \
            include/SettingsDialog.h

INCLUDEPATH += ./include

DESTDIR = bin

