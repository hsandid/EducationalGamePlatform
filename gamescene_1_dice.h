#ifndef GAMESCENE_1_DICE_H
#define GAMESCENE_1_DICE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>
#include <stdlib.h>
#include <time.h>

/**
 *
 * \file gamescene_1_dice.h
 * \brief The gameScene_1_dice class
 */

class gameScene_1_dice : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit gameScene_1_dice(QObject *parent = 0);
    int *id; //!< ID of the dice ( dice1/dice2)
    int *diceVal; //!< int denoting current value of dice

signals:

public slots:
    void update();
    void setup(int value);
};

#endif // GAMESCENE_1_DICE_H
