#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVector>
#include <QVariant>

class TreeItem {
public:
    explicit TreeItem (const QVector<QVariant> &data,
                       TreeItem *parentItem = 0); //Конструктор узла дерева
    ~TreeItem();               //...и деструктор

    void appendChild(TreeItem *child); //Добавить узел-потомок
    TreeItem *child(int row); //Вернуть дочерний элемент
    int childCount() const; //Количество дочерних элементов
    int columnCount() const; //Вернуть количество столбцов элемента
    QVariant data(int column) const; //Вернуть данные указанного столбца
    int childNumber() const; //Вернуть номер строки элемента

    TreeItem *parentItem(); //Вернуть родительский элемент
    bool insertChildren(int position, int count, int columns); //Вставить потомков (строки)
    bool insertColumns(int position, int columns); //Вставить столбцы
    bool removeChildren(int position, int count);  //Удалить потомков
    bool removeColumns(int position, int columns); //Удалить столбцы
    bool setData(int column, const QVariant &value); //Установить данные
private: //Внутреннее представление данных:
    QList <TreeItem*> m_childItems; //Список дочерних элементов
    QVector <QVariant> m_itemData; //Список данных текущего узла
    TreeItem *m_parentItem; //Ссылка на родительский узел
};
#endif // TREEITEM_H
