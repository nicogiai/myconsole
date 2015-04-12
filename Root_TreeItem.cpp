#include "Root_TreeItem.h"
#include <QDebug>

Root_TreeItem::Root_TreeItem(const QList<QVariant> &data, AbstractTreeItem *parent) :
    AbstractTreeItem(data, parent)
{
    qDebug() << "Root_TreeItem Constructor called";
}

unsigned int Root_TreeItem::getObjectType()
{
    return ROOT;
}
