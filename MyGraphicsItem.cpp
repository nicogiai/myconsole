#include "MyGraphicsItem.h"
#include <QDebug>
#include "GraphicsScene.h"
#include <QKeyEvent>
#include <QDebug>

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
        setModelData( scene(), index, x(), customRole::XposRole);
    } else if( event->key() == Qt::Key_Right) {
        setPos( x()+10, y());
        setModelData( scene(), index, x(), customRole::XposRole);
    } else if( event->key() == Qt::Key_Up) {
        setPos( x(), y()-10);      
        setModelData( scene(), index, y(), customRole::YposRole);
    } else if( event->key() == Qt::Key_Down) {
        setPos( x(), y()+10);  
        setModelData( scene(), index, y(), customRole::YposRole);
    }

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

void MyGraphicsItem::advance(int phase)
{
    if( phase == 0 )
    {
        //calculate new position
        //qDebug() << "Calculate New pos";

        newpos.setX( modelData ( scene(), index, customRole::XposRole ).toInt() );
        newpos.setY( modelData ( scene(), index, customRole::YposRole ).toInt() );

    } else {
        //change position
        //qDebug() << "New pos?";
        if( newpos != pos() ){
            //qDebug() << "Set New pos";
            setPos(newpos);
        }
    }
}
