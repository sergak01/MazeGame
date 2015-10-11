#-------------------------------------------------
#
# Project created by QtCreator 2015-04-20T17:27:27
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MazeGame
TEMPLATE = app


SOURCES += main.cpp\
        mazemainwindow.cpp \
    mazepainter.cpp \
    mazepainterborder.cpp

HEADERS  += mazemainwindow.h \
    mazepainter.h \
    mazepainterborder.h

FORMS    += mazemainwindow.ui

RESOURCES += \
    side.qrc
