#-------------------------------------------------
#
# Project created by QtCreator 2012-07-27T18:07:43
#
#-------------------------------------------------
TEMPLATE = app

DESTDIR = ../bin

INCLUDEPATH += ../include
unix:INCLUDEPATH += /usr/include/python2.7

LIBS += -lmoply
unix:!macx:!symbian: LIBS += -lpython2.7

QT       += core gui opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += main.cpp
SOURCES += mainwindow.cpp

HEADERS += mainwindow.h
HEADERS += moply/gldrawer.h

FORMS   += mainwindow.ui

TARGET = playground

#CONFIG += release
CONFIG += debug

DEPENDPATH += ../include/moply
PRE_TARGETDEPS += ../lib/libmoply.a

QMAKE_LIBDIR += ../lib

