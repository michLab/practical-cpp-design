CONFIG(debug, debug|release): DEFINES += DEBUG
CONFIG(release, debug|release): DEFINES += RELEASE
VERSION = 1.0.0
CONFIG += c++14
unix:DEFINES += POSIX