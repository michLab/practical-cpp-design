HOME =../../
include($$HOME/common.pri) 
TEMPLATE = lib 
TARGET = pdCalcBackend 
DEPENDPATH += .
INCLUDEPATH += . $$HOME/src
unix:DESTDIR = $$HOME/lib

HEADERS += Stack.h

SOURCES += Stack.cpp

unix:LIBS += -ldl
