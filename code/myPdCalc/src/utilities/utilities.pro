HOME =../../
include($$HOME / common.pri) 
TEMPLATE = lib 
TARGET = pdCalcUtilities
DEPENDPATH += .
INCLUDEPATH += . $$HOME/src
unix: DESTDIR = $$HOME/lib

HEADERS += Publisher.h \
    Observer.h \
    Exception.h

SOURCES += Publisher.cpp \
    Observer.cpp

unix : LIBS += -ldl
