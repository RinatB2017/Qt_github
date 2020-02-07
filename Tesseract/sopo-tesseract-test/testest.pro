TEMPLATE = app

QT += qml quick widgets

DEPENDPATH  += \
    $$PWD/src
INCLUDEPATH = $$DEPENDPATH

SOURCES += \
    main.cpp \
    tesser.cpp

RESOURCES += src/qml.qrc

LIBS += -ltesseract -llept

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(src/deployment.pri)

HEADERS += \
    tesser.h

VPATH = $$INCLUDEPATH
