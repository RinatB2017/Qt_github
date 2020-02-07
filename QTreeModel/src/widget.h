#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <QtWidgets>
#include <QFile>
#include <QDir>

namespace Ui { class Widget; }
class Widget : public QWidget {
    Q_OBJECT
    Ui::Widget *ui;
public:
    Widget(QWidget *parent = 0);
    void updateActions(); //слот для обновления состояния кнопок
private slots: //слоты для действий, выполняемых по кнопкам
    void insertChild();
    bool insertColumn();
    void insertRow();
    bool removeColumn();
    void removeRow();
public slots: //для реализации сигнала selectionChanged у QTreeView::selectionModel
    void updateActions(const QItemSelection &,const QItemSelection &);
};
#endif // WIDGET_H
