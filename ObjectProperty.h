#ifndef OBJECTPROPERTY_H
#define OBJECTPROPERTY_H

#include <QHash>
#include <QVariant>
#include <QDebug>

/*! this class does what a QObject deriving class also does but this is the lightweight solution */
class ObjectProperty {
  public:
    /*! constructor */
    ObjectProperty();
    /*! destuctor */
    ~ObjectProperty();
    /*! get a property, init it with  */
    const QVariant getProperty( QString key, QVariant init );
    /*! set a property */
    void setProperty( QString, QVariant );
  public:
    /*! get a property */
    const QVariant getProperty( QString );

  private: // Members
    /*! holds all properties */
    QHash<QString, QVariant> property;
};

#endif // OBJECTPROPERTY_H
