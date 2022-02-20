HOME = ../../
include($$HOME/common.pri)
TEMPLATE = lib
TARGET = pdCalcBackendTest
DEPENDPATH += $$HOME/src/backend
INCLUDEPATH += . $$HOME $$HOME/src
unix:DESTDIR = $$HOME/lib

HEADERS += StackTest.h

SOURCES += StackTest.cpp

unix:LIBS += -L$$HOME/lib -lpdCalcUtilities -lpdCalcBackend

QT -= gui core
QT += testlib