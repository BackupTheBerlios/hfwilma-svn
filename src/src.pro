TEMPLATE = app
TARGET   = hfwilma

QT += network
CONFIG += debug qtestlib
INCLUDEPATH += . astmanager data gui

TRANSLATIONS = src_de.ts \


SOURCES  = \
           main.cpp  \
           astmanager/astmanager.cpp \
           astmanager/astmanagerreadthread.cpp \
           data/channel.cpp \
           data/connection.cpp \
           gui/mainwidget.cpp  \

HEADERS  = \
           astmanager/astmanager.h \
           astmanager/astmanagerreadthread.h \
           data/channel.h \
           data/connection.h \
           gui/mainwidget.h \

FORMS = \
        forms/channelwidget.ui

RESOURCES= src.qrc
include(../hfwilma.pri)
