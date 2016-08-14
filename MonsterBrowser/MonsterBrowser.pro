#-------------------------------------------------
#
# Project created by QtCreator 2016-08-03T21:13:52
#
#-------------------------------------------------

QT       += core gui
# Handy for testing and debugging purposes.
#CONFIG   += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MonsterBrowser
TEMPLATE = app
DESTDIR = ..


SOURCES += main.cpp\
        mainwindow.cpp \
    serverview.cpp \
    servermodel.cpp \
    colorednames.cpp \
    masterlist.cpp \
    serverdata.cpp \
    maintoolbar.cpp

HEADERS  += mainwindow.h \
    serverview.h \
    servermodel.h \
    colorednames.h \
    masterlist.h \
    serverdata.h \
    maintoolbar.h
