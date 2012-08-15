#-------------------------------------------------
#
# Project created by QtCreator 2012-07-20T20:34:36
#
#-------------------------------------------------

QT       += core gui

TARGET = Amiga
TEMPLATE = app


SOURCES += main.cpp\
        amiga.cpp \
    configchipset.cpp \
    configram.cpp \
    configfloppy.cpp \
    configcdrom.cpp \
    configharddisks.cpp \
    configgraphics.cpp \
    configmisc.cpp \
    configtheme.cpp \
    configinput.cpp

HEADERS  += amiga.h \
    configchipset.h \
    configram.h \
    configfloppy.h \
    configcdrom.h \
    configharddisks.h \
    configgraphics.h \
    configmisc.h \
    configtheme.h \
    configinput.h

FORMS    += amiga.ui

RESOURCES += \
    ICO.qrc
