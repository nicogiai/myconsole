#ifndef ABSTRACTTREEITEM_H
#define ABSTRACTTREEITEM_H

#include <QList>
#include <QVariant>

#include "ObjectProperty.h"

/*! TreeItemType /struct */
enum TreeItemType {
    ROOT,
    NODE,
    AIRCRAFT,
    RADAR,
    UNKNOWN
};

class AbstractTreeItem : public ObjectProperty
{
    friend class PlayerTreeItem;
    friend class Root_TreeItem;

public:
    AbstractTreeItem(const QList<QVariant> &data, AbstractTreeItem *parent = 0);
    
    /*! appends a new child to m_childItems, child has to have this as parent already! */
    virtual void appendChild( AbstractTreeItem *child );

    /*! returns AbstractTreeItem* from the m_childItems list with index=row*/
    AbstractTreeItem *child( int row );

    /*! returns the number of childs:
      - 0 no childs
      - >0 child amount
      - <0 error
    */
    int childCount() const;

    /* */
    int columnCount() const;

    QVariant data(int columnt) const;
    bool setData(int column, const QVariant& value);

    /*! returns the m_childItems position offset of this in/from the parent item */
    int row() const;

    /*! returns the parent item
      - only one item doesn't have a parent, that is the AutomateRoot
      - all other items MUST have a valid parent*/
    AbstractTreeItem *parent();

    /*! returns the object type, see deriving classes for details */
    virtual unsigned int getObjectType() = 0;

    /*! returns the id for this item */
    unsigned int getId();

    /*! sets the id for this item */
    void setId(unsigned int id);

    /*! returns m_childItems */
    QList<AbstractTreeItem*> childItems() const;

protected:
    /*! id of this object
      - 0 is default but it's overwritten in the constructor of the deriving class
      - only the AutomateRoot may leave the 0 unchanged! */
    unsigned int ID;

    /*! see TreeItemType
      This variable is used to identify what kind of object we have.*/
    unsigned int objectType;

    QList<QVariant> itemData;

private:
    /*! WARNING: never delete objects as for instance childItems within the destructor
    since this will create inconsistencies between the model and this data structure.
    A better way is to fail with exit(0) since this problem must be handled with great care! */
    //virtual ~AbstractTreeItem();

    /*! This container holds all child items */
    QList<AbstractTreeItem*> m_childItems;

    /*! This parent item is used to traverse the tree upwards. */
    AbstractTreeItem *parentItem;

};

#endif // ABSTRACTTREEITEM_H
