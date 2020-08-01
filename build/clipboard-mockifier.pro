include(../vendor/vendor.pri)

HEADERS += ../src/MainWindow.h
ICON = ../res/icon.icns
QMAKE_INFO_PLIST = ../res/clipboard-mockifier-Info.plist
QT += core gui widgets
RESOURCES = ../clipboard-mockifier.qrc
SOURCES += ../src/main.cpp ../src/MainWindow.cpp
TARGET = "Clipboard Mockifier"
TEMPLATE += app
