#include <QTimer>
#include "mainscene.h"
#include "rubbish.h"

MainScene::MainScene(QGraphicsScene *parent) :
    QGraphicsScene(parent)
{
    theBasket= new basket();
    addItem(theBasket);
    theBasket->setFlag(basket::ItemIsFocusable);
    theBasket->setFocus();

    theBasket->setPos(200, 300);
    timer= new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1500);
}

void MainScene::update()
{

    Ball *theBall= new Ball();

    addItem(theBall);
    //addItem(new QGraphicsPixmapItem(QPixmap("net.jpeg")));

   // theBall->setRect(0, 0, 10, 20);
    theBall->setPos(rand()%500, 0);
}
