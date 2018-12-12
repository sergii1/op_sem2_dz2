#ifndef DOMITEM_H
#define DOMITEM_H

#include <QtXml>
#include <QHash>

class DomItem
{
public:
    DomItem(QDomNode &node, int row, DomItem *parent = 0);
    ~DomItem();
    DomItem *child(int i);
    DomItem* parent();
    QDomNode node() const;
    int row();

private:
    QDomNode m_domNode;
    QHash<int, DomItem*> m_children;
    DomItem *m_parent;
    int m_row;
};

#endif // DOMITEM_H
