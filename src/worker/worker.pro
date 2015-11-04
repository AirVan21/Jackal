#-------------------------------------------------
#
# Project created by QtCreator 2015-11-03T14:32:15
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = worker
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++1y -Wall -Werror -pedantic
QMAKE_CXXFLAGS_DEBUG += -O0
QMAKE_CXXFLAGS_RELEASE += -O2

SOURCES += main.cpp \
    ffmpeg_wrapper.cpp \
    worker.cpp

INCLUDEPATH += ../share ../

LIBS += -L../share -lshare

HEADERS += \
    ffmpeg_wrapper.h \
    worker.h
