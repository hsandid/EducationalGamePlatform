#include "menuwidget.h"
#include "loginwidget.h"

menuWidget::menuWidget(QWidget *parent) :
    QWidget(parent)
{
    // Here shall be designed the main menu screen
    // ALL CODE HERE SHALL BE CONSIDERED TEMPLATE


    test_layout = new QGridLayout;
    play_layout = new QGridLayout;
    profile_layout = new QGridLayout;
    play = new QWidget();
    profile = new QWidget();
    Welcome = new QLabel("Welcome Back");
    Game1Name = new QLabel("Snackes&Ladders");
    Game2Name = new QLabel("Cabo");
    Play1 = new QPushButton("Play");
    Play2 = new QPushButton("Play") ;
    Load1 = new QPushButton("Load");
    Load2 = new QPushButton("Load");
    image1 = new QPixmap("images/S&L.PNG");
    image2 = new QPixmap("images/Cabo.PNG");
    profile_layout->addWidget(Welcome,0,0,1,4,Qt::AlignCenter);
    profile_layout->addWidget(image1,1,0,2,2);
    profile_layout->addWidget(image2,1,2,2,2);


    play->setLayout(play_layout);

    profile->setLayout(profile_layout);

    tabWidget = new QTabWidget;
    tabWidget->addTab(play, tr("Play"));
    tabWidget->addTab(profile, tr("My Profile"));

    test_layout->addWidget(tabWidget);
    this->setLayout(test_layout);


}


