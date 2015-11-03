#-------------------------------------------------
#
# Project created by QtCreator 2015-11-03T14:34:39
#
#-------------------------------------------------

QT       += core network
QT       -= gui

TARGET = server
CONFIG   += console
CONFIG   -= app_bundle

QMAKE_CXXFLAGS += -std=c++1y -Wall -Werror -pedantic
QMAKE_CXXFLAGS_DEBUG += -O0
QMAKE_CXXFLAGS_RELEASE += -O2

TEMPLATE = app

INCLUDEPATH += ../share

SOURCES += main.cpp \
    server.cpp

HEADERS += \
    server.h

LIBS += -L../share -lshare
