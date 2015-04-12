#include "ItemView.h"
#include <QDebug>

ItemView::ItemView(QGraphicsView* view, GraphicsScene* scene, QAbstractItemModel *model, QWidget * parent) :
    QAbstractItemView(parent)
{
    connect ( scene, SIGNAL ( reset() ), this, SLOT ( reset() ) );
    connect ( this, SIGNAL ( clearScene() ), scene, SLOT ( clearScene() ) );

    this->view = view;
    this->scene = scene;
    this->model = model;

    setModel ( model );
    view->setScene ( scene );

}

void ItemView::reset() {
    qDebug() << __PRETTY_FUNCTION__;

    emit clearScene();

    init();
}

void ItemView::init()
{
    qDebug() << __PRETTY_FUNCTION__;

    for ( int i = 0; i < model->rowCount ( QModelIndex() ); ++i )
    {

        qDebug() << "adding node i =" << i;
        QModelIndex item = model->index ( i, 0, QModelIndex() );

        scene->playerInserted ( QPersistentModelIndex ( item ) );
    }
    qDebug() << __FUNCTION__ << "END";
}

QRect ItemView::visualRect ( const QModelIndex &/*index*/ ) const {
    return QRect() /*view->rect()*/;
}

void ItemView::scrollTo ( const QModelIndex &/*index*/, ScrollHint /*hint*/ ) {

}

QModelIndex ItemView::indexAt ( const QPoint &/*point*/ ) const {
    return QModelIndex();
}

QModelIndex ItemView::moveCursor ( CursorAction /*cursorAction*/, Qt::KeyboardModifiers /*modifiers*/ ) {
    return QModelIndex();
}


int ItemView::horizontalOffset() const {
    return 0;
}

int ItemView::verticalOffset() const {
    return 0;
}

bool ItemView::isIndexHidden ( const QModelIndex &/*index*/ ) const {
    return false;
}

void ItemView::setSelection ( const QRect &/*rect*/, QItemSelectionModel::SelectionFlags /*command*/ ) {

}

QRegion ItemView::visualRegionForSelection ( const QItemSelection &/*selection*/ ) const {
    return QRegion();
}

void ItemView::rowsInserted ( const QModelIndex & parent, int start, int end ) {
    qDebug() << "rowsInserted in ItemView called: need to insert " << end - start + 1 << " item(s).";
    /*
    for ( int i = start; i <= end; ++i ) {
        QModelIndex item = model->index ( i, 0, parent );
        if ( model->data ( item, customRole::TypeRole ).toInt() == ViewTreeItemType::NODE )
            scene->nodeInserted ( QPersistentModelIndex ( item ) );
        else if ( model->data ( item, customRole::TypeRole ).toInt() == ViewTreeItemType::NODE_CONNECTION )
            scene->connectionInserted ( QPersistentModelIndex ( item ) );
    }
    */
}

void ItemView::rowsAboutToBeRemoved ( const QModelIndex & parent, int start, int end ) {
    qDebug() << "rowsAboutToBeRemoved in ItemView called: need to remove " << end-start+1 << " item(s).";
    /*
    for ( int i = start; i <= end; ++i ) {
        QModelIndex item = model->index ( i, 0, parent );
        if ( model->data ( item, customRole::TypeRole ).toInt() == ViewTreeItemType::NODE )
            scene->nodeRemoved ( QPersistentModelIndex ( item ) );
        else if ( model->data ( item, customRole::TypeRole ).toInt() == ViewTreeItemType::NODE_CONNECTION )
            scene->connectionRemoved ( QPersistentModelIndex ( item ) );
    }
    */
}

void ItemView::dataChanged ( const QModelIndex & topLeft, const QModelIndex & bottomRight ) {
    qDebug() << __FUNCTION__;

    QModelIndex tmpIndex = topLeft;

    do {
        qDebug() << "dataChanged is now called()";

        switch ( model->data ( tmpIndex, customRole::TypeRole ).toInt() ) {

        case ViewTreeItemType::NODE:
//        qDebug() << __FUNCTION__ << "Node modification";
            scene->updateNode ( QPersistentModelIndex ( tmpIndex ) );
            break;

        default:
            qDebug() << __PRETTY_FUNCTION__ << " didn't understand what i should be doing";
            exit ( 0 );
        }
        if ( tmpIndex == bottomRight )
            break;
        tmpIndex = traverseTroughIndexes ( tmpIndex );

    } while ( tmpIndex.isValid() );
}

/*!
** This algorithm traverses trough the QModelIndex hierarchy
**  topleft -- itemA -- connection1
**             \---- -- connection2       given the topLeft item it returns itemA
**          -- itemB                      given itemA it returns connection1
**             \---- -- connection1       given connection1 it returns itemB
**          -- itemC                      ...
**          -- itemD (bottomRight)        and so on
**             \---- -- connection1
**             \---- -- connection2     <- given this last item, it returns QModelIndex()
*/
QModelIndex ItemView::traverseTroughIndexes ( QModelIndex index )
{
//   qDebug() << "  " << index.row() << " ";
    // 1. dive deep into the structure until we found the bottom (not bottomRight)
    QModelIndex childIndex = model->index ( 0,0,index );

//   qDebug() << "step a";
    if ( childIndex.isValid() )
        return childIndex;

    // 2. now traverse all elements in the lowest hierarchy
    QModelIndex tmpIndex = model->index ( index.row() +1,0,model->parent ( index ) );//index.sibling(index.row()+1,0);

//   qDebug() << "step b";
    if ( tmpIndex.isValid() )
        return tmpIndex;

    // 3. if no more childs are found, return QModelIndex()
//   qDebug() << "step c";
    return QModelIndex();
}
