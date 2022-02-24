HOME = ../../
include($$HOME/common.pri)
TEMPLATE = lib
TARGET = pdCalcUtilitiesTest
DEPENDPATH += $$HOME/src/utilities
INCLUDEPATH += . $$HOME $$HOME/src
unix:DESTDIR = $$HOME/lib

HEADERS += 
SOURCES += 

unix:LIBS += -L$$HOME/lib -lpdCalcUtilities

QT -= gui core
QT += testlib