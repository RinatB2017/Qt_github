#include "widget.h"
#include "treemodel.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);
    //Инициализируем ресурсы:
    Q_INIT_RESOURCE(simpletreemodel);
    //Получаем предустановленное "дерево" в file:
    QFile file(":/default.txt");
    file.open(QIODevice::ReadOnly);
    //Создаем заголовки столбцов:
    QStringList headers;
    headers << tr("Заголовок") << tr("Описание");
    //Загружаем данные в модель:
    TreeModel *model = new TreeModel(headers, file.readAll());
    file.close();
    ui->treeView->setModel(model);
    for (int column = 0; column < model->columnCount(); ++column) ui->treeView->resizeColumnToContents(column);

    //Осталось соединить сигналы со слотами:
    connect(ui->treeView->selectionModel(),SIGNAL(selectionChanged(const QItemSelection&,const QItemSelection&)),
            this, SLOT(updateActions(const QItemSelection&,const QItemSelection&)));
    connect(ui->insertRowAction,SIGNAL(clicked()),this,SLOT(insertRow()));
    connect(ui->insertColumnAction,SIGNAL(clicked()),this,SLOT(insertColumn()));
    connect(ui->removeRowAction,SIGNAL(clicked()),this,SLOT(removeRow()));
    connect(ui->removeColumnAction,SIGNAL(clicked()),this,SLOT(removeColumn()));
    connect(ui->insertChildAction,SIGNAL(clicked()),this,SLOT(insertChild()));
    //и обновить состояние кнопок:
    updateActions();
}

void Widget::insertChild() {
    //Получаем модельный индекс и модель элемента:
    QModelIndex index = ui->treeView->selectionModel()->currentIndex();
    QAbstractItemModel *model = ui->treeView->model();
    //Вставляем данные:
    if (model->columnCount(index) == 0) {
        if (!model->insertColumn(0, index)) return;
    }
    if (!model->insertRow(0, index)) return;
    //Инициализируем их:
    for (int column = 0; column < model->columnCount(index); ++column) {
        QModelIndex child = model->index(0, column, index);
        model->setData(child, QVariant("Данные"), Qt::EditRole);
        if (!model->headerData(column, Qt::Horizontal).isValid())
            model->setHeaderData(column, Qt::Horizontal, QVariant("Столбец"), Qt::EditRole);
    }
    //Выбираем вставленный узел:
    ui->treeView->selectionModel()->setCurrentIndex(model->index(0, 0, index),
                                                    QItemSelectionModel::ClearAndSelect);
    //Меняем состояние кнопок:
    updateActions();
}

bool Widget::insertColumn() {
    QAbstractItemModel *model = ui->treeView->model();
    int column = ui->treeView->selectionModel()->currentIndex().column();
    bool changed = model->insertColumn(column + 1);
    if (changed)
        model->setHeaderData(column + 1, Qt::Horizontal, QVariant("Столбец"), Qt::EditRole);
    updateActions();
    return changed;
}

void Widget::insertRow() {
    QModelIndex index = ui->treeView->selectionModel()->currentIndex();
    QAbstractItemModel *model = ui->treeView->model();
    if (!model->insertRow(index.row()+1, index.parent())) return;
    updateActions();
    for (int column = 0; column < model->columnCount(index.parent()); ++column) {
        QModelIndex child = model->index(index.row()+1, column, index.parent());
        model->setData(child, QVariant("Данные"), Qt::EditRole);
    }
}

bool Widget::removeColumn() {
    QAbstractItemModel *model = ui->treeView->model();
    int column = ui->treeView->selectionModel()->currentIndex().column();
    bool changed = model->removeColumn(column); //Удалить столбец для каждого потомка
    if (changed) updateActions();
    return changed;
}

void Widget::removeRow() {
    QModelIndex index = ui->treeView->selectionModel()->currentIndex();
    QAbstractItemModel *model = ui->treeView->model();
    if (model->removeRow(index.row(), index.parent())) updateActions();
}

void Widget::updateActions(const QItemSelection &selected,const QItemSelection &deselected) {
    updateActions();
}

void Widget::updateActions() {
    //Обновим состояние кнопок:
    bool hasSelection = !ui->treeView->selectionModel()->selection().isEmpty();
    ui->removeRowAction->setEnabled(hasSelection);
    ui->removeColumnAction->setEnabled(hasSelection);
    bool hasCurrent = ui->treeView->selectionModel()->currentIndex().isValid();
    ui->insertRowAction->setEnabled(hasCurrent);
    ui->insertColumnAction->setEnabled(hasCurrent);
    //Покажем информацию в заголовке окна:
    if (hasCurrent) {
        ui->treeView->closePersistentEditor(ui->treeView->selectionModel()->currentIndex());
        int row = ui->treeView->selectionModel()->currentIndex().row();
        int column = ui->treeView->selectionModel()->currentIndex().column();
        if (ui->treeView->selectionModel()->currentIndex().parent().isValid())
            this->setWindowTitle(tr("(row,col)=(%1,%2)").arg(row).arg(column));
        else
            this->setWindowTitle(tr("(row,col)=(%1,%2) ВЕРХ").arg(row).arg(column));
    }
}
