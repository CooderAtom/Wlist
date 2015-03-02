#-------------------------------------------------
#
# Project created by QtCreator 2015-02-15T09:51:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WList
TEMPLATE = app


SOURCES += main.cpp\
        wlist.cpp \
    listitem.cpp \
    listarea.cpp

HEADERS  += wlist.h \
    listitem.h \
    listarea.h

FORMS    += wlist.ui \
    listitem.ui \
    listarea.ui
