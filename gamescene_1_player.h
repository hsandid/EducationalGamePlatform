#ifndef GAMESCENE_1_PLAYER_H
#define GAMESCENE_1_PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QSound>
#include <QThread>

/**
 *
 * \file gameScene_1_player.h
 * \brief The gameScene_1_player class
 */


class gameScene_1_player : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit gameScene_1_player(QObject *parent = 0);
    QGraphicsScene * parentScene;
    bool *goForward; //!< Bool used in movement logic
    int *id; //!< ID used for player1/player2
    int *position; //!< Used to store player position
    int *newPosition; //!< Used to store player position

signals:

public slots:
void moveInstantaneous();
void setup(int playerid);

};

#endif // GAMESCENE_1_PLAYER_H
