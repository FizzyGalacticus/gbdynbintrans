#-------------------------------------------------
#
# Project created by QtCreator 2016-02-11T16:43:35
#
#-------------------------------------------------

QT       += core gui
CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gbdynbintrans
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/aboutdialog.cpp \
    src/jsoncpp.cpp \
    src/registerbank.cpp

HEADERS  += src/mainwindow.h \
    src/aboutdialog.h \
    src/json/json.h \
    src/json/json-forwards.h \
    src/registerbank.h

FORMS    += src/mainwindow.ui \
    src/aboutdialog.ui \
    src/registerbank.ui
