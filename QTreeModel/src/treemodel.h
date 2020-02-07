#ifndef TREEMODEL_H
#define TREEMODEL_H
#include <QAbstractItemModel>
#include <QModelIndex>
#include "treeitem.h"

class TreeModel : public QAbstractItemModel {
    Q_OBJECT
public:
    TreeModel(const QStringList &headers, const QString &data, QObject *parent = 0);
    ~TreeModel();
    /*
  Уточняем заголовки методов правильными ключевыми словами C++:
  const - функция не меняет объект, для которого вызывается
  override - функция переопределяет вирутальный метод базового класса
 */
    QVariant data(const QModelIndex &index, int role) const override;
    //получить данные из модельного индекса index с ролью role
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    //получить флаги выбора
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    //получить данные заголовка
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    //получить модельный индекс по строке и столбцу
    QModelIndex parent(const QModelIndex &index) const override;
    //получить модельный индекс родителя
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    //получить количество строк и столбцов для элемента с заданным модельным индексом
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    //установить данные узла с индексом index в значение value
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value,
                       int role = Qt::EditRole) override;
    //установить данные заголовка столбца
    bool insertColumns(int position, int columns,const QModelIndex &parent = QModelIndex()) override;
    bool removeColumns(int position, int columns, const QModelIndex &parent = QModelIndex()) override;
    bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex()) override;
    //вставка и удаление столбцов и строк
private:
    void setupModelData(const QStringList &lines, TreeItem *parent);
    //внутренний метод для установки данных модели
    TreeItem *getItem(const QModelIndex &index) const;
    //внутренний метод для получения элемента
    TreeItem *rootItem; //ссылка на корневой узел
};
#endif // TREEMODEL_H
