#include "gamescene_1_dice.h"



gamescene_1_dice::gamescene_1_dice(QObject *parent) :
    QObject(parent)
{
//    srand(time(0));

    this->setPixmap((QPixmap(":/images/dice-one.png")).scaled(30,30));
    this->setVisible(true);


    this->setFlag(QGraphicsItem::ItemIsFocusable);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this,  SLOT(destroy()));
    timer->start(500);



}

void gamescene_1_dice::destroy()
{
    scene()->removeItem(this);
    delete this;
    return;
}

void gamescene_1_dice::init(int value)
{
   this->setFocus();





       switch(value)
       {
           case 1:
           this->setPixmap((QPixmap(":/images/dice-one.png")).scaled(30,30));
           break;
           case 2:
           this->setPixmap((QPixmap(":/images/dice-two.png")).scaled(30,30));
           break;
           case 3:
           this->setPixmap((QPixmap(":/images/dice-three.png")).scaled(30,30));
           break;
           case 4:
           this->setPixmap((QPixmap(":/images/dice-four.png")).scaled(30,30));
           break;
           case 5:
           this->setPixmap((QPixmap(":/images/dice-five.png")).scaled(30,30));
           break;
           case 6:
           this->setPixmap((QPixmap(":/images/dice-six.png")).scaled(30,30));
           break;
           default:
           break;
       }






//   this->setVisible(false);
}
