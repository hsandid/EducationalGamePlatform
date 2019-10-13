#include "birthdaywidget.h"

birthdaywidget::birthdaywidget(QWidget *parent) :
    QWidget(parent)
{
    layout = new QVBoxLayout();
    bdtext = new QLabel("Happy birthday!!!");
    conf = new QPushButton("Continue");
    layout->addWidget(bdtext);
    layout->addWidget(conf);
    this->setLayout(layout);

    QObject::connect(conf,SIGNAL(clicked()),this,SLOT(confirmExit()));
}

void birthdaywidget::confirmExit()
{
this->close();
delete this;
}
