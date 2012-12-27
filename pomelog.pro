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
DESTDIR = lib

HEADERS += \
    pLog.h \
    pLogBehavior.h \
    include/pomelog.h

SOURCES += \
    pLog.cpp \
    pLogBehavior.cpp
