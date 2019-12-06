#include "gamescene_1.h"
#include "menuwidget.h"
#include <stdlib.h>
#include <time.h>



/**
 * \file gameScene_1.cpp
 * \brief Contains gameScene_1 class definition
 *
 * Main game scene for Game 1. It is the container for all
 * visual elements and logic for Game 1.
 */

gameScene_1::gameScene_1(QObject *parent) :
    QGraphicsScene(parent)
{
    //Initializing arrays
    snakePos = new int[14];
    ladderPos = new int[12];

    //First Roll state (default:1)
    firstRoll = new bool(false);

    //Playerturn variable (default ::: false:player1, true:player2)
    playerTurn = new bool(false);
    //Button choosed variable (default ::: false:left, true:right)
    sidePick= new bool(false);
    //Win state
    winState= new bool(false);
    //CPU Init
    CPU= new bool(false);

    winner= new bool(false);


    //Settings the background board
    setBackgroundBrush(QBrush(QImage(":/images/default-board.jpg").scaledToHeight(700).scaledToWidth(964)));
    setSceneRect(0,0,964,700);

    //Adding text label
    text = new QGraphicsTextItem("Snakes'n'Ladders");
    text->setPos(705,50);
    text->setScale(2);
    text->setDefaultTextColor(Qt::black);
    addItem(text);

    text2 = new QGraphicsTextItem("Player with the highest die roll begins");
    text2->setPos(701,300);
    text2->setScale(0.95);
    text2->setDefaultTextColor(Qt::black);
    addItem(text2);

    text3 = new QGraphicsTextItem("Player 1 : Left die, Player 2 : Right die");
    text3->setPos(701,320);
    text3->setScale(0.95);
    text3->setDefaultTextColor(Qt::black);
    addItem(text3);

    //Adding buttons
    rolldice = new QPushButton("Roll Dice");
    pickdice1 = new QPushButton("Pick Dice 1");
    pickdice2 = new QPushButton("Pick Dice 2");
    backtomenu = new QPushButton("Menu");
    rolldice->setGeometry(QRect(780, 350, 100, 70));
    pickdice1->setGeometry(QRect(710, 600, 100, 30));
    pickdice2->setGeometry(QRect(850, 600, 100, 30));
    backtomenu->setGeometry(QRect(780, 650, 100, 30));
    pickdice1->setEnabled(false);
    pickdice2->setEnabled(false);
    addWidget(rolldice);
    addWidget(pickdice1);
    addWidget(pickdice2);
    addWidget(backtomenu);

    //Adding dices
    dice1 = new gameScene_1_dice();
    dice1->setup(1);
    dice1->setPos(710,480);
    dice1->setFlag(QGraphicsItem::ItemIsFocusable);
    addItem(dice1);
    dice2 = new gameScene_1_dice();
    dice2->setup(2);
    dice2->setPos(850,480);
    dice2->setFlag(QGraphicsItem::ItemIsFocusable);
    addItem(dice2);

    //Generating the board
    generateBoard();

    //Adding 2 player char
    player1 = new gameScene_1_player();
    player2 = new gameScene_1_player();
    player1->setup(1);
    player2->setup(2);
    player1->setFlag(QGraphicsItem::ItemIsFocusable);
    player2->setFlag(QGraphicsItem::ItemIsFocusable);
    addItem(player1);
    addItem(player2);

    connect(rolldice, SIGNAL(clicked()), this,SLOT(diceRoll()));
    connect(pickdice1, SIGNAL(clicked()), this,SLOT(selectLeft()));
    connect(pickdice2, SIGNAL(clicked()), this,SLOT(selectRight()));
    connect(backtomenu, SIGNAL(clicked()), this,SLOT(backToMenu()));

}


/**
 * @brief gameScene_1::loadGame
 * @param posp1 : player1 position
 * @param posp2 : player2 position
 * @param turn : bool which denotes which player's turn it is
 *
 * Loads existing game, if there is any
 */
void gameScene_1::loadGame(int posp1,int posp2, bool turn)
{
    *firstRoll=true;
    *player1->newPosition=posp1;
    *player2->newPosition=posp2;
    player1->moveInstantaneous();
    player2->moveInstantaneous();

    *playerTurn=turn;
    text3->setOpacity(0);

    if (!*playerTurn)
    {
        text2->setPlainText("Player 1 plays");
    }
    else
    {
        text2->setPlainText("Player 2 plays");
    }
    if(*CPU)
    {
        *playerTurn=false;
        text2->setPlainText("Player 1 plays");
    }



}

/**
 * @brief gameScene_1::backToMenu
 *
 * Go back to main menu
 */
