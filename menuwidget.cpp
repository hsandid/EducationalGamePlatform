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
    play->setLayout(play_layout);
    profile->setLayout(profile_layout);

    tabWidget = new QTabWidget;
    tabWidget->addTab(play, tr("Play"));
    tabWidget->addTab(profile, tr("My Profile"));

    test_layout->addWidget(tabWidget);
    this->setLayout(test_layout);


}


