#ifndef ITEMVIEW_H
#define ITEMVIEW_H

#include <QAbstractItemView>
#include <QGraphicsView>

#include "GraphicsScene.h"
#include <QAbstractItemModel>


class ItemView : public QAbstractItemView
{
    Q_OBJECT
public:
    explicit ItemView(QGraphicsView* view, GraphicsScene* scene, QAbstractItemModel *model, QWidget * parent = 0);
    
private:
    /*! a QGraphicsScene can have several views in theory, we only have one but that can be extended later */
    QGraphicsView* view;

    /*! we only have one scene which this graphicsView should visualize */
    GraphicsScene* scene;

    /*! we only have one model which this graphicsView should visualize */
    QAbstractItemModel *model;

    /*! this is the rect in which all items lie */
    QRect visualRect( const QModelIndex &index ) const ;

    /*! not used but must be implemented since we inherit from QAbstractItemView */
    void scrollTo( const QModelIndex &index, ScrollHint hint = EnsureVisible ) ;

    /*! not used but must be implemented since we inherit from QAbstractItemView */
    QModelIndex indexAt( const QPoint &point ) const ;

    /*! not used but must be implemented since we inherit from QAbstractItemView */
    QModelIndex moveCursor( CursorAction cursorAction, Qt::KeyboardModifiers modifiers ) ;

    /*! not used but must be implemented since we inherit from QAbstractItemView */
    int horizontalOffset() const ;

    /*! not used but must be implemented since we inherit from QAbstractItemView */
    int verticalOffset() const ;

    /*! not used but must be implemented since we inherit from QAbstractItemView */
    bool isIndexHidden( const QModelIndex &index ) const ;

    /*! not used but must be implemented since we inherit from QAbstractItemView */
    void setSelection( const QRect &rect, QItemSelectionModel::SelectionFlags command ) ;

    /*! not used but must be implemented since we inherit from QAbstractItemView */
    QRegion visualRegionForSelection( const QItemSelection &selection ) const ;

    /*! callback which is called by the model on item insertion operations */
    void rowsInserted( const QModelIndex & parent, int start, int end );

    /*! callback which is called by the model on item removal operations */
    void rowsAboutToBeRemoved( const QModelIndex & parent, int start, int end );

    /*! callback which is called by the model on item change operations */
    void dataChanged( const QModelIndex & , const QModelIndex & );


    /*! helper function to get all items between two items in a hierarchy
     ** we have to check all items between topLeft and bottomRight
     ** let's update all QModelIndex'es in between */
    QModelIndex traverseTroughIndexes( QModelIndex index );

public slots:
    

protected slots:
  /*! in a new view this will query all data to create a layout and to have all items in the scene */
  void init();
  /*! helper function to implement a reset call for a custom view, see implementation */
  void reset();

signals:
  /*! helper signal for reset() call */
  void clearScene();

};

#endif // ITEMVIEW_H
