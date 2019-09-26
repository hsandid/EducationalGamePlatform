#include "rubbish.h"
#include <QTimer>
#include <QGraphicsScene>
//#include <QPixMap>

Ball::Ball(QObject *parent) :
    QObject(parent)
{
    setPixmap((QPixmap("garbage.png")).scaled(100,100));
    timer= new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(100);    

}

void Ball::update()
{
	
	if(!scene()->collidingItems(this).isEmpty())
    {
        scene()->removeItem(this);
        delete this;
	}

    else if (y() + 10 == 600)
    {
        scene()->removeItem(this);
        delete this;
    }
    else{
    setPos(x(), y() + 10);}
}
