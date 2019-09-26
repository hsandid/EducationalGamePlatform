#include "man.h"
#include <QKeyEvent>

basket::basket(QObject *parent) :
    QObject(parent)
{

    setPixmap((QPixmap("garbageman.png")).scaled(300,300));

}

void basket::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Right)
    {
        if (x() < 800)
        {
            setPos(x() + 10, y());
        }
    }
    if (event->key() == Qt::Key_Left)
    {
        if (x() > 0)
        {
            setPos(x() - 10, y());
        }
    }
}
