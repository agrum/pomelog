#-------------------------------------------------
#
# Project created by QtCreator 2012-12-27T11:42:58
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = pomelog
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = lib

if:CONFIG(release, debug|release): DESTDIR = release
else:CONFIG(debug, debug|release): DESTDIR = debug

HEADERS += \
    pLog.h \
	pLogBehavior.h \
    pLogException.h \
    ../include/pomelog.h

SOURCES += \
    pLog.cpp \
    pLogBehavior.cpp \
    pLogException.cpp
