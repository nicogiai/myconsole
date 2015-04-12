#include "TreeModel.h"

#include "PlayerTreeItem.h"


TreeModel::TreeModel(AbstractTreeItem *root, QObject *parent) :
    QAbstractItemModel(parent)
{

    this->m_root = root;
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (index.column() == 0 || index.column() == 2 || index.column() == 3)
        return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
    else
        return QAbstractItemModel::flags(index);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role ) const
{
    if( role != Qt::DisplayRole || orientation != Qt::Horizontal )
        return QVariant();

    //return m_root->data(section);

    switch( section )
    {
    case 0:
        if ( role == Qt::DisplayRole )
            return QString( "Id" );
    case 1:
        if ( role == Qt::DisplayRole )
            return QString( "Type" );
    case 2:
        if ( role == Qt::DisplayRole )
            return QString( "Xpos" );
    case 3:
        if ( role == Qt::DisplayRole )
            return QString( "Ypos" );
    default:
        return QVariant();
    }

}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent ) const
{
    AbstractTreeItem *parentObject;

    if( !parent.isValid() )
        parentObject = m_root;
    else
        parentObject = static_cast<AbstractTreeItem*>( parent.internalPointer() );

    if( row >= 0 && row < parentObject->childItems().count() )
        return createIndex( row, column, parentObject->childItems().at( row ) );
    else
        return QModelIndex();
}

int TreeModel::rowCount(const QModelIndex &parent ) const
{
    AbstractTreeItem *parentObject;

    if( !parent.isValid() )
        parentObject = m_root;
    else
        parentObject = static_cast<AbstractTreeItem*>( parent.internalPointer() );

    return parentObject->childCount();
    //return parentObject->children().count();
}

int TreeModel::columnCount(const QModelIndex &parent ) const
{
    return m_root->columnCount();
    //return 4; //mejorar esto
}

QVariant TreeModel::data( const QModelIndex &index, int role) const
{
    if( !index.isValid() )
        return QVariant();

    AbstractTreeItem* n = static_cast<AbstractTreeItem*>( index.internalPointer() );
    PlayerTreeItem* p = static_cast<PlayerTreeItem*>( n );

    if( role == customRole::XposRole ){
        return p->getProperty( "xpos" );
    }

    if( role == customRole::YposRole ){
        return p->getProperty( "ypos" );
    }

    if( role == customRole::TypeRole ){
        return n->getProperty( "type" );
    }

    if( role == Qt::DisplayRole )
    {

        switch ( index.column() ) {
        case 0:
            return n->getProperty( "id" );
        case 1:
            return n->getProperty( "type" );
        case 2:
            return n->getProperty( "xpos" );
        case 3:
            return n->getProperty( "ypos" );
        default:
            break;
        }
    }

 /*
    if( role == Qt::DisplayRole )
    {
        return n->data(index.column());
    }

    if( role == customRole::TypeRole) {
        return n->data(1);
    }

    if ( role == customRole::XposRole ) {
        return n->data(2);
    }

    if ( role == customRole::YposRole ) {
        return n->data(3);
    }
*/
    return QVariant();

}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if( !index.isValid() )
        return QModelIndex();

    AbstractTreeItem *indexObject = static_cast<AbstractTreeItem*>( index.internalPointer() );
    AbstractTreeItem *parentObject = indexObject->parent();

    if( parentObject == m_root )
        return QModelIndex();

    AbstractTreeItem *grandParentObject = parentObject->parent();

    return createIndex( grandParentObject->childItems().indexOf( parentObject ), 0, parentObject );
}

bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    AbstractTreeItem* n = static_cast<AbstractTreeItem*>( index.internalPointer() );
    PlayerTreeItem* p = static_cast<PlayerTreeItem*>( n );

    if ( index.isValid() && role == Qt::EditRole)
    {
        n->setData(index.column(), value);
    }

    if ( index.isValid() && role == customRole::XposRole)
    {
        p->setProperty("xpos", value.toInt());
        emit dataChanged(index, index);
        return true;
    }

    if ( index.isValid() && role == customRole::YposRole)
    {
        p->setProperty("ypos", value.toInt());
        emit dataChanged(index, index);
        return true;
    }

    // getTreeItemType( index ) == NODE_CONNECTION
    if ( index.isValid() && role == Qt::EditRole && index.column() == 2 )
    {
        p->setProperty("xpos", value.toInt());
        emit dataChanged(index, index);
        return true;
    }

    if ( index.isValid() && role == Qt::EditRole && index.column() == 3  )
    {
        p->setProperty("ypos", value.toInt());
        emit dataChanged(index, index);
        return true;
    }

    if ( index.isValid() && role == Qt::EditRole && index.column() == 0 )
    {
        n->setProperty("id", value.toInt());
        emit dataChanged(index, index);
        return true;
    }

    if ( index.isValid() && role == Qt::EditRole)
    {


        //n->setData(index.column(), value);


        /*
        switch( index.column() )
        {
        case 0:
            static_cast<AbstractTreeItem*>( index.internalPointer() )->setId(value.toInt());
            break;
        default:
            return false;
        }
        */

        //the model must let the views know that some data has changed:
        //emit dataChanged(index, index);

        return true;
    }

    return false;
}
