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
    password_edit->setEchoMode(QLineEdit::Password);

    passwordconf = new QLabel("Confirm Password :");
    passwordconf_edit = new QLineEdit();
    passwordconf_edit->setEchoMode(QLineEdit::Password);

    date_text = new QLabel("Date of Birth :");
    date_picker = new QDateEdit();
    date_picker->setMinimumDate(QDate(1900,1,1));
    date_picker->setMaximumDate(QDate(2021,1,1));ss
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

    error_message = new QLabel("");



    register_layout = new QGridLayout();
    register_layout->setSpacing(5);

    //Adding spacing items over all the first and last column
    register_layout->addItem(new QSpacerItem(10,10),0,0,5,1);
    register_layout->addItem(new QSpacerItem(10,10),0,5,4,1);
    register_layout->addItem(new QSpacerItem(90,90),10,1,1,3);

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
    register_layout->addWidget(error_message,9,1,1,3,Qt::AlignCenter);
    register_layout->addWidget(cancel,11,2);
    register_layout->addWidget(confirm,11,3);


    isSelected = false;

    this->setLayout(register_layout);
    this->setWindowTitle("Registration Page");



    QObject::connect(add_pppicture,SIGNAL(clicked()),this,SLOT(selectPicture()));
    QObject::connect(confirm,SIGNAL(clicked()),this,SLOT(checkConditions()));
    QObject::connect(cancel,SIGNAL(clicked()),this,SLOT(cancelRegistration()));



}

void registerWidget::cancelRegistration()
{
    loginWidget *login = new loginWidget();
    login->show();
    this->close();
    delete this;

}

void registerWidget::selectPicture()
{

    filename = new QString(QFileDialog::getOpenFileName(this,tr("Open Image"), "/home",tr("Image Files (*png)")));
    if (filename->toUtf8()!=NULL)
    {
        pppicture->setPixmap(QPixmap(filename->toUtf8()).scaledToHeight(100).scaledToWidth(100));
        isSelected = true;
    }
    else
    {
        filename = new QString(":images/symbol.png");
        pppicture->setPixmap(QPixmap(filename->toUtf8()).scaledToHeight(100).scaledToWidth(100));
        isSelected = false;
    }

}

bool registerWidget::passCheck()
{
    if (passwordconf_edit->text().toLower() == passwordconf_edit->text())
    {

        return false;
    }
    else if (passwordconf_edit->text().toUpper() == passwordconf_edit->text())
    {

        return false;
    }
    else if (passwordconf_edit->text().length()<8)
    {

        return false;
    }


    QString passTemp = passwordconf_edit->text();


        if (passTemp.contains('0',Qt::CaseInsensitive) || passTemp.contains('1',Qt::CaseInsensitive)
                || passTemp.contains('2',Qt::CaseInsensitive) || passTemp.contains('3',Qt::CaseInsensitive)
                || passTemp.contains('4',Qt::CaseInsensitive) || passTemp.contains('5',Qt::CaseInsensitive)
                || passTemp.contains('6',Qt::CaseInsensitive) || passTemp.contains('7',Qt::CaseInsensitive)
                || passTemp.contains('8',Qt::CaseInsensitive) || passTemp.contains('9',Qt::CaseInsensitive))
        {
            return true;
        }
        else
        {

        return false;
     }
}

void registerWidget::checkConditions()
{

if (username_edit->text().replace(" ","").isEmpty() || lname_edit->text().replace(" ","").isEmpty() || fname_edit->text().replace(" ","").isEmpty() || password_edit->text().replace(" ","").isEmpty() || passwordconf_edit->text().replace(" ","").isEmpty())
{
  error_message->setText("Please fill all sections");
}
else if (password_edit->text()!=passwordconf_edit->text())
{
    error_message->setText("Passwords do not match");
}
else if (!passCheck())
{
    error_message->setText("Password should consist of \n at least 9 characters and contain at \nleast one number, upper and lower\n case letters.");
}
else if (username_edit->text().replace(" ","").toLower()=="guest" )
{
    error_message->setText("'guest' cannot be set as username");
}
else
{
    confirmRegistration();
}

}

void registerWidget::confirmRegistration()
{
    QFile file("userdata.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonParseError JsonParseError;
    QJsonDocument JsonDocument = QJsonDocument::fromJson(file.readAll(), &JsonParseError);
    file.close();

    QJsonObject RootObject = JsonDocument.object();
    QJsonObject myuser;
    myuser.insert(QString("fname"),fname_edit->text());
    myuser.insert(QString("lname"),lname_edit->text());
    myuser.insert(QString("password"),password_edit->text());
    myuser.insert(QString("date_of_birth"),date_picker->text());
    if(male_button->isChecked())
    {
        myuser.insert(QString("gender"),QString("male"));
    }
    else if(female_button->isChecked())
    {
        myuser.insert(QString("gender"),QString("female"));
    }
    if (isSelected==true)
    {
        myuser.insert(QString("pp_present"),QString("yes"));
        QString homepath = QDir::homePath();
        if(!QDir(homepath+"/Pictures/GameSystem").exists())
        {
        QDir().mkdir(homepath+"/Pictures/GameSystem");
        }
        QFile::copy(filename->toUtf8(), QString(homepath+"/Pictures/GameSystem/"+username_edit->text().replace(" ","")+".png"));

    }
    else
    {
        myuser.insert(QString("pp_present"),QString("no"));
    }

    RootObject.insert(username_edit->text(),myuser);

    JsonDocument.setObject(RootObject);


    file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    file.write(JsonDocument.toJson());
    file.close();

    loginWidget *login = new loginWidget();
    login->show();
    this->close();
    delete this;

}

