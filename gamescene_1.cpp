#include "gamescene_1.h"
#include <stdlib.h>
#include <time.h>

gameScene_1::gameScene_1(QObject *parent) :
    QGraphicsScene(parent)
{
    //Settings the background board
    setBackgroundBrush(QBrush(QImage(":/images/default-board.jpg").scaledToHeight(700).scaledToWidth(700)));
    setSceneRect(0,0,700,700);

    //Adding brushes
    square = new QGraphicsRectItem(0,0,69,69);
    square->setBrush(QBrush(Qt::red));
    addItem(square);
    square = new QGraphicsRectItem(70,70,69,69);
    square->setBrush(QBrush(Qt::green));
    addItem(square);
    square = new QGraphicsRectItem(140,140,69,69);
    square->setBrush(QBrush(Qt::red));
    addItem(square);

    //Adding player char
    player1 = new gameScene_1_player();
    player1->setPos(1,635);
    player1->setFlag(QGraphicsItem::ItemIsFocusable);
    addItem(player1);


}

