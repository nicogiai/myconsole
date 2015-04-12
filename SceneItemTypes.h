#ifndef SCENEITEMTYPES_H
#define SCENEITEMTYPES_H

#include <QGraphicsItem>

/*! a qgraphisscene has different items in it
 ** we use that to distinguish between different object types
 */
enum {
  SceneItem_PlayerType = QGraphicsItem::UserType + 1,
  SceneItem_UnknownType
};

#endif // SCENEITEMTYPES_H
