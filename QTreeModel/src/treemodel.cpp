#include "treeitem.h"
#include "treemodel.h"

TreeModel::TreeModel(const QStringList &headers,
                     const QString &data,
                     QObject *parent)
    : QAbstractItemModel(parent)
{
    QVector <QVariant> rootData;
    rootData << "Узел" << "Описание"; //В модели будет 2 столбца
    rootItem = new TreeItem(rootData);
    //Создали корневой элемент
    setupModelData(data.split(QString("\n")), rootItem);
    //Данные о строках модели разделены переводом строки
}

TreeModel::~TreeModel() { delete rootItem; }

int TreeModel::columnCount(const QModelIndex &parent) const {
    return rootItem->columnCount();
}

QVariant TreeModel::data (const QModelIndex &index, int role) const {
    if (!index.isValid()) return QVariant();
    if (role != Qt::DisplayRole  && role != Qt::EditRole) return QVariant();
    TreeItem *item = getItem(index);
    return item->data(index.column());
}

TreeItem *TreeModel::getItem(const QModelIndex &index) const {
    if (index.isValid()) {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if (item) return item;
    }
    return rootItem;
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const {
    if (!index.isValid()) return 0;
    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) return rootItem->data(section);
    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const {
    if (parent.isValid() && parent.column() != 0) return QModelIndex();
    TreeItem *parentItem = getItem(parent);
    TreeItem *childItem = parentItem->child(row);
    if (childItem) return createIndex(row, column, childItem);
    else return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const {
    if (!index.isValid()) return QModelIndex();
    TreeItem *childItem = getItem(index);
    TreeItem *parentItem = childItem->parentItem();
    if (parentItem == rootItem) return QModelIndex();
    return createIndex(parentItem->childNumber(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const {
    TreeItem *parentItem = getItem(parent);
    return parentItem->childCount();
}

void TreeModel::setupModelData(const QStringList &lines, TreeItem *parent) {
    QList<TreeItem*> parents;
    QList<int> indentations;
    parents << parent;
    indentations << 0;
    int number = 0;
    //Ищем первый непробельный символ с номером position
    while (number < lines.count()) {
        int position = 0;
        while (position < lines[number].length()) {
            if (lines[number].at(position) != ' ') break;
            position++;
        }
        //Отрезаем пробельное начало строки
        QString lineData = lines[number].mid(position).trimmed();
        if (!lineData.isEmpty()) {
            //Читаем остальную часть строки, если она есть
            QStringList columnStrings = lineData.split(":::", QString::SkipEmptyParts);
            //Учитываем разделитель столбцов
            QVector <QVariant> columnData; //Список данных столбцов
            for (int column = 0; column < columnStrings.count(); ++column)
                columnData << columnStrings[column];
            if (position > indentations.last()) {
                //Последний потомок текущего родителя теперь будет новым родителем,
                //пока у текущего родителя нет потомков
                if (parents.last()->childCount() > 0) {
                    parents << parents.last()->child(parents.last()->childCount()-1);
                    indentations << position;
                }
            }
            else {
                while (position < indentations.last() && parents.count() > 0) {
                    parents.pop_back();
                    indentations.pop_back();
                }
            }
            //Добавить новый узел в список потомков текущего родителя
            parents.last()->appendChild(new TreeItem(columnData, parents.last()));
        }
        ++number;
    }
}

bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (role != Qt::EditRole) return false;
    TreeItem *item = getItem(index);
    bool result = item->setData(index.column(), value);
    if (result) {
        emit dataChanged(index, index);
    }
    return result;
}

bool TreeModel::setHeaderData(int section, Qt::Orientation orientation,
                              const QVariant &value, int role) {
    if (role != Qt::EditRole || orientation != Qt::Horizontal) return false;
    bool result = rootItem->setData(section, value);
    if (result) {
        emit headerDataChanged(orientation, section, section);
    }
    return result;
}

bool TreeModel::insertColumns(int position, int columns, const QModelIndex &parent) {
    bool success;
    beginInsertColumns(parent, position, position + columns - 1);
    success = rootItem->insertColumns(position, columns);
    endInsertColumns();
    return success;
}

bool TreeModel::insertRows(int position, int rows, const QModelIndex &parent) {
    TreeItem *parentItem = getItem(parent);
    bool success;
    beginInsertRows(parent, position, position + rows - 1);
    success = parentItem->insertChildren(position, rows, rootItem->columnCount());
    endInsertRows();
    return success;
}

bool TreeModel::removeColumns(int position, int columns, const QModelIndex &parent) {
    bool success;
    beginRemoveColumns(parent, position, position + columns - 1);
    success = rootItem->removeColumns(position, columns);
    endRemoveColumns();
    if (rootItem->columnCount() == 0) removeRows(0, rowCount());
    return success;
}

bool TreeModel::removeRows(int position, int rows, const QModelIndex &parent) {
    TreeItem *parentItem = getItem(parent);
    bool success = true;
    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildren(position, rows);
    endRemoveRows();
    return success;
}

