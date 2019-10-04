#include "registerwidget.h"
#include "loginwidget.h"

registerWidget::registerWidget(QWidget *parent) :
    QWidget(parent)
{
    // Here shall be designed the register user screen
    // ALL CODE HERE SHALL BE CONSIDERED TEMPLATE
    // This is Hadi's Part

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

    grid_01 = new QVBoxLayout();




    this->setLayout(grid_01);


}



