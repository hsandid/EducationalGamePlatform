#include "loginwidget.h"
#include "menuwidget.h"
#include "registerwidget.h"

loginWidget::loginWidget(QWidget *parent) :
    QWidget(parent)
{
    // Here shall be designed the login screen
    // ALL CODE HERE SHALL BE CONSIDERED TEMPLATE
    // This is Mehiedinne's part

    test_screen = new QLabel("Welcome To Our GameSystem");
    LogINbutton = new QPushButton("Login");
    RegisterButton = new QPushButton("Register");
    UserName = new QLabel("Username");
    UserNameLine = new QLineEdit();
    PassWord = new QLabel("Password");
    PassWordLine= new QLineEdit();

    test_layout = new QGridLayout ();

    test_layout->addWidget(test_screen,0,0,2,2,Qt::AlignCenter);
    test_layout->addWidget(UserName,3,0);
    test_layout->addWidget(UserNameLine,3,1);
    test_layout->addWidget(PassWord,4,0);
    test_layout->addWidget(PassWordLine,4,1);
    test_layout->addWidget(LogINbutton);
    test_layout->addWidget(RegisterButton);

    this->setLayout(test_layout);

    QObject::connect(LogINbutton,SIGNAL(clicked()),this,SLOT(GoToMainPage()));
    QObject::connect(RegisterButton,SIGNAL(clicked()),this,SLOT(GoToRegisterPage()));


}


void loginWidget::GoToMainPage()
{
menuWidget *menuInit = new menuWidget();
menuInit->show();
this->close();
}

void loginWidget::GoToRegisterPage()
{
registerWidget *registerInit = new registerWidget();
registerInit->show();
this->close();
}


