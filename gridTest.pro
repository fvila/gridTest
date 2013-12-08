#-------------------------------------------------
#
# Project created by QtCreator 2013-09-27T12:55:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gridTest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        customrubberband.cpp \
        cadview.cpp \
        cadscene.cpp

HEADERS  += mainwindow.h \
    customrubberband.h \
    cadview.h \
    cadscene.h

FORMS    += mainwindow.ui
