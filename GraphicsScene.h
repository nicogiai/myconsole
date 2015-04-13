#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QPersistentModelIndex>
#include <QVariant>
#include <QTimer>


#include "MyGraphicsItem.h"
#include "TreeModel.h"

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphicsScene(TreeModel *model, QObject *parent = 0);
    
    /*! a wrapper function for all items in the scene, so that they can call data() directly */
    QVariant data( const QModelIndex &index, int role ) const;
    /*! a wrapper function for all items in the scene, so that they can call setData() directly */
    bool setData( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );

    /*! callback function which is called from the Model->ItemView->GraphicsScene to notify about changed node(s) */
    void updateNode( QPersistentModelIndex item );
    /*! updates a node based on item pointer */
    void updateNode( QGraphicsItem* item );

//protected:
    /*! callback function which is called from the Model->ItemView->GraphicsScene to notify about new player(s) */
    QGraphicsItem* playerInserted( QPersistentModelIndex item );

private:
    /*! the GraphicsScene visualizes the data of this model */
    TreeModel *m_model;
    QTimer *timer;

    /*! converts a QPersistentModelIndex into a QGraphicsItem
    ** the QGraphicsScene stores all graphical objects and in those objects
    ** we have a QPersistentModelIndex stored. this gives us the possibility of
    ** having several different graphicsViews on the same automate
    **
    ** a general compare function had to be implemented: compareIndexes
    ** since this implementation doesn't use
    ** column BUT columns somehow whxere reported to be different, meaning: a stored index could have column 3
    ** while the treeView would make a difference because the treeView uses the columns to distinguish between
    ** different entries in the hierarchical view (the treeView) where for instance column 3 shows the node name
    ** and column 4 shows the symbol_index of a connection*/
    QGraphicsItem* modelToSceenIndex( QPersistentModelIndex index );

    /*! a custom compare function to only compare fields in a QPersistentModelIndex which matter since
    ** the treeView handles rows/columns in items the GraphicsScene doesn't so we do not need to
    ** compare all the fields */
    bool compareIndexes( const QPersistentModelIndex & a, const QPersistentModelIndex & b );

    /*! we handle all keyboard events here, this is only interrupted when an item got focus */
    void keyPressEvent( QKeyEvent * keyEvent );

signals:
    /*! when a new view pops up this reset() is called to query items from the model */
    void reset();

public slots:

protected slots:
    /*! this is similar to clear() in qt 4.4 but as we need to remove all connections
    ** and then all nodes this is the way we go*/
    void clearScene();
    
};

#endif // GRAPHICSSCENE_H