void gameScene_1::backToMenu()
{
//check wincondition

    QFile config("config.json");
    config.open(QFile::ReadOnly | QFile::Text );
    QString userInfo;
    QString userName;
    userInfo = config.readAll();
    config.close();

    QJsonParseError JsonParseError;
    QJsonDocument jsonDoc= QJsonDocument::fromJson(userInfo.toUtf8(),&JsonParseError);
    QJsonObject obj = jsonDoc.object();
    userName = obj["loggedon"].toString();

    if (*firstRoll && *winState && userName!="guest")
    {
        //Add extra text file with contents
        QFile file;
        QString fileContents;
        file.setFileName("userdata.json");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        fileContents = file.readAll();
        file.close();

        QJsonDocument jsonDocTwo= QJsonDocument::fromJson(fileContents.toUtf8());
        QJsonObject objTwo = jsonDocTwo.object();

        QJsonObject myUser = objTwo[userName].toObject();

         myUser.insert(QString("game1_active"),QString("no"));

         QJsonArray win = myUser["game1_win"].toArray();
         if(*winner)
         {
             win.append(QJsonValue(1));
         }
         else
         {
                win.append(QJsonValue(0));
         }


         myUser.insert(QString("game1_win"),QJsonValue(win));

         objTwo.insert(userName,myUser);

         jsonDocTwo.setObject(objTwo);

         file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
         file.write(jsonDocTwo.toJson());
         file.close();

    }
    else if (*firstRoll && !*winState && userName!="guest")
    {
        QFile file;
        QString fileContents;
        file.setFileName("userdata.json");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        fileContents = file.readAll();
        file.close();

        QJsonDocument jsonDocTwo= QJsonDocument::fromJson(fileContents.toUtf8());
        QJsonObject objTwo = jsonDocTwo.object();

        QJsonObject myUser = objTwo[userName].toObject();
        myUser.insert(QString("game1_active"),QString("yes"));
        myUser.insert(QString("p1pos"),*player1->position);
        myUser.insert(QString("p2pos"),*player2->position);
        if(!*playerTurn)
        {
            myUser.insert(QString("turn"),QString("p1"));
        }
        else
        {
            myUser.insert(QString("turn"),QString("p2"));
        }
        if(*CPU)
        {
            myUser.insert(QString("cpu"),QString("true"));
        }
        else
        {
            myUser.insert(QString("cpu"),QString("false"));
        }



        objTwo.insert(userName,myUser);
        jsonDocTwo.setObject(objTwo);

        file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
        file.write(jsonDocTwo.toJson());
        file.close();
    }

    menuWidget *menu = new menuWidget();
    menu->show();
    QList<QGraphicsView *> views = this->views();
    for (int i=0;i<views.size();i++)
    {
        views.at(i)->close();
        views.at(i)->deleteLater();
    }

    this->deleteLater();


}

/**
 * @brief gameScene_1::movePlayer
 *
 * Move player after a dice roll
 */
void gameScene_1::movePlayer()
{
    *player1->newPosition =   *player1->position + *dice1->diceVal;
    *player2->newPosition =   *player2->position + *dice2->diceVal;

    if (*player1->newPosition>100)
    {
        int tempPos = *player1->newPosition-100;
        tempPos = 100-tempPos;
        *player1->newPosition = 100;
        player1->moveInstantaneous();
        *player1->newPosition = tempPos;
        player1->moveInstantaneous();


    }
    else
    {
        player1->moveInstantaneous();

    }

    if (*player2->newPosition>100)
    {
        int tempPos = *player2->newPosition-100;
        tempPos = 100-tempPos;
        *player2->newPosition = 100;
        player2->moveInstantaneous();
        *player2->newPosition = tempPos;
        player2->moveInstantaneous();


    }
    else
    {
        player2->moveInstantaneous();
    }

}

/**
 * @brief gameScene_1::movePlayerOpp
 *
 * Move player after a dice roll
 */
void gameScene_1::movePlayerOpp()
{
    *player1->newPosition =   *player1->position + *dice2->diceVal;
    *player2->newPosition =   *player2->position + *dice1->diceVal;

    if (*player1->newPosition>100)
    {
        int tempPos = *player1->newPosition-100;
        tempPos = 100-tempPos;
        *player1->newPosition = 100;
        player1->moveInstantaneous();
        *player1->newPosition = tempPos;
        player1->moveInstantaneous();


    }
    else
    {
        player1->moveInstantaneous();

    }

    if (*player2->newPosition>100)
    {
        int tempPos = *player2->newPosition-100;
        tempPos = 100-tempPos;
        *player2->newPosition = 100;
        player2->moveInstantaneous();
        *player2->newPosition = tempPos;
        player2->moveInstantaneous();


    }
    else
    {
        player2->moveInstantaneous();
    }

}

/**
 * @brief gameScene_1::diceRoll
 *
 * Roll dice & implements game loop
 */
