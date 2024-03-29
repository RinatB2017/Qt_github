#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(w.sizeHint());
    w.show();
    qsrand(QDateTime::currentDateTimeUtc().toMSecsSinceEpoch());
    return a.exec();
}
