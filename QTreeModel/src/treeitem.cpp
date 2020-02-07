#include "treeitem.h"

TreeItem::TreeItem (const QVector<QVariant> &data, TreeItem *parent)
{
    //Конструктору узла нужно передать данные и ссылку на родителя
    m_parentItem = parent;
    m_itemData = data;
}

TreeItem::~TreeItem()
{
    qDeleteAll(m_childItems);
}

/*
 Методы класса служат, по сути, интерфейсом к
 соответствующим методам стандартного класса QVector:
*/

void TreeItem::appendChild(TreeItem *item)
{
    m_childItems.append(item);
    //Добавить узел в список потомков
}

TreeItem *TreeItem::child (int row)
{
    return m_childItems.value(row);
    //По номеру строки выбрать нужного потомка из списка
}

int TreeItem::childCount() const
{
    return m_childItems.count();
    //Количество потомков узла = длине списка потомков
}

int TreeItem::columnCount() const
{
    return m_itemData.count();
    //Количество столбцов в узле = длине списка данных узла
}

QVariant TreeItem::data (int column) const
{
    return m_itemData.value(column);
    //Взять данные из нужного столбца
}

TreeItem *TreeItem::parentItem()
{
    return m_parentItem; //Вернуть ссылку на родителя
}

int TreeItem::childNumber() const
{
    //Если есть родитель - найти свой номер в списке его потомков
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));
    return 0; //Иначе вернуть 0
}

/*
 Следующие 4 метода просто управляют контейнерами класса m_childItems и m_itemData,
 предназначенными для хранения данных
*/

bool TreeItem::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > m_childItems.size())
        return false;
    for (int row = 0; row < count; ++row)
    {
        QVector<QVariant> data(columns);
        TreeItem *item = new TreeItem(data, this);
        m_childItems.insert(position, item);
    }
    return true;
}

bool TreeItem::insertColumns(int position, int columns) {
    if (position < 0 || position > m_itemData.size()) return false;
    for (int column = 0; column < columns; ++column) m_itemData.insert(position, QVariant());
    foreach (TreeItem *child, m_childItems) child->insertColumns(position, columns);
    return true;
}

bool TreeItem::removeChildren(int position, int count) {
    if (position < 0 || position + count > m_childItems.size()) return false;
    for (int row = 0; row < count; ++row) delete m_childItems.takeAt(position);
    return true;
}

bool TreeItem::removeColumns(int position, int columns) {
    if (position < 0 || position + columns > m_itemData.size()) return false;
    for (int column = 0; column < columns; ++column) m_itemData.removeAt(position);
    foreach (TreeItem *child, m_childItems) child->removeColumns(position, columns);
    return true;
}

//А этот метод ставит значение value в столбец column элемента:
bool TreeItem::setData(int column, const QVariant &value) {
    if (column < 0 || column >= m_itemData.size()) return false;
    m_itemData[column] = value;
    return true;
}
