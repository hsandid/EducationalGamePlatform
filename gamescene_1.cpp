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
//    player1 = new gameScene_1_player();
//    player1->setPos(1,635);
//    player1->setFlag(QGraphicsItem::ItemIsFocusable);
//    addItem(player1);



        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this,  SLOT(initDice()));
        timer->start(500);


}

void gameScene_1::initDice()
{
    //Init dice
    dice1 = new gamescene_1_dice();
    dice1->setPos(300,300);
    dice1->setFlag(QGraphicsItem::ItemIsFocusable);

    srand(time(0));
    dice1->init(rand()%6+1);

    addItem(dice1);

    //   while(i<6)
    //   {


    //       dice1=rand()%6+1;

    //       switch(dice1)
    //       {
    //           case 1:
    //           this->changeImage((QPixmap(":/images/dice-one.png")).scaled(30,30));
    //           break;
    //           case 2:
    //           this->changeImage((QPixmap(":/images/dice-two.png")).scaled(30,30));
    //           break;
    //           case 3:
    //           this->changeImage((QPixmap(":/images/dice-three.png")).scaled(30,30));
    //           break;
    //           case 4:
    //           this->changeImage((QPixmap(":/images/dice-four.png")).scaled(30,30));
    //           break;
    //           case 5:
    //           this->changeImage((QPixmap(":/images/dice-five.png")).scaled(30,30));
    //           break;
    //           case 6:
    //           this->changeImage((QPixmap(":/images/dice-six.png")).scaled(30,30));
    //           break;
    //           default:
    //           break;


    //       }

    //       QThread::msleep(500);


    //       i++;
    //   }
}

