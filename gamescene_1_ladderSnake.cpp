#include "gamescene_1_ladderSnake.h"
#include <QTextStream>


/**
 * \file gameScene_1_laddersnake.cpp
 * \brief Contains gameScene_1_ladderSnake class definition
 *
 * This class contains attributes for each instances of Ladders & Snakes.
 */


gamescene_1_ladderSnake::gamescene_1_ladderSnake(QObject *parent) :
    QObject(parent)
{
    goForward=new bool();
    *goForward=true;
    posXstart = new int();
    *posXstart = 0;
    posYstart = new int();
    *posYstart = 0;
    posXend = new int();
    *posXend = 0;
    posYend = new int();
    *posYend = 0;
    posXtemp=new int();
    *posXtemp = 0;
    posYtemp=new int();
    *posYtemp = 0;
    posXtempFunc=new int();
    *posXtempFunc = 0;
    posYtempFunc=new int();
    *posYtempFunc = 0;
    size= new double();
    *size = 0;
    angle= new double();
    *angle= 0;
    centerX= new double();
    *centerX = 0;
    centerY= new double();
    *centerY= 0;
    tempLength= new double();
    *tempLength= 0;
    id = new int();
    *id=0;


}

/**
 * @brief gamescene_1_ladderSnake::initLadder
 * @param seed : 0-1 are ladder instance seeds, 2-3-4 are snake instance seeds
 * @param start : where is the instance start position
 * @param end :  where is the instance end position
 *
 * Initialize ladder or snake instance with given parameters
 */
void gamescene_1_ladderSnake::initLadder(int seed,int start,int end)
{


        *id=seed;
        *size = qSqrt(qPow(getXYcase(start,0)-getXYcase(end,0),2)+qPow(getXYcase(start,1)-getXYcase(end,1),2));
        *centerX= (getXYcase(start,0)+ getXYcase(end,0))/2;
        *centerY= (getXYcase(start,1)+ getXYcase(end,1))/2;

        *posXtempFunc = getXYcase(end,0);
        *posYtempFunc = getXYcase(start,1);
        *tempLength = qSqrt(qPow(getXYcase(start,0)- *posXtempFunc ,2)+qPow(getXYcase(start,1)- *posYtempFunc ,2));



        *angle = qRadiansToDegrees(qAcos(*tempLength/ *size));


        if(seed==0)
        {
            QPixmap p1 = (QPixmap(":/images/ladders/ladder1.png")).scaled(40, *size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            setPixmap(p1);
        }
        else if (seed==1)
        {
            QPixmap p1 = (QPixmap(":/images/ladders/ladder2.png")).scaled(40, *size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            setPixmap(p1);
        }
        else if (seed==2)
        {
            QPixmap p1 = (QPixmap(":/images/snakes/snakes1.png")).scaled(40, *size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            setPixmap(p1);
        }
        else if (seed==3)
        {
            QPixmap p1 = (QPixmap(":/images/snakes/snakes2.png")).scaled(40, *size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            setPixmap(p1);
        }
        else if (seed==4)
        {
            QPixmap p1 = (QPixmap(":/images/snakes/snakes3.png")).scaled(40, *size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            setPixmap(p1);
        }

        setPos(getXYcase(end,0)-20,getXYcase(end,1));
        if(*posXtempFunc<getXYcase(start,0))
        {
            setRotation(*angle-90);
        }
        else
        {
            setRotation(-*angle+90);
        }



}

/**
 * @brief gamescene_1_ladderSnake::getXYcase
 * @param caseNum : value of the case to search
 * @param xy : xy=0  return x value , xy=1  return y value
 * @return x coordinate of the case
 *
 * When assigning a case to a ladder/snake, we search for its coordinates using this function
 */
int  gamescene_1_ladderSnake::getXYcase(int caseNum,int xy)
{

    *goForward=true;

    *posXtemp = 35;
    *posYtemp = 665;

    for (int i=1;i<caseNum;i++)
    {
        if(*goForward)
        {

            if(*posXtemp> 630)
            {
                *posYtemp= *posYtemp-70;
                *goForward=false;
            }
            else
            {
                *posXtemp= *posXtemp+70;
            }

        }
        else
        {
            if(*posXtemp < 60)
                {
                                *posYtemp= *posYtemp-70;
                               *goForward=true;
                }

                       else
                       {
                           *posXtemp= *posXtemp-70;
                       }
        }
    }

    if (xy==0)
    {
        return *posXtemp;
    }
    else
    {
        return *posYtemp;
    }




}


