#-------------------------------------------------
#
# Project created by QtCreator 2016-07-03T21:30:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEPENDPATH  += \
    /usr/include/qt5/QtConcurrent \
    $$PWD/src \
    $$PWD/src/ui
INCLUDEPATH = $$DEPENDPATH

TARGET = TesseractGui
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    widget.cpp \
    thread.cpp

HEADERS  += \
    mainwindow.h \
    widget.h \
    thread.h

FORMS    += mainwindow.ui

LIBS += -L/usr/local/lib -ltesseract -llept

DISTFILES += \
    README.txt

VPATH = $$INCLUDEPATH
