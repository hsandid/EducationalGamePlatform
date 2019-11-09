#ifndef GAMESCENE_1_H
#define GAMESCENE_1_H

#include "gamescene_1_player.h"
#include "gamescene_1_dice.h"
#include "gamescene_1_ladderSnake.h"
#include <QGraphicsScene>
#include <QWidget>
#include <QtWidgets>
#include <QSound>
#include <QFuture>
#include <QThread>
#include <QtConcurrent/QtConcurrent>
#include <stdlib.h>
#include <time.h>


class gameScene_1 : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit gameScene_1(QObject *parent = 0);

    //Sidebar
     QGraphicsTextItem *text;
     QGraphicsTextItem *text2;
     QGraphicsTextItem *text3;
     QPushButton *rolldice;
     QPushButton *pickdice1;
     QPushButton *pickdice2;
     QPushButton *backtomenu;


    //Players item
    gameScene_1_player *player1;
    gameScene_1_player *player2;

    //Dice item
    gameScene_1_dice *dice1;
    gameScene_1_dice *dice2;

    //LadderSnake Gen + Brush
    gamescene_1_ladderSnake *ladderSnake;
    QGraphicsRectItem* square;

    //LadderSnake positions
    int *ladderPos;
    int *snakePos;

    //Logic items
    bool *firstRoll;
    bool *playerTurn;
    bool *sidePick;
    bool *winState;

    //CPU or Human Player
    bool *CPU;







signals:

public slots:
void generateBoard();
void selectLeft();
void selectRight();
void diceRoll();
void checkSnakeLadder();
void winCondition();
void movePlayer();
void movePlayerOpp();
void backToMenu();
void loadGame(int posp1,int posp2, bool turn);
};

#endif // GAMESCENE_1_H
