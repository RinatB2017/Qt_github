# -------------------------------------------------
# Project created by QtCreator 2015-01-03T00:25:16
# -------------------------------------------------
# TODO compat with QT5
QT += \
    core \
    xml

QT -= gui

TEMPLATE    = app
TARGET      = linvert

CONFIG  += console
CONFIG  -= app_bundle

PROGRAMM_PATH  += \
    $$PWD \
    $$PWD/src \
    $$PWD/src/ui
INCLUDEPATH += $$PROGRAMM_PATH
DEPENDPATH  += $$PROGRAMM_PATH

SOURCES += \
    main.cpp \
    linvertapplication.cpp \
    lisourcefile.cpp \
    liuifile.cpp \
    lisourcelist.cpp \
    licppfile.cpp

HEADERS += \
    linvertapplication.h \
    lisourcefile.h \
    liuifile.h \
    lisourcelist.h \
    licppfile.h

VPATH = $$INCLUDEPATH
