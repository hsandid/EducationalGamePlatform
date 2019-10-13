#include "menuwidget.h"
#include "loginwidget.h"
#include "birthdaywidget.h"

menuWidget::menuWidget(QWidget *parent) :
    QWidget(parent)
{
    // Here shall be designed the main menu screen
    // ALL CODE HERE SHALL BE CONSIDERED TEMPLATE


    test_layout = new QGridLayout;
    play_layout = new QGridLayout;
    history_layout = new QGridLayout;
    profile_layout = new QGridLayout;
    play = new QWidget();
    profile = new QWidget();
    history = new QWidget();



    usernameDisplay = new QLabel("username : ");
    ppDisplay = new QLabel();
    fnameDisplay = new QLabel("First Name : ");
    lnameDisplay = new QLabel("Last Name : ");
    dobDisplay = new QLabel("Date of Birth : ");
    genderDisplay = new QLabel("Gender : ");




    play->setLayout(play_layout);


    profile_layout->addWidget(usernameDisplay,0,0);
    profile_layout->addWidget(ppDisplay,1,0);
    profile_layout->addWidget(fnameDisplay,2,0);
    profile_layout->addWidget(lnameDisplay,3,0);
    profile_layout->addWidget(dobDisplay,4,0);
    profile_layout->addWidget(genderDisplay,5,0);

    profile->setLayout(profile_layout);

    history->setLayout(history_layout);


    tabWidget = new QTabWidget;
    tabWidget->addTab(play, tr("Play"));
    tabWidget->addTab(profile, tr("My Profile"));
    tabWidget->addTab(history, tr("History"));

    readFromJsonProfile();

    test_layout->addWidget(tabWidget);
    this->setLayout(test_layout);
    this->setWindowTitle("Main Menu");




}



void menuWidget::readFromJsonProfile()
{

    QFile config("config.json");
    config.open(QFile::ReadOnly | QFile::Text );
    QString userInfo;
    QString userName;
    userInfo = config.readAll();
    config.close();

    QJsonParseError JsonParseError;
    QJsonDocument jsonDoc= QJsonDocument::fromJson(userInfo.toUtf8(),&JsonParseError);
    QJsonObject obj = jsonDoc.object();
    userName = obj["loggedon"].toString();

    if (userName=="guest")
    {
    tabWidget->setTabEnabled(1,false);
    }
    else
    {
        QFile file;
        QString fileContents;
        file.setFileName("userdata.json");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        fileContents = file.readAll();
        file.close();

        QJsonDocument jsonDocTwo= QJsonDocument::fromJson(fileContents.toUtf8());
        QJsonObject objTwo = jsonDocTwo.object();

        QJsonObject myUser = objTwo[userName].toObject();

        usernameDisplay->setText("Username : "+userName);
        fnameDisplay->setText("First Name : "+ myUser["fname"].toString());
        lnameDisplay->setText("Last Name : "+ myUser["lname"].toString());
        dobDisplay->setText("Date of Birth : "+ myUser["date_of_birth"].toString());
        genderDisplay->setText("Gender : "+ myUser["gender"].toString());

        if(myUser["pp_present"].toString()=="yes")
        {
            QString homepath = QDir::homePath();
            ppDisplay->setPixmap(QPixmap(QString(homepath+"/Pictures/GameSystem/"+userName+".png")).scaledToHeight(200).scaledToWidth(200));


        }
        else
        {
            ppDisplay->setPixmap(QPixmap(QString(":images/symbol.png")).scaledToHeight(200));


        }


        QDate cd = QDate::currentDate();
        QDate da =QDate::fromString(myUser["date_of_birth"].toString(),"yyyy-MM-dd");

        if(cd.day()==da.day() && cd.month()==da.month())
        {
            birthdaywidget *bd = new birthdaywidget();
            bd->show();

        }



    }




}

