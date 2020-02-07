#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QFileSystemModel>
#include <QtGui/QDesktopServices>
#include <QStandardPaths>
#include "tesser.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);    
    QQmlApplicationEngine engine;
    QString p;

    // Workaround for Error: Illegal min or max specification!
    // "Fatal error encountered!" == NULL:Error:Assert failed:in file globaloc.cpp, line 75
    // https://github.com/tesseract-ocr/tesseract/issues/94
    setlocale(LC_NUMERIC, "C");

    qmlRegisterType<tesser>("org.tal.tesser", 1, 0, "TesseractOCR");

    QFileSystemModel *fsm = new QFileSystemModel(&engine);
    p=QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    fsm->setRootPath(p);
    fsm->setResolveSymlinks(true);

    engine.rootContext()->setContextProperty("filePicturesPath", p);
    engine.rootContext()->setContextProperty("fileSystemModel", fsm);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    //tesser *t=new tesser();
    //t->ocr("/home/milang/ocrtest.png");

    return app.exec();
}

