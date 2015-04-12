#include "MainWindow.h"
#include <QGridLayout>

#include <QStandardItemModel>
#include <QDirModel>


#include "TreeModel.h"

#include "PlayerTreeItem.h"
#include "Root_TreeItem.h"

#include <QGraphicsRectItem>

#include "ItemView.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    //create model and populate
    QList<QVariant> rootData;
    rootData << "ID" << "Type" << "Xpos" << "YPos";
    Root_TreeItem *root_item = new Root_TreeItem(rootData);

    tree_model = new TreeModel(root_item);

    QList<QVariant> node1Data;

    node1Data << "1" << "1" << "0" << "0";
    PlayerTreeItem* node1 = new PlayerTreeItem( node1Data, root_item );
    node1->setId(1);
    node1->setPos(0,0);

    node1->setProperty("id", 1);
    node1->setProperty("type", 1);
    node1->setProperty("xpos", 0);
    node1->setProperty("ypos", 0);
    root_item->appendChild( node1 );

    QList<QVariant> node2Data;
    node2Data << "2" << "1" << "150" << "50";
    PlayerTreeItem* node2 = new PlayerTreeItem( node2Data, root_item );
    node2->setId(2);
    node2->setPos(150,50);

    node2->setProperty("id", 2);
    node2->setProperty("type", 1);
    node2->setProperty("xpos", 150);
    node2->setProperty("ypos", 150);
    root_item->appendChild( node2 );

    ////////////////////////////////////////////////////////

    QWidget *centralWidget = new QWidget;

    treeView = new QTreeView;
    treeView->setModel(tree_model);

    treeView->resizeColumnToContents(0);

    tableView = new QTableView;
    tableView->setModel(tree_model);


    scene = new GraphicsScene(tree_model);

    // create an item to put into the scene
    //QGraphicsRectItem* rect = new QGraphicsRectItem();
    //rect->setRect(0,0,100,100);
    // add the item to the scene
    //scene->addItem(rect);

    view = new QGraphicsView(scene);

    ItemView* itemView = new ItemView(view, scene, tree_model, this);
    itemView->hide();

    QGridLayout *top_layout = new QGridLayout;
    top_layout->addWidget(treeView, 0, 0);
    top_layout->addWidget(tableView, 0, 1);

    QGridLayout *bottom_layout = new QGridLayout;
    bottom_layout->addWidget(view, 0, 0);

    QVBoxLayout *main_layout = new QVBoxLayout;
    main_layout->addLayout(top_layout);
    main_layout->addLayout(bottom_layout);

    centralWidget->setLayout(main_layout);
    setCentralWidget(centralWidget);

    setWindowTitle(tr("Mi consola"));

}

MainWindow::~MainWindow()
{
    
}
