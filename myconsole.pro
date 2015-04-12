#-------------------------------------------------
#
# Project created by QtCreator 2015-04-08T17:33:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myconsole
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    ItemView.cpp \
    AbstractTreeItem.cpp \
    Root_TreeItem.cpp \
    TreeModel.cpp \
    GraphicsScene.cpp \
    PlayerTreeItem.cpp \
    AbstractGraphicsItemModelExtension.cpp \
    MyGraphicsItem.cpp \
    ObjectProperty.cpp

HEADERS  += MainWindow.h \
    ItemView.h \
    AbstractTreeItem.h \
    Root_TreeItem.h \
    TreeModel.h \
    GraphicsScene.h \
    PlayerTreeItem.h \
    AbstractGraphicsItemModelExtension.h \
    MyGraphicsItem.h \
    SceneItemTypes.h \
    ObjectProperty.h
