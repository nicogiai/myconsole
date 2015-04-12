#ifndef ABSTRACTGRAPHICSITEMMODELEXTENSION_H
#define ABSTRACTGRAPHICSITEMMODELEXTENSION_H

#include <QPersistentModelIndex>
#include <QGraphicsScene>

/*!
 * this class extends all normal QGraphicsItem(s) with another data/setData function, both yet different
 * class definitions can be used simultaneously since the parameterlist is different.
 *
 * and this is a central place for all items to query the model for data/setData
 */
class AbstractGraphicsItemModelExtension
{
public:
    /*! a wrapper function for all items in the scene, so that they can call data() directly */
    QVariant modelData( QGraphicsScene* scene, const QModelIndex &index, int role ) const;
    /*! a wrapper function for all items in the scene, so that they can call setData() directly */
    bool setModelData( QGraphicsScene* scene, const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );
};

#endif // ABSTRACTGRAPHICSITEMMODELEXTENSION_H
