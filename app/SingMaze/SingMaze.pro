#-------------------------------------------------
#
# Project created by QtCreator 2013-08-24T23:37:04
#
#-------------------------------------------------

QT       += core gui multimedia

INCLUDEPATH += ../../core/
DEPENDPATH += ../../lib/

Release:LIBS += ../../lib/stand.lib
Release:PRE_TARGETDEPS += ../../lib/stand.lib
Debug:LIBS += ../../lib/standd.lib
Debug:PRE_TARGETDEPS += ../../lib/standd.lib

TARGET = SingMaze
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp\
        SingMazeMain.cpp \
    models/MazeProject.cpp \
    models/TimeMapModel.cpp \
    models/MazeBuffer.cpp

HEADERS  += SingMazeMain.h \
    models/MazeProject.h \
    models/TimeMapModel.h \
    models/MazeBuffer.h

FORMS    += SingMazeMain.ui
