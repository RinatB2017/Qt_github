######################################################################
# Automatically generated by qmake (2.01a) ?? ??? 31 01:46:53 2016
######################################################################

TEMPLATE    = app
TARGET      = test

DEPENDPATH  += \
    $$PWD \
    $$PWD/src
INCLUDEPATH = $$DEPENDPATH

unix {
    OBJECTS_DIR = /dev/shm/my_programm/$$TARGET/obj
    MOC_DIR     = /dev/shm/my_programm/$$TARGET/moc
    UI_DIR      = /dev/shm/my_programm/$$TARGET/ui
    RCC_DIR     = /dev/shm/my_programm/$$TARGET/rc
}

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
    message(Qt5 = $$QT)
}
else {
    message(Qt4 = $$QT)
}

HEADERS += mainwindow.h
SOURCES += mainwindow.cpp

SOURCES += main.cpp

VPATH = $$INCLUDEPATH
