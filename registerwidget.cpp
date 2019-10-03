#include "registerwidget.h"
#include "loginwidget.h"

registerWidget::registerWidget(QWidget *parent) :
    QWidget(parent)
{
    // Here shall be designed the register user screen
    // ALL CODE HERE SHALL BE CONSIDERED TEMPLATE
    // This is Hadi's Part

    test_screen = new QLabel("This is the Login Page");
    button = new QPushButton("Confirm Registration");

    test_layout = new QVBoxLayout();

    test_layout->addWidget(test_screen);
    test_layout->addWidget(button);


    this->setLayout(test_layout);

    QObject::connect(button,SIGNAL(clicked()),this,SLOT(GoToLoginPage()));
}


void registerWidget::GoToLoginPage()
{
loginWidget *loginInit = new loginWidget();
loginInit->show();
this->close();
}
