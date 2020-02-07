TEMPLATE = subdirs
CONFIG += ordered
CONFIG -= flat
# Directories
SUBDIRS += \
	src \
	qironplugin
           	         
greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
    message(Qt5 = $$QT)
}
else {
    message(Qt4 = $$QT)
}
