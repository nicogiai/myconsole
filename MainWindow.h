#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractItemModel>
#include <QTreeView>
#include <QTableView>
#include <QGraphicsScene>
#include "GraphicsScene.h"
#include "TreeModel.h"
#include <QGraphicsView>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QAbstractItemModel* model;
    TreeModel* tree_model;

    GraphicsScene* scene;
    QGraphicsView* view;

    QTreeView* treeView;
    QTableView* tableView;

};

#endif // MAINWINDOW_H
