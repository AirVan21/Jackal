#-------------------------------------------------
#
# Project created by QtCreator 2015-11-03T14:32:15
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = worker
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    ffmpeg_wrapper.cpp

INCLUDEPATH += ../share ../

LIBS += -L../share -lshare

HEADERS += \
    ffmpeg_wrapper.h
