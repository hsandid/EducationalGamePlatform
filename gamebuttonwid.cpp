#include "gamebuttonwid.h"

gamebuttonWid::gamebuttonWid(QWidget *parent) :
    QWidget(parent)
{
     //image1 = new QPixmap("images/S&L.PNG");
    image1 = new QLabel();
    image1->setPixmap(QPixmap(":images/S&L.PNG").scaledToHeight(200).scaledToWidth(200));

     SinglePlayer = new QPushButton("Play vs Bot");
     Multiplayer = new QPushButton("Play Multiplayer");
     layout = new QGridLayout;
     layout->addWidget(image1,0,0,1,4,Qt::AlignCenter);
     layout->addWidget(SinglePlayer,1,0,2,2);
     layout->addWidget(Multiplayer,1,2,2,2);
     this->setLayout(layout);


}
