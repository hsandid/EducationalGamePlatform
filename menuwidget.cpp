#include "menuwidget.h"
#include "loginwidget.h"

menuWidget::menuWidget(QWidget *parent) :
    QWidget(parent)
{
    // Here shall be designed the main menu screen
    // ALL CODE HERE SHALL BE CONSIDERED TEMPLATE

    test_screen = new QLabel("This is the Menu page");
    button = new QPushButton("Logout");
    test_layout = new QVBoxLayout();

    test_layout->addWidget(test_screen);
    test_layout->addWidget(button);


    this->setLayout(test_layout);

    QObject::connect(button,SIGNAL(clicked()),this,SLOT(GoToLoginPage()));
}


void menuWidget::GoToLoginPage()
{
loginWidget *loginInit = new loginWidget();
loginInit->show();
this->close();
}
