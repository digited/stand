#-------------------------------------------------
#
# Project created by QtCreator 2013-03-20T01:23:00
#
#-------------------------------------------------

QT       += core gui multimedia

Release:TARGET = StandGui
Debug:TARGET = StandGuid

DESTDIR = ../lib/

TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += libvsq

HEADERS += \
    views/AbstractSequenceView.h

SOURCES += \
    views/AbstractSequenceView.cpp

