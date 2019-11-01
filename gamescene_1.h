#ifndef GAMESCENE_1_H
#define GAMESCENE_1_H

#include "gamescene_1_player.h"
#include <QGraphicsScene>

class gameScene_1 : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit gameScene_1(QObject *parent = 0);

    //Brush : Red & Green for use with snakes and ladders points
    QGraphicsRectItem* square;

    //Player 1 item
    gameScene_1_player *player1;




signals:

public slots:

};

#endif // GAMESCENE_1_H
