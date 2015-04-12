#include "AbstractGraphicsItemModelExtension.h"
#include "GraphicsScene.h"

QVariant AbstractGraphicsItemModelExtension::modelData(  QGraphicsScene* scene, const QModelIndex &index, int role ) const {
  if (scene == NULL) // might happen if an item is currently not in any scene
    return QVariant();
  GraphicsScene* m_scene = (GraphicsScene*) scene;
//   GraphicsScene* m_scene = static_cast<GraphicsScene*> (scene);
  return m_scene->data( index, role );
}

bool AbstractGraphicsItemModelExtension::setModelData( QGraphicsScene* scene, const QModelIndex & index, const QVariant & value, int role ) {
  if (scene == NULL) // might happen if an item is currently not in any scene
    return false;
  GraphicsScene* m_scene = (GraphicsScene*) scene;
//   GraphicsScene* m_scene = static_cast<GraphicsScene*> (scene);
  return m_scene->setData( index, value, role );
}
