#include "loginwidget.h"
#include "menuwidget.h"
#include "registerwidget.h"

loginWidget::loginWidget(QWidget *parent) :
    QWidget(parent)
{
    // Here shall be designed the login screen
    // ALL CODE HERE SHALL BE CONSIDERED TEMPLATE

    test_screen = new QLabel("This is the Login Page");
    button = new QPushButton("Login");
    button_1 = new QPushButton("Register");
    test_layout = new QVBoxLayout();

    test_layout->addWidget(test_screen);
    test_layout->addWidget(button);
    test_layout->addWidget(button_1);

    this->setLayout(test_layout);

    QObject::connect(button,SIGNAL(clicked()),this,SLOT(GoToMainPage()));
    QObject::connect(button_1,SIGNAL(clicked()),this,SLOT(GoToRegisterPage()));


}


void loginWidget::GoToMainPage()
{
menuWidget *menuInit = new menuWidget();
menuInit->show();
this->hide();
}

void loginWidget::GoToRegisterPage()
{
registerWidget *registerInit = new registerWidget();
registerInit->show();
this->hide();
}


