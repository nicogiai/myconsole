#ifndef MYGRAPHICSITEM_H
#define MYGRAPHICSITEM_H

#include <QGraphicsRectItem>

#include <QPersistentModelIndex>
#include <QGraphicsSceneMouseEvent>

#include "AbstractGraphicsItemModelExtension.h"

#include "SceneItemTypes.h"


class MyGraphicsItem : public QGraphicsRectItem, public AbstractGraphicsItemModelExtension
{

public:
    explicit MyGraphicsItem( QPersistentModelIndex index );
    
    /*! used to identify a object by a class of objects, see it's implementation */
    int type() const;

    void keyPressEvent(QKeyEvent* event);

    /*! this member function tracks the following changes:
     **  - itemlabel changes
     **  and is indirectly called by dataChanged() from the Model and
     **  directly called by our GraphicsScene dataChanged handler*/
    void updateData();


    /*! This index is needed to map QModelIndexes to QGraphicsItems. Since we need to
    ** store the QModelIndexe we are enforced to use a QPersistentModelIndex which
    ** implicitly updates if the date in the model changes. That means when you remove
    ** the connection 3 (out of 7 connections) all QPersistentModelIndex (4,5,6,7) are
    ** automatically updated to the new pos: 3,4,5,6 which is very important! */
    QPersistentModelIndex index;
    
};

#endif // MYGRAPHICSITEM_H