void gameScene_1::diceRoll()
{
    QSound::play(":/sound_effects/diceroll.wav");
    dice1->update();
    dice2->update();

    // First roll loop

    if(!*firstRoll)
    {
    if (*dice1->diceVal>*dice2->diceVal)
    {
        *playerTurn=false;
        *firstRoll=true;
        text2->setPlainText("Player 1 begins! (Black chip)");
        text3->setOpacity(0);


    }
    else if (*dice1->diceVal<*dice2->diceVal)
    {
        *playerTurn=true;
        *firstRoll=true;
        text2->setPlainText("Player 2 begins! (Red chip)");
        text3->setOpacity(0);


    }
    else if (*dice1->diceVal==*dice2->diceVal)
    {
        text2->setPlainText("Same die value, roll again!");
        text3->setOpacity(0);

    }
    }
    else if (*dice1->diceVal==*dice2->diceVal)
    {




            movePlayer();

            checkSnakeLadder();

         winCondition();







            if (!*playerTurn)
            {
                text2->setPlainText("Same value! Player 1 plays again");
            }
            else
            {
                text2->setPlainText("Same value! Player 2 plays again");
            }


    }
    else
    {

        if (!*playerTurn)
        {
            text2->setPlainText("Player 1 must select die");
        }
        else
        {
            text2->setPlainText("Player 2 must select die");
        }

        rolldice->setEnabled(false);
        pickdice1->setEnabled(true);
        pickdice2->setEnabled(true);

        //Init CPU selection
        if(!*winState && *playerTurn && *CPU)
        {
            srand(time(NULL));
            int value;
            value = rand()%2;
            if(value==0)
            {
                selectLeft();
            }
            else
            {
                selectRight();
            }
        }


    }


}

/**
 * @brief gameScene_1::winCondition
 *
 * Check if the win condition ( player reaches case 100) is satisfied
 */
void gameScene_1::winCondition()
{

    if (*player1->position==100)
    {
         text2->setPlainText("Player 1 wins the game");
         *winner=false;
         rolldice->setEnabled(false);
         pickdice1->setEnabled(false);
         pickdice2->setEnabled(false);
         *winState=true;
    }
    if (*player2->position==100)
    {
            text2->setPlainText("Player 2 wins the game");
            *winner=true;
            rolldice->setEnabled(false);
            pickdice1->setEnabled(false);
            pickdice2->setEnabled(false);
            *winState=true;
    }




}

/**
 * @brief gameScene_1::selectLeft
 *
 * This function is executed when the player selects the left dice
 */
void gameScene_1::selectLeft()
{
    pickdice1->setEnabled(false);
    pickdice2->setEnabled(false);
    *sidePick=false;
    text2->setPlainText("Please Wait");

    if (!*playerTurn)
    {
        movePlayer();

        checkSnakeLadder();

        text2->setPlainText("Player 2's turn now (Red chip)");
    }
    else
    {
        //Init CPU selection
       movePlayerOpp();
        checkSnakeLadder();

        text2->setPlainText("Player 1's turn now (Black chip)");
    }

    winCondition();



    *playerTurn = !*playerTurn;

    if (!*winState)
    {
         rolldice->setEnabled(true);
    }

    if (!*winState &&*playerTurn && *CPU)
    {
        diceRoll();
    }


}
/**
 * @brief gameScene_1::selectRight
 *
 * This function is executed when the player selects the right dice
 */
void gameScene_1::selectRight()
{
    pickdice1->setEnabled(false);
    pickdice2->setEnabled(false);
    *sidePick=true;

    if (!*playerTurn)
    {
        movePlayerOpp();

        checkSnakeLadder();

        text2->setPlainText("Player 2's turn now (Red chip)");

    }
    else
    {
        movePlayer();

        checkSnakeLadder();

        text2->setPlainText("Player 1's turn now (Black chip)");

    }

    //Check for win condition
    winCondition();


     *playerTurn = !*playerTurn;
      if (!*winState)
      {
           rolldice->setEnabled(true);
      }

      if (!*winState && *playerTurn && *CPU)
      {
          diceRoll();
      }
}

/**
 * @brief gameScene_1::generateBoard
 *
 * Generate board dynamically ( add snakes/ladders) from a text file
 */
