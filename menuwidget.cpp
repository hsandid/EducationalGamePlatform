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


    Welcome = new QLabel("Welcome Back");
    Game1Name = new QLabel("Snakes'n'Ladders");
    Game2Name = new QLabel("Cabo");
    Play1 = new QPushButton("Play");
    Play2 = new QPushButton("Play") ;
    Load1 = new QPushButton("Load");
    Load2 = new QPushButton("Load");
    image1 = new QLabel();
    image1->setPixmap(QPixmap(":images/snl.png").scaledToHeight(200).scaledToWidth(200));
    image2 = new QLabel();
    image2->setPixmap(QPixmap(":images/cabo.png").scaledToHeight(200).scaledToWidth(200));
    play_layout->addWidget(Welcome,0,0,1,2,Qt::AlignCenter);
    play_layout->addWidget(image1,1,0,1,1);
    play_layout->addWidget(image2,1,1,1,1);
   play_layout->addWidget(Game1Name,2,0,Qt::AlignCenter);
   play_layout->addWidget(Game2Name,2,1,Qt::AlignCenter);
   play_layout->addWidget(Play1,3,0);
   play_layout->addWidget(Play2,3,1);
    play_layout->addWidget(Load1,4,0);
    play_layout->addWidget(Load2,4,1);


    play->setLayout(play_layout);



    profile_layout->addWidget(ppDisplay,0,0);
    profile_layout->addWidget(usernameDisplay,1,0);
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
    this->setFixedSize(QSize(500, 500));



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
    tabWidget->setTabEnabled(2,false);
    Load1->setEnabled(false);
    Load2->setEnabled(false);

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

