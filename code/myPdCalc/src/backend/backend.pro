HOME =../../
include($$HOME/common.pri) 
TEMPLATE = lib 
TARGET = pdCalcBackend 
DEPENDPATH += .
INCLUDEPATH += . $$HOME/src
unix:DESTDIR = $$HOME/lib

HEADERS += Stack.h \
    Command.h

SOURCES += Stack.cpp \
    Command.cpp

unix:LIBS += -ldl
