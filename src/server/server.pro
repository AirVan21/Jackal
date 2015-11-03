#-------------------------------------------------
#
# Project created by QtCreator 2015-11-03T14:34:39
#
#-------------------------------------------------

QT       += core
QT       += network
QT       -= gui
CONFIG   += c++14

TARGET = server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

<<<<<<< Updated upstream
SOURCES += main.cpp

INCLUDEPATH += ../share

LIBS += -L../share -lshare
=======
LIBS += -L../share/ -lshare

SOURCES += main.cpp \
    server.cpp

HEADERS += \
    server.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-share-Desktop_Qt_5_5_1_GCC_64bit-Debug/release/ -lshare
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-share-Desktop_Qt_5_5_1_GCC_64bit-Debug/debug/ -lshare
else:unix: LIBS += -L$$PWD/../build-share-Desktop_Qt_5_5_1_GCC_64bit-Debug/ -lshare

INCLUDEPATH += $$PWD/../build-share-Desktop_Qt_5_5_1_GCC_64bit-Debug
DEPENDPATH += $$PWD/../build-share-Desktop_Qt_5_5_1_GCC_64bit-Debug

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-share-Desktop_Qt_5_5_1_GCC_64bit-Debug/release/libshare.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-share-Desktop_Qt_5_5_1_GCC_64bit-Debug/debug/libshare.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-share-Desktop_Qt_5_5_1_GCC_64bit-Debug/release/share.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-share-Desktop_Qt_5_5_1_GCC_64bit-Debug/debug/share.lib
else:unix: PRE_TARGETDEPS += $$PWD/../build-share-Desktop_Qt_5_5_1_GCC_64bit-Debug/libshare.a
>>>>>>> Stashed changes
