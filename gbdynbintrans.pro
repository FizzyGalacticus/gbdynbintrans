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
    src/registerbank.cpp \
    src/opcodedecoder.cpp \
    src/cpu.cpp \
    src/operand.cpp \
    src/memorybank.cpp \
    src/memoryoperand.cpp \
    src/registeroperand.cpp \
    src/constantoperand.cpp

HEADERS  += src/mainwindow.h \
    src/aboutdialog.h \
    src/json/json.h \
    src/json/json-forwards.h \
    src/registerbank.h \
    src/opcodedecoder.h \
    src/cpu.h \
    src/operand.h \
    src/memorybank.h \
    src/memoryoperand.h \
    src/registeroperand.h \
    src/constantoperand.h

FORMS    += src/mainwindow.ui \
    src/aboutdialog.ui \
    src/registerbank.ui \
    src/opcodedecoder.ui \
    src/cpu.ui \
    src/memorybank.ui

RESOURCES += \
    src/resources.qrc
