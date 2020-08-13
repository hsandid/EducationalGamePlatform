#include "gamescene_1_player.h"
#include <QTextStream>

/**
 * \file gameScene_1_player.cpp
 * \brief Contains gameScene_1_player class definition
 *
 * This class contains all visual and logic attributes for the player elements.
 */


gameScene_1_player::gameScene_1_player(QObject *parent) :
    QObject(parent)
{
    goForward = new bool();
    *goForward=true;
    id = new int();
    *id=0;
    position = new int();
    *position=1;
    newPosition = new int();
    *newPosition=1;



}

/**
 * @brief gameScene_1_player::setup
 * @param playerid : id for player
 *
 * Initializing the player instance
 */
void gameScene_1_player::setup(int playerid)
{
    if(playerid==1)
    {
    setPixmap((QPixmap(":/images/player1.png").scaled(35,35)));
    setPos(5,665);
    *id=1;
    }
    else
    {
    setPixmap((QPixmap(":/images/player2.png").scaled(35,35)));
    setPos(35,630);
    *id=2;
    }
}

/**
 * @brief gameScene_1_player::moveInstantaneous
 *
 * Move the player to its newly assigned position
 */
void gameScene_1_player::moveInstantaneous()
{
    this->setFocus();
    QSound::play(":/sound_effects/playermove.wav");

    int moves =*newPosition - *position;
    bool backTurn = false;

    if (moves<0)
    {
        moves=moves*(-1);
        backTurn=true;
    }

    if (!backTurn)
    {
        for (int i=0;i<moves;i++)
        {
            if(*goForward)
            {

                if(this->x()> 630)
                {
                    int posX = this->x();
                    int posY = this->y();
                    *goForward=false;
                    this->setPos(posX,posY-70);

                }
                else
                {
                    int posX = this->x();
                    int posY = this->y();
                    this->setPos(posX+70,posY);
                }

            }
            else
            {
                if(this->x() < 60)
                           {
                               int posX = this->x();
                               int posY = this->y();



                                   this->setPos(posX,posY-70);
                                   *goForward=true;



                           }
                           else
                           {
                               int posX = this->x();
                               int posY = this->y();
                               this->setPos(posX-70,posY);
                           }
            }
        }

    }
    else
    {
        for (int i=0;i<moves;i++)
        {
            if(*goForward)
            {



                if(this->x()< 60)
                {
                    int posX = this->x();
                    int posY = this->y();
                    *goForward=false;
                    this->setPos(posX,posY+70);

                }
                else
                {
                    int posX = this->x();
                    int posY = this->y();
                    this->setPos(posX-70,posY);
                }

            }
            else
            {
                if(this->x() > 630)
                           {
                               int posX = this->x();
                               int posY = this->y();


                                this->setPos(posX,posY+70);
                                *goForward=true;
                               }



                           else
                           {
                               int posX = this->x();
                               int posY = this->y();
                               this->setPos(posX+70,posY);
                           }
            }
        }
    }



 *position=*newPosition;
}
