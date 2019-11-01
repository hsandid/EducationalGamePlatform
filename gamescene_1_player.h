#ifndef GAMESCENE_1_PLAYER_H
#define GAMESCENE_1_PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>

class gameScene_1_player : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit gameScene_1_player(QObject *parent = 0);
    QGraphicsScene * parentScene;
    QTimer * timer;
    bool *goForward;

signals:

public slots:
void update();

};

#endif // GAMESCENE_1_PLAYER_H
