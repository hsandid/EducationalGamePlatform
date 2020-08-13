#include "card.h"

/**
 * \file card.cpp
 * \brief Contains card class definition
 *
 * This class contains all logic and graphical elements related
 * to cards used by players in cabo
 */

card::card(QObject *parent) :
    QObject(parent)
{

    hasCard = new bool();
    *hasCard=true;
    cardShown= new bool();
    *cardShown = false;
    cardValue = new int();
    *cardValue = 0;
    setPixmap((QPixmap(":/images/facedown.jpg")).scaled(80,108));


}

/**
 * @brief card::setPosition
 *
 * Set position of a specific card in the scene
 */

void card::setPosition(int x, int y, int rotation)
{
this->setPos(x,y);
this->setRotation(rotation);
}

void card::setCardPic()
{
    bool temp = *cardShown;
    *cardShown=!temp;
    //Should be *cardShown
    if(*cardShown)
    {
        if(*cardValue==0)
        {
            setPixmap((QPixmap(":/images/card0.jpg")).scaled(80,108));
        }
        else if( *cardValue==1)
        {

            setPixmap((QPixmap(":/images/card1.jpg")).scaled(80,108));

        }
        else if( *cardValue==2)
        {

            setPixmap((QPixmap(":/images/card2.jpg")).scaled(80,108));

        }
        else if( *cardValue==3)
        {

            setPixmap((QPixmap(":/images/card3.jpg")).scaled(80,108));

        }
        else if( *cardValue==4)
        {

            setPixmap((QPixmap(":/images/card4.jpg")).scaled(80,108));

        }
        else if( *cardValue==5)
        {

            setPixmap((QPixmap(":/images/card5.jpg")).scaled(80,108));

        }
        else if( *cardValue==6)
        {

            setPixmap((QPixmap(":/images/card6.jpg")).scaled(80,108));

        }
        else if( *cardValue==7)
        {

            setPixmap((QPixmap(":/images/card7.jpg")).scaled(80,108));

        }
        else if( *cardValue==8)
        {

            setPixmap((QPixmap(":/images/card8.jpg")).scaled(80,108));

        }
        else if( *cardValue==9)
        {

            setPixmap((QPixmap(":/images/card9.jpg")).scaled(80,108));

        }
        else if( *cardValue==10)
        {

            setPixmap((QPixmap(":/images/card10.jpg")).scaled(80,108));

        }
        else if( *cardValue==11)
        {

            setPixmap((QPixmap(":/images/card11.jpg")).scaled(80,108));

        }
        else if( *cardValue==12)
        {

            setPixmap((QPixmap(":/images/card12.jpg")).scaled(80,108));

        }
        else if( *cardValue==13)
        {

            setPixmap((QPixmap(":/images/card13.jpg")).scaled(80,108));

        }
    }
    else
    {
        setPixmap((QPixmap(":/images/facedown.jpg")).scaled(80,108));
    }
}
