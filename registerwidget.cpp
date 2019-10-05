#include "registerwidget.h"
#include "loginwidget.h"
#include <QSpacerItem>

registerWidget::registerWidget(QWidget *parent) :
    QWidget(parent)
{

    // Add title to page
        // What elements should be added to the register page?
        // First name, Last name, username, password, date of birth
        // Profile picture, gender
        // Special considerations should be made for the password.
        // QLabels needed : Welcome text, fname, lname, username, gender
        // date of birth, password, profile picture, confirm password, Error message

        // QLineEdits needed : fname, lname, username, password, confirm password

        // QSpinBox needed : 3 for date of birth : day,month,year

        // QDateEdit : date of birth

        // QRadioButtons needed : male,female,do not specify
        // + don't forget the vboxlayout.

        // QPushButtons needed :  Cancel, Confirm, select picture

        // Challenges :

        //Creating a cadre for the picture to be displayed in the register page ( with a default blank pic)
        //copy the picture selected by the user in the working directory
        //Need to address the "save to JSON" issue to add separate users
        //Maybe apply a specific style ?

    welcome = new QLabel("Please fill the following to register your account");
    fname = new QLabel("First name");
    fname_edit = new QLineEdit();
    lname = new QLabel("Last name");
    lname_edit = new QLineEdit();
    username = new QLabel("Username");
    username_edit = new QLineEdit();
    password = new QLabel("Password");
    password_edit = new QLineEdit();
    passwordconf = new QLabel("Confirm Password");
    passwordconf_edit = new QLineEdit();

    register_layout = new QGridLayout();

    register_layout->addWidget(welcome,0,1,1,3,Qt::AlignCenter);
    register_layout->addItem(new QSpacerItem(10,10),0,0,5,1);
    register_layout->addItem(new QSpacerItem(10,10),0,4,5,1);
    register_layout->addWidget(fname,1,1);
    register_layout->addWidget(fname_edit,1,2);
    register_layout->addWidget(lname,2,1);
    register_layout->addWidget(lname_edit,2,2);
    register_layout->addWidget(username,3,1);
    register_layout->addWidget(username_edit,3,2);
    register_layout->addWidget(password,4,1);
    register_layout->addWidget(password_edit,4,2);
    register_layout->addWidget(passwordconf,5,1);
    register_layout->addWidget(passwordconf_edit,5,2);
    register_layout->setSpacing(5);


    this->setLayout(register_layout);



}



