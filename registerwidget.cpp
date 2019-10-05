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

    fname = new QLabel("First name :");
    fname_edit = new QLineEdit();

    lname = new QLabel("Last name :");
    lname_edit = new QLineEdit();

    username = new QLabel("Username :");
    username_edit = new QLineEdit();

    password = new QLabel("Password :");
    password_edit = new QLineEdit();

    passwordconf = new QLabel("Confirm Password :");
    passwordconf_edit = new QLineEdit();

    date_text = new QLabel("Date of Birth :");
    date_picker = new QDateEdit();
    date_picker->setMinimumDate(QDate(1900,1,1));
    date_picker->setMaximumDate(QDate(2021,1,1));
    date_picker->setDisplayFormat(QString("yyyy-MM-dd"));
    date_picker->setDate(QDate(2019,1,1));

    gender_container = new QGroupBox();
    gender_radio = new QVBoxLayout();
    male_button = new QRadioButton("Male");
    female_button = new QRadioButton("Female");
    male_button->setChecked(true);
    gender_text = new QLabel("Gender :");
    gender_radio->addWidget(male_button);
    gender_radio->addWidget(female_button);
    gender_container->setLayout(gender_radio);

    filename = new QString(":images/symbol.png");
    pppicture_text = new QLabel("Profile Picture :");
    add_pppicture = new QPushButton("Select Picture");
    pppicture = new QLabel();
    pppicture->setPixmap(QPixmap(filename->toUtf8()).scaledToHeight(100).scaledToWidth(100));

    cancel = new QPushButton("Cancel");
    confirm = new QPushButton("Confirm");






    register_layout = new QGridLayout();
    register_layout->setSpacing(5);

    //Adding spacing items over all the first and last column
    register_layout->addItem(new QSpacerItem(10,10),0,0,5,1);
    register_layout->addItem(new QSpacerItem(10,10),0,5,4,1);

    register_layout->addWidget(welcome,0,1,1,3,Qt::AlignCenter);
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
    register_layout->addWidget(passwordconf,5,1);
    register_layout->addWidget(passwordconf_edit,5,2);
    register_layout->addWidget(date_text,6,1);
    register_layout->addWidget(date_picker,6,2);
    register_layout->addWidget(gender_text,7,1);
    register_layout->addWidget(gender_container,7,2);
    register_layout->addWidget(pppicture_text,8,1);
    register_layout->addWidget(pppicture,8,2);
    register_layout->addWidget(add_pppicture,8,3);
    register_layout->addWidget(cancel,9,1);
    register_layout->addWidget(confirm,9,2);


    this->setLayout(register_layout);

    QObject::connect(add_pppicture,SIGNAL(clicked()),this,SLOT(selectPicture()));



}

void registerWidget::selectPicture()
{

    filename = new QString(QFileDialog::getOpenFileName(this,tr("Open Image"), "/home",tr("Image Files (*png)")));
    pppicture->setPixmap(QPixmap(filename->toUtf8()).scaledToHeight(100).scaledToWidth(100));
}



