#-------------------------------------------------
#
# Project created by QtCreator 2015-08-26T20:56:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FreeFlow
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gui.cpp \
    selection.cpp \
    pairpoint.cpp

HEADERS  += mainwindow.h \
    gui.h \
    ../build-FreeFlow-Desktop_Qt_5_5_0_GCC_64bit-Debug/ui_mainwindow.h \
    ../build-FreeFlow-Desktop_Qt_5_5_0_GCC_64bit-Debug/ui_GUI.h \
    selection.h \
    ../build-FreeFlow-Desktop_Qt_5_5_0_GCC_64bit-Debug/ui_selection.h \
    pairpoint.h

FORMS    += mainwindow.ui \
    GUI.ui \
    selection.ui
