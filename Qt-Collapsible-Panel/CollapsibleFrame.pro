#-------------------------------------------------
#
# Project created by QtCreator 2012-05-05T15:36:58
#
#-------------------------------------------------

TARGET      = CollapsibleFrame
TEMPLATE    = app

PROGRAMM_PATH  += \
    $$PWD \
    $$PWD/src \
    $$PWD/src/ui \
    $$PWD/images
INCLUDEPATH += $$PROGRAMM_PATH
DEPENDPATH  += $$PROGRAMM_PATH

QT          += core gui

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
    message(Qt5 = $$QT)
}
else {
    message(Qt4 = $$QT)
}

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    collapsibleframe.cpp \
    extendedqlabel.cpp

HEADERS  += \
    mainwindow.h \
    collapsibleframe.h \
    extendedqlabel.h

FORMS    += mainwindow.ui

RESOURCES += \
    $$PWD/images/resources.qrc

VPATH = $$INCLUDEPATH
