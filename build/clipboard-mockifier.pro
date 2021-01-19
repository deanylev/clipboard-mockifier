include(../src/singleapplication/singleapplication.pri)
include(../vendor/vendor.pri)

DEFINES += QAPPLICATION_CLASS=QApplication
HEADERS += ../src/MainWindow.h
ICON = ../res/icon.icns
LIBS += -dead_strip
QMAKE_INFO_PLIST = ../res/clipboard-mockifier-Info.plist
QT += core gui widgets
RC_ICONS = ../res/icon.ico
RESOURCES = ../clipboard-mockifier.qrc
SOURCES += ../src/main.cpp ../src/MainWindow.cpp
TARGET = "Clipboard Mockifier"
TEMPLATE += app
