#-------------------------------------------------
#
# Project created by QtCreator 2015-11-03T14:35:53
#
#-------------------------------------------------

QT += network

TARGET = share
TEMPLATE = lib
CONFIG += staticlib

QMAKE_CXXFLAGS += -std=c++1y -Wall -Werror -pedantic
QMAKE_CXXFLAGS_DEBUG += -O0
QMAKE_CXXFLAGS_RELEASE += -O2

SOURCES += protocol/message_factory.cpp \
    protocol/socket_wrapper.cpp

HEADERS += protocol/message.h \
    protocol/message_factory.h \
    utils/utils.h \
    protocol/socket_wrapper.h

