TEMPLATE = lib

DESTDIR = ../lib
TARGET = moply

QMAKE_DISTCLEAN = ../lib/libmoply.a

CONFIG += staticlib
CONFIG += debug
#CONFIG += release

INCLUDEPATH += ../include

HEADERS += ../include/moply/embpymol.h \
    ../include/moply/gldrawer.h

SOURCES += embpymol.cpp \
           gldrawer.cpp

QT       += core gui opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

unix:INCLUDEPATH += /usr/include/python2.7
unix:!macx:!symbian: LIBS += -lpython2.7
