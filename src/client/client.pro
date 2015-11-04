
#-------------------------------------------------
#
# Project created by QtCreator 2015-11-03T14:35:53
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++1y -Wall -Werror -pedantic
QMAKE_CXXFLAGS_DEBUG += -O0
QMAKE_CXXFLAGS_RELEASE += -O2

SOURCES += main.cpp\
        mainwindow.cpp \
    mkvmerge_wrapper.cpp \
    client_logic.cpp \
    network_manager.cpp \
    task_parameter.cpp

INCLUDEPATH += ../
HEADERS  += mainwindow.h \
    mkvmerge_wrapper.h \
    client_logic.h \
    task_parameters.h \
    network_manager.h \
    mkvmerge_wrapper.cpp.autosave

FORMS    += mainwindow.ui

LIBS += -L../share -lshare

DISTFILES += \
    client.pro.user
