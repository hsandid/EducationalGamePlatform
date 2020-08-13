#include "birthdaywidget.h"


/**
 * \file birthdaywidget.cpp
 * \brief Contains birthdaywidget class definition
 *
 * This QWidget is shown whenever the user logs-in on his
 * birthdate.
 */

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

/**
 * @brief birthdaywidget::confirmExit
 *
 * Exit from birthday message
 */
void birthdaywidget::confirmExit()
{
this->close();
delete this;
}
