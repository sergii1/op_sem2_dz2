#include "dommodel.h"

DomModel::DomModel(QDomDocument document, QObject *parent) : QAbstractItemModel(parent)
{
    m_root = new DomItem(document, 0);
}

DomModel::~DomModel()
{
    delete m_root;
}

int DomModel::columnCount(const QModelIndex&) const
{
    return 2;
}

QModelIndex DomModel::parent(const QModelIndex &child) const
{
    if (!child.isValid())
        return QModelIndex();

    DomItem *childItem = static_cast<DomItem*>(child.internalPointer());
    DomItem *parentItem = childItem->parent();

    if (!parentItem || parentItem == m_root)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

QModelIndex DomModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    DomItem *m_parent;

    if (!parent.isValid())
        m_parent = m_root;
    else
        m_parent = static_cast<DomItem*>(parent.internalPointer());
    DomItem *childItem = m_parent->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

int DomModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;

    DomItem *m_parent;

    if (!parent.isValid())
        m_parent = m_root;
    else
        m_parent = static_cast<DomItem*>(parent.internalPointer());

    return m_parent->node().childNodes().count();
}

QVariant DomModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    DomItem *item = static_cast<DomItem*>(index.internalPointer());

    if(index.column() == 0)
        return  item->node().toElement().tagName();
    else if(index.column() == 1)
    {
        qDebug() << item->node().toCharacterData().data();
        return item->node().toCharacterData().data();
    }

    return QVariant();
}

QVariant DomModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
             return QVariant();

     if (orientation == Qt::Horizontal) {
         if (section == 0)
                 return tr("XML Tag");
         else if(section == 1)
                 return tr("Value");
         }
     return QVariant();
}
