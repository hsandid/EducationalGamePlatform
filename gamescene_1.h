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

/**
 *
 * \file gamescene_1.h
 * \brief The gameScene_1 class
 */

class gameScene_1 : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit gameScene_1(QObject *parent = 0);

    //Sidebar
     QGraphicsTextItem *text; //!< Text element in GUI
     QGraphicsTextItem *text2; //!< Text element in GUI
     QGraphicsTextItem *text3; //!< Text element in GUI
     QPushButton *rolldice; //!< Button associated to rolling the dices
     QPushButton *pickdice1; //!< Button associated to pick a dice
     QPushButton *pickdice2; //!< Button associated to pick a dice
     QPushButton *backtomenu; //!< Button associated to going back to menu


    //Players item
    gameScene_1_player *player1; //!< Player 1 entity
    gameScene_1_player *player2;  //!< Player 2 entity

    //Dice item
    gameScene_1_dice *dice1;  //!< Dice 1 entity
    gameScene_1_dice *dice2;  //!< Dice 2 entity

    //LadderSnake Gen + Brush
    gamescene_1_ladderSnake *ladderSnake;  //!< Ladder&Snake entity
    QGraphicsRectItem* square;  //!< Boxes used to denote ladder/snakes

    //LadderSnake positions
    int *ladderPos;  //!< Array used to store Ladder start/end positions
    int *snakePos; //!< Array used to store Snake start/end positions

    //Logic items
    bool *firstRoll; //!< Bool denoting first roll status
    bool *playerTurn; //!< Bool denoting player turn
    bool *sidePick; //!< Bool denoting left/right dice pick
    bool *winState; //!< Bool denoting win state

    //CPU or Human Player
    bool *CPU; //!< Bool denoting CPU adversary / human adversary







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
