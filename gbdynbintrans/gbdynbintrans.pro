#-------------------------------------------------
#
# Project created by QtCreator 2016-02-11T16:43:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gbdynbintrans
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    aboutdialog.cpp \
    jsoncpp.cpp

HEADERS  += mainwindow.h \
    aboutdialog.h \
    json/json.h \
    json/json-forwards.h

FORMS    += mainwindow.ui \
    aboutdialog.ui
