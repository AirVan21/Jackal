#-------------------------------------------------
#
# Project created by QtCreator 2015-11-03T14:34:39
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

INCLUDEPATH += ../share

LIBS += -L../share -lshare
