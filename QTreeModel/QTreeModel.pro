#-------------------------------------------------
#
# Project created by QtCreator 2017-04-28T12:31:56
#
#-------------------------------------------------

QT       += core gui

DEPENDPATH  += \
    $$PWD/src \
    $$PWD/src/ui
INCLUDEPATH = $$DEPENDPATH

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTreeModel
TEMPLATE = app

SOURCES += \
    main.cpp\
    treeitem.cpp \
    treemodel.cpp \
    widget.cpp

HEADERS  += \
    treeitem.h \
    treemodel.h \
    widget.h

FORMS    += widget.ui

RESOURCES += \
    simpletreemodel.qrc

OTHER_FILES +=

VPATH = $$INCLUDEPATH
