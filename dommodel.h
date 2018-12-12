#ifndef DOMMODEL_H
#define DOMMODEL_H

#include <QAbstractItemModel>
#include <QtXml>
#include "domitem.h"

class DomModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit DomModel(QDomDocument document, QObject* parent = 0);
    ~DomModel();
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

private:
    DomItem *m_root;
};

#endif // DOMMODEL_H
