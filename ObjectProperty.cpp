#include "ObjectProperty.h"

ObjectProperty::ObjectProperty() { }
ObjectProperty::~ObjectProperty() { }

void ObjectProperty::setProperty(QString key, QVariant value) {
  property.insert(key,value);
}

// this is a convenience function, to stop program termination on faults
const QVariant ObjectProperty::getProperty(QString key, QVariant init) {
  if (!property.contains(key)) {
    property.insert(key,init);
  }
  return property.value(key);
}

const QVariant ObjectProperty::getProperty(QString key) {
//   if (!property.contains(key)) {
//     qDebug() << __FILE__ << " " << __FUNCTION__ << " ERROR: getProperty for key " << key << " not found in property space";
//     qDebug() << __FILE__ << " " << __FUNCTION__ << " FIX your code, and try again, exiting now";
//     exit(1);
//   }
  return property.value(key);
}
