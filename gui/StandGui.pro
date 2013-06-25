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

HEADERS += \
    views/AbstractSequenceView.h \
    views/ControlCurveView.h \
    views/ControlGridView.h \
    views/AbstractGridView.h \
    utility/Utility.h \
    views/PianoPainter.h \
    views/NoteView.h \
    models/Selection.h \
    views/BeatView.h \
    views/TempoView.h \
    views/AbstractLabelView.h \
    views/SingerView.h \
    views/TrackSelectionView.h \
    views/PianoView.h \
    views/ControlSelectionView.h \
    models/ControlCurveSelection.h \
    views/ControlCurvePainter.h \
    views/AbstractControlPainter.h

SOURCES += \
    views/AbstractSequenceView.cpp \
    views/ControlCurveView.cpp \
    views/ControlGridView.cpp \
    views/AbstractGridView.cpp \
    utility/Utility.cpp \
    views/PianoPainter.cpp \
    views/NoteView.cpp \
    models/Selection.cpp \
    views/BeatView.cpp \
    views/TempoView.cpp \
    views/AbstractLabelView.cpp \
    views/SingerView.cpp \
    views/TrackSelectionView.cpp \
    views/PianoView.cpp \
    views/ControlSelectionView.cpp \
    models/ControlCurveSelection.cpp \
    views/ControlCurvePainter.cpp \
    views/AbstractControlPainter.cpp

