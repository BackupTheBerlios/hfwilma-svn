TEMPLATE = app
TARGET   = hfwilma

SOURCES  = \
           main.cpp  \
           gui/mainwidget.cpp  \
#           astmanager/astmanager.cpp \
#           data/connection.cpp \
#           data/connections.cpp

HEADERS  = \
           gui/mainwidget.h \
#           astmanager/astmanager.h\   
#           data/connection.h \
#           data/connections.h

RESOURCES= src.qrc
include(../hfwilma.pri)
