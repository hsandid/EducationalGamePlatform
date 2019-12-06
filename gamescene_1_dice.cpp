#include "gamescene_1_dice.h"


/**
 * \file gameScene_1_dice.cpp
 * \brief Contains gameScene_1_dice class definition
 *
 * This class contains all logic and graphical elements related
 * to the 'dice' in Game 1.
 */

gameScene_1_dice::gameScene_1_dice(QObject *parent) :
    QObject(parent)
{
    id = new int();
    *id=0;
    diceVal = new int();
    *diceVal=0;



    setPixmap((QPixmap(":/images/dice-six.png")).scaled(100,100));

}

/**
 * @brief gameScene_1_dice::setup
 * @param value : id of dice (either 1 or 2)
 *
 * Setup a dice instance
 */

void gameScene_1_dice::setup(int value)
{
    *id=value;
}

/**
 * @brief gameScene_1_dice::update
 *
 * Roll the dice and update its value randomly
 */
void gameScene_1_dice::update()
{
    setFocus();
     if(*id==1)
        {
            srand(time(NULL));
        }
        else
        {
            srand(time(NULL)^2);
        }

        int value;
        value = rand()%6+1;

        switch(value)
              {
                  case 1:
                  this->setPixmap((QPixmap(":/images/dice-one.png")).scaled(100,100));
                  *diceVal=1;
                  break;
                  case 2:
                  this->setPixmap((QPixmap(":/images/dice-two.png")).scaled(100,100));
                  *diceVal=2;
                  break;
                  case 3:
                  this->setPixmap((QPixmap(":/images/dice-three.png")).scaled(100,100));
                  *diceVal=3;
                  break;
                  case 4:
                  this->setPixmap((QPixmap(":/images/dice-four.png")).scaled(100,100));
                  *diceVal=4;
                  break;
                  case 5:
                  this->setPixmap((QPixmap(":/images/dice-five.png")).scaled(100,100));
                  *diceVal=5;
                  break;
                  case 6:
                  this->setPixmap((QPixmap(":/images/dice-six.png")).scaled(100,100));
                  *diceVal=6;
                  break;
                  default:
                  break;
              }





}
