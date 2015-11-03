#-------------------------------------------------
#
# Project created by QtCreator 2015-11-03T14:35:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    mkvmerge_wrapper.cpp

HEADERS  += mainwindow.h \
    mkvmerge_wrapper.h \
    task_parameters.h

FORMS    += mainwindow.ui
