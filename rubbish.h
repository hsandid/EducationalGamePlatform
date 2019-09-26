#ifndef BALL_H
#define BALL_H

#include <QObject>
#include <QGraphicsPixmapItem>
//#include <QGraphicsRectItem>
class Ball : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Ball(QObject *parent = 0);
    QTimer* timer;
signals:
    
public slots:
    void update();
};

#endif // BALL_H
