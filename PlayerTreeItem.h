#ifndef PLAYERTREEITEM_H
#define PLAYERTREEITEM_H

#include "AbstractTreeItem.h"

class PlayerTreeItem : public AbstractTreeItem
{
public:
    PlayerTreeItem(const QList<QVariant> &data, AbstractTreeItem *parent = 0);

    int xpos;
    int ypos;

    /*! returns the object type, see deriving classes for details */
    unsigned int getObjectType();

    void setPos(int x, int y);

    /*! sets the id for this item */
    void setId(unsigned int id);
};

#endif // PLAYERTREEITEM_H
