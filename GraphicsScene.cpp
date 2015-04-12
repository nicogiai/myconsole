#include "GraphicsScene.h"
#include <QKeyEvent>
#include <QDebug>

GraphicsScene::GraphicsScene(TreeModel *model, QObject *parent) :
    QGraphicsScene(parent)
{
    this->m_model = model;

}

/// this wrapper function is here to enable all QGraphicsItems to query for data
/// this is handy since all important querying can now be done from within the item,
/// and creates true object encapsulation
QVariant GraphicsScene::data ( const QModelIndex &index, int role ) const
{
    return this->m_model->data ( index, role );
}

/// this wrapper function is here to enable all QGraphicsItems to set data
bool GraphicsScene::setData ( const QModelIndex & index, const QVariant & value, int role )
{
    return this->m_model->setData ( index, value, role );
}

void GraphicsScene::updateNode ( QPersistentModelIndex item )
{
    qDebug() << "updateNode( QPersistentModelIndex item )";
    updateNode ( modelToSceenIndex ( item ) );
}

void GraphicsScene::updateNode ( QGraphicsItem* item )
{
    qDebug() << "updateNode( QGraphicsItem* item )";


    if ( item == NULL ) {
        qDebug() << __FUNCTION__ << " " << __LINE__ << "Warning, something is going wrong";
        return;
    }
    ( ( MyGraphicsItem * ) item )->updateData();

}

QGraphicsItem *GraphicsScene::playerInserted(QPersistentModelIndex item)
{
    qDebug() << __FUNCTION__;
    MyGraphicsItem* node = new MyGraphicsItem ( item );
    addItem ( node );

    node->setRect(0,0,100,100); //mal! hay que obetenerlo del modelo

    //node->setPos ( model->data ( item, customRole::PosRole ).toPoint() );
    updateNode ( node );

    return node;
}

QGraphicsItem* GraphicsScene::modelToSceenIndex ( QPersistentModelIndex index )
{
    QList<QGraphicsItem *> m_list = items();
    qDebug() << "=== searching in: " << m_list.size() << " items ====";
    qDebug() << " searching for: " << index.row() <<  " " << index.column() << " row/column";

    for ( int i = 0; i < m_list.size(); ++i ) {
        if ( m_list[i]->type() == SceneItem_PlayerType ) {
            if ( compareIndexes ( ( ( MyGraphicsItem * ) m_list[i] )->index, index ) ) {
         qDebug() << "node found";
                return m_list[i];
            }
        }

    }
    qDebug() << "FATAL: failed to modify the item, since the QGraphicsScene equivalent to the given QPersistentModelIndex wasn't found, exiting";
    exit ( 1 );

    return NULL;
}

bool GraphicsScene::compareIndexes ( const QPersistentModelIndex & a, const QPersistentModelIndex & b ) {
    if ( a.row() != b.row() )
        return false;
    if ( a.internalPointer() != b.internalPointer() )
        return false;
    return true;
}

/*
** in qt 4.4 we have clear() as well but we won't use it since we have to
** remove all connections first and then all nodes. removing a node while it still
** has references (in/out connections) will result in a error since we need to
** have that error for debugging of other data-structure errors.
**
** behaviour can be changed later if appreciated
*/
void GraphicsScene::clearScene() {

    qDebug() << __FUNCTION__;

//   foreach( QGraphicsItem* i, items() ) {
//     QString o;
//     switch(i->type()) {
//       case  SceneItem_NodeType:
//         o="SceneItem_NodeType";
//         break;
//       case  SceneItem_ConnectionType:
//         o="SceneItem_ConnectionType";
//         break;
//       case  SceneItem_ConnectionHandleType:
//         o="SceneItem_ConnectionHandleType";
//         break;
//       case  SceneItem_LabelEditorType:
//         o="SceneItem_LabelEditorType";
//         break;
//     }
//     qDebug() << "item: " << (unsigned int)i << " type::" << o;
//   }

    /*
    QVector<QGraphicsItem*> connections;
    QVector<QGraphicsItem*> nodes;

    qDebug() << " ======= " << items().size() << " items to delete ========== ";
    foreach ( QGraphicsItem* i, items() ) {
        if ( i->type() == SceneItem_ConnectionType ) {
            connections.push_back ( i );
        }
        if ( i->type() == SceneItem_NodeType ) {
            nodes.push_back ( i );
        }
    }
    foreach ( QGraphicsItem* i, connections )
    delete i;
    foreach ( QGraphicsItem* i, nodes )
    delete i;
    if ( items().size() ) {
        //FIXME this should never happen, sleep(10) should be replaced by exit(0), and Warning by FATAL ERROR
        qDebug() << "Warning: we still got items on this scene while there should not be any, exiting!";
        exit(1);
    }
    */
}

void GraphicsScene::keyPressEvent ( QKeyEvent * keyEvent )
{

    qDebug() << "GraphicsScene press hkey";

    if ( focusItem() != NULL ) {
        QGraphicsScene::keyPressEvent ( keyEvent );
        return;
    }


}
