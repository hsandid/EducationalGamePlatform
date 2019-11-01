#ifndef GAMESCENE_1_DICE_H
#define GAMESCENE_1_DICE_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>
#include <qthread.h>
#include<time.h>
#include<stdlib.h>
class gamescene_1_dice : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit gamescene_1_dice(QObject *parent = 0);
    QTimer * timer;

public slots:
   // void update();
    void init(int value);
    void destroy();
};

#endif // GAMESCENE_1_DICE_H
