#include "gamescene_1_player.h"

gameScene_1_player::gameScene_1_player(QObject *parent) :
    QObject(parent)
{
    goForward = new bool();
    *goForward=true;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this,SLOT(update()));
    timer->start(200);
    setPixmap((QPixmap(":/images/player1.png").scaled(35,65)));

}

void gameScene_1_player::update()
{
       this->setFocus();

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


                          if ( this->y()< 60)
                          {
                           this->setPos(1,635);
                              *goForward=true;
                          }
                          else
                          {
                              this->setPos(posX,posY-70);
                              *goForward=true;
                          }


                      }
                      else
                      {
                          int posX = this->x();
                          int posY = this->y();
                          this->setPos(posX-70,posY);
                      }
       }


   }
