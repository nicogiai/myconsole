#include "AbstractTreeItem.h"
#include <QDebug>

AbstractTreeItem::AbstractTreeItem(const QList<QVariant> &data, AbstractTreeItem *parent)
{
    qDebug() << "AbstractTreeItem Constructor called";
    this->parentItem = parent;
    this->ID = 0;
    this->itemData = data;
}

void AbstractTreeItem::appendChild( AbstractTreeItem *item )
{
  if ( item->parent() != this ) {
    qDebug( "ERROR: you can't add a child to a parent item where \
            the parent of the child doesn't match the parent you want to add it to!" );
  }
  m_childItems.append( item );
}

AbstractTreeItem *AbstractTreeItem::child( int row )
{
  return m_childItems.value( row );
}

int AbstractTreeItem::childCount() const
{
  return m_childItems.count();
}


int AbstractTreeItem::columnCount() const
{
    return itemData.count();
}

QVariant AbstractTreeItem::data(int column) const
{
    return itemData.value(column);
}

bool AbstractTreeItem::setData(int column, const QVariant &value)
{
    //no funca
    QVariant actual = itemData.value(column);
    actual.setValue( value );

    itemData.value(column).setValue(value);

    return true;
}

AbstractTreeItem *AbstractTreeItem::parent()
{
  return parentItem;
}

int AbstractTreeItem::row() const
{
//   qDebug() << (unsigned int) parentItem;
  if ( parentItem )
    return parentItem->m_childItems.indexOf( const_cast<AbstractTreeItem*>( this ) );

  return 0;
}

unsigned int AbstractTreeItem::getId()
{
  return ID;
}

void AbstractTreeItem::setId(unsigned int id)
{
    qDebug() << "AbstractTreeItem " << __FUNCTION__;
    itemData.value(0).setValue(this->ID);
    this->ID = id;

}

QList<AbstractTreeItem*> AbstractTreeItem::childItems() const {
  return m_childItems;
}
