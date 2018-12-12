#include "domitem.h"

DomItem::DomItem(QDomNode& node, int row, DomItem *parent)
    : m_domNode(node),
      m_row(row),
      m_parent(parent)
{
}

DomItem* DomItem::parent()
{
    return m_parent;
}

int DomItem::row()
{
    return m_row;
}

QDomNode DomItem::node() const
{
    return m_domNode;
}

DomItem *DomItem::child(int i)
{
    if(m_children.contains(i))
        return m_children[i];

    if(i >= 0 && i < m_domNode.childNodes().count())
    {
        QDomNode childNode = m_domNode.childNodes().item(i);
        DomItem *childItem = new DomItem(childNode, i, this);
        m_children[i] = childItem;
        return childItem;
    }

    return nullptr;
}

DomItem::~DomItem()
{
    for(QHash<int,DomItem*>::iterator i = m_children.begin(); i != m_children.end(); i++)
        delete i.value();
}