void gameScene_1::generateBoard()
{

    QFile file(":/json/boarddata.json");
    QString fileContents;
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    fileContents = file.readAll();
    file.close();

    QJsonDocument jsonDoc= QJsonDocument::fromJson(fileContents.toUtf8());
    QJsonObject obj = jsonDoc.object();



    QJsonArray snakeInfo = obj["snakes"].toArray();
    for (int i=0;i<14;i++)
    {
        snakePos[i]=snakeInfo[i].toInt();
    }

    QJsonArray ladderInfo = obj["ladders"].toArray();
    for (int i=0;i<12;i++)
    {
        ladderPos[i]=ladderInfo[i].toInt();
    }

    ladderSnake = new gamescene_1_ladderSnake();

    //Setting ladder pictures and associated green boxes
    for (int i=0;i<6;i=i+2)
    {
            int tempXBox=ladderSnake->getXYcase(ladderPos[i],0)-35;
            int tempYBox=ladderSnake->getXYcase(ladderPos[i],1)-35;
            square = new QGraphicsRectItem(tempXBox,tempYBox,69,69);
            square->setBrush(QBrush(Qt::green));
            square->setOpacity(0.5);
            addItem(square);
            ladderSnake = new gamescene_1_ladderSnake();
            ladderSnake->initLadder(0,ladderPos[i],ladderPos[i+1]);
            ladderSnake->setFlag(QGraphicsItem::ItemIsFocusable);
            addItem(ladderSnake);



    }
    for (int i=6;i<12;i=i+2)
    {
            int tempXBox=ladderSnake->getXYcase(ladderPos[i],0)-35;
            int tempYBox=ladderSnake->getXYcase(ladderPos[i],1)-35;
            square = new QGraphicsRectItem(tempXBox,tempYBox,69,69);
            square->setBrush(QBrush(Qt::green));
            square->setOpacity(0.5);
            addItem(square);
            ladderSnake = new gamescene_1_ladderSnake();
            ladderSnake->initLadder(1,ladderPos[i],ladderPos[i+1]);
            ladderSnake->setFlag(QGraphicsItem::ItemIsFocusable);
            addItem(ladderSnake);

    }

    //Setting snakes pictures and associated green boxes
    for (int i=0;i<4;i=i+2)
    {
            int tempXBox=ladderSnake->getXYcase(snakePos[i+1],0)-35;
            int tempYBox=ladderSnake->getXYcase(snakePos[i+1],1)-35;
            square = new QGraphicsRectItem(tempXBox,tempYBox,69,69);
            square->setBrush(QBrush(Qt::red));
            square->setOpacity(0.5);
            addItem(square);
            ladderSnake = new gamescene_1_ladderSnake();
            ladderSnake->initLadder(2,snakePos[i],snakePos[i+1]);
            ladderSnake->setFlag(QGraphicsItem::ItemIsFocusable);
            addItem(ladderSnake);

    }
    for (int i=4;i<8;i=i+2)
    {
            int tempXBox=ladderSnake->getXYcase(snakePos[i+1],0)-35;
            int tempYBox=ladderSnake->getXYcase(snakePos[i+1],1)-35;
            square = new QGraphicsRectItem(tempXBox,tempYBox,69,69);
            square->setBrush(QBrush(Qt::red));
            square->setOpacity(0.5);
            addItem(square);
            ladderSnake = new gamescene_1_ladderSnake();
            ladderSnake->initLadder(3,snakePos[i],snakePos[i+1]);
            ladderSnake->setFlag(QGraphicsItem::ItemIsFocusable);
            addItem(ladderSnake);


    }
    for (int i=8;i<14;i=i+2)
    {
            int tempXBox=ladderSnake->getXYcase(snakePos[i+1],0)-35;
            int tempYBox=ladderSnake->getXYcase(snakePos[i+1],1)-35;
            square = new QGraphicsRectItem(tempXBox,tempYBox,69,69);
            square->setBrush(QBrush(Qt::red));
            square->setOpacity(0.5);
            addItem(square);
            ladderSnake = new gamescene_1_ladderSnake();
            ladderSnake->initLadder(4,snakePos[i],snakePos[i+1]);
            ladderSnake->setFlag(QGraphicsItem::ItemIsFocusable);
            addItem(ladderSnake);

    }

}

void gameScene_1::checkSnakeLadder()
{
    for (int i=0;i<12;i=i+2)
    {
            if(*player1->position == ladderPos[i])
            {
                QSound::play(":/sound_effects/ladder.wav");
                //Change player position to the value of ladderPos[i+1]
                *player1->newPosition=ladderPos[i+1];
                player1->moveInstantaneous();
            }

            if(*player2->position == ladderPos[i])
            {
                QSound::play(":/sound_effects/ladder.wav");
                //Change player position to the value of ladderPos[i+1]
                *player2->newPosition=ladderPos[i+1];
                player2->moveInstantaneous();
            }


    }

    for (int i=0;i<14;i=i+2)
    {
            if(*player1->position == snakePos[i+1])
            {
                QSound::play(":/sound_effects/snake.wav");
                        *player1->newPosition=snakePos[i];

                        player1->moveInstantaneous();
                //Change player position to the value of snakePos[i]
            }

            if(*player2->position == snakePos[i+1])
            {
                 QSound::play(":/sound_effects/snake.wav");

                        *player2->newPosition=snakePos[i];
                        player2->moveInstantaneous();
                //Change player position to the value of snakePos[i]
            }


    }

}
