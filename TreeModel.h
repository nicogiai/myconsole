#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include "AbstractTreeItem.h"

class AbstractTreeItem;


namespace customRole {
  enum CustomRole {
    IdRole = Qt::UserRole, // UserRole is the first number one can use for selfassigned roles by the Qt-toolkit
    XposRole,
    YposRole,
    TypeRole // used by views to query a QModelIndex for its type [ROOT, NODE .. or whatever]
  };
}

namespace ViewTreeItemType {
  // the idea behind yet another type identifier is that we map the types below via the model to the
  // types defined in AbstractTreeItem.h (see TreeItemType in AbstractTreeItem.h)
  enum TreeItemType {
    ROOT,
    NODE,
    AIRCRAFT,
    RADAR,
    UNKNOWN
  };
}


class TreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit TreeModel(AbstractTreeItem *root, QObject *parent = 0);
    
    Qt::ItemFlags flags( const QModelIndex &index ) const;
    QVariant data( const QModelIndex &index, int role ) const;
    QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
    int rowCount( const QModelIndex &parent = QModelIndex() ) const;
    int columnCount( const QModelIndex &parent = QModelIndex() ) const;
    QModelIndex index( int row, int column, const QModelIndex &parent = QModelIndex() ) const;
    QModelIndex parent( const QModelIndex &index ) const;

    bool setData(const QModelIndex & index, const QVariant & value, int role);

private:
    AbstractTreeItem *m_root;

signals:
    
public slots:
    
};

#endif // TREEMODEL_H
