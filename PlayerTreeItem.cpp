#include "PlayerTreeItem.h"
#include <QDebug>

PlayerTreeItem::PlayerTreeItem(const QList<QVariant> &data, AbstractTreeItem *parent) :
    AbstractTreeItem( data, parent )
{
    qDebug() << "PlayerTreeItem Constructor called";

    this->xpos = 0;
    this->ypos = 0;

}


unsigned int PlayerTreeItem::getObjectType()
{
    return NODE;
}

void PlayerTreeItem::setPos(int x, int y)
{
    this->xpos = x;
    this->ypos = y;
}

void PlayerTreeItem::setId(unsigned int id)
{
    qDebug() << "PlayerTreeItem";
    qDebug() << __FUNCTION__;

}
