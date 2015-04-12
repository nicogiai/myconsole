#ifndef ROOT_TREEITEM_H
#define ROOT_TREEITEM_H

#include "AbstractTreeItem.h"

class Root_TreeItem : public AbstractTreeItem
{

public:
    Root_TreeItem(const QList<QVariant> &data, AbstractTreeItem *parent = 0);

    /*! returns the object type, see deriving classes for details */
    unsigned int getObjectType();
    
};

#endif // ROOT_TREEITEM_H
