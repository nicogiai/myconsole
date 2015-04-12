#include "MyGraphicsItem.h"
#include <QDebug>
#include "GraphicsScene.h"
#include <QKeyEvent>

MyGraphicsItem::MyGraphicsItem(QPersistentModelIndex index)
{
    this->index = index;

    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();

}

void MyGraphicsItem::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "MyRect press hkey";

    if( event->key() == Qt::Key_Left) {
        setPos( x()-10, y());
    } else if( event->key() == Qt::Key_Right) {
        setPos( x()+10, y());
    } else if( event->key() == Qt::Key_Up) {
        setPos( x(), y()-10);
    } else if( event->key() == Qt::Key_Down) {
        setPos( x(), y()+10);
    }

    setModelData( scene(), index, pos().x(), customRole::XposRole);
    setModelData( scene(), index, pos().y(), customRole::YposRole);

    //emit dataCha

}

int MyGraphicsItem::type() const {
    return SceneItem_PlayerType;
}

void MyGraphicsItem::updateData() {
    qDebug() << "MyGraphicsItem " << __FUNCTION__;

    if ( scene() == NULL ) {
        qDebug() << "item isn't in any scene, can't query for valid data";
        return;
    }

    //Qt::DisplayRole
    //customRole::XposRole
    int xpos = modelData ( scene(), index, customRole::XposRole ).toInt();
    int ypos = modelData ( scene(), index, customRole::YposRole ).toInt();

    qDebug() << "xpos=" << xpos << "ypos=" << ypos;

    this->setPos(xpos, ypos);
    update();

}
