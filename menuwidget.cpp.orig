#include "menuwidget.h"
#include "loginwidget.h"
#include "birthdaywidget.h"
#include "gamescene_1.h"


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

    isGuest = new bool(false);

    usernameDisplay = new QLabel("username : ");
    ppDisplay = new QLabel();
    fnameDisplay = new QLabel("First Name : ");
    lnameDisplay = new QLabel("Last Name : ");
    dobDisplay = new QLabel("Date of Birth : ");
    genderDisplay = new QLabel("Gender : ");


    Welcome = new QLabel("Welcome Back");
    Game1Name = new QLabel("Snakes'n'Ladders");
    Game2Name = new QLabel("Cabo");
    Play1 = new QPushButton("New game (CPU)");
    Play1x = new QPushButton("New game (Multiplayer)");
    Play2 = new QPushButton("New game (CPU)");
    Play2x = new QPushButton("New game (Multiplayer)");
    Load1 = new QPushButton("Load Game");
    Load2 = new QPushButton("Load Game");
    Load1->setEnabled(false);
    Load2->setEnabled(false);
    Logout = new QPushButton("Log out");
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
   play_layout->addWidget(Play1x,4,0);
   play_layout->addWidget(Play2x,4,1);
    play_layout->addWidget(Load1,5,0);
    play_layout->addWidget(Load2,5,1);


    play->setLayout(play_layout);



    profile_layout->addWidget(ppDisplay,0,0);
    profile_layout->addWidget(usernameDisplay,1,0);
    profile_layout->addWidget(fnameDisplay,2,0);
    profile_layout->addWidget(lnameDisplay,3,0);
    profile_layout->addWidget(dobDisplay,4,0);
    profile_layout->addWidget(genderDisplay,5,0);
    profile_layout->addWidget(Logout,6,0,1,2,Qt::AlignCenter);

    profile->setLayout(profile_layout);

    history->setLayout(history_layout);


    tabWidget = new QTabWidget;
    tabWidget->addTab(play, tr("Play"));
    tabWidget->addTab(profile, tr("My Profile"));
    tabWidget->addTab(history, tr("History"));


    readFromJsonProfile();

    test_layout->addWidget(tabWidget);
    tabWidget->setTabEnabled(2,false);
    this->setLayout(test_layout);
    this->setWindowTitle("Main Menu");
    this->setFixedSize(QSize(600, 500));

    QObject::connect(Logout,SIGNAL(clicked()),this,SLOT(logout()));
    QObject::connect(Play1,SIGNAL(clicked()),this,SLOT(startGameCPU()));
    QObject::connect(Play1x,SIGNAL(clicked()),this,SLOT(startGameMultiplayer()));
    QObject::connect(Load1,SIGNAL(clicked()),this,SLOT(loadGame()));



}

void menuWidget::loadGame()
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

    QFile file;
    QString fileContents;
    file.setFileName("userdata.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    fileContents = file.readAll();
    file.close();

    QJsonDocument jsonDocTwo= QJsonDocument::fromJson(fileContents.toUtf8());
    QJsonObject objTwo = jsonDocTwo.object();

    QJsonObject myUser = objTwo[userName].toObject();



    QGraphicsView * myView = new QGraphicsView();
    gameScene_1 * scene1 = new gameScene_1();

    if(myUser["cpu"]==QString("true"))
    {
       *scene1->CPU=true;
    }
    else
    {
        *scene1->CPU=false;
    }

    if(myUser["turn"]==QString("p1"))
    {
        scene1->loadGame(myUser[QString("p1pos")].toInt(),myUser[QString("p2pos")].toInt(),false);

    }
    else
    {
        scene1->loadGame(myUser[QString("p1pos")].toInt(),myUser[QString("p2pos")].toInt(),true);
    }




    myView->setScene(scene1);
    myView->setFixedSize(960,700);
    myView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    myView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    myView->show();

    this->close();
    delete this;


}

void menuWidget::logout()
{
    loginWidget *login = new loginWidget();
    login->show();
    this->close();
    delete this;
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


    Load1->setEnabled(false);
    Load2->setEnabled(false);

    usernameDisplay->setText("Logged in as a Guest");
    usernameDisplay->setAlignment(Qt::AlignCenter);
    fnameDisplay->setVisible(false);
    lnameDisplay->setVisible(false);
    dobDisplay->setVisible(false);
    genderDisplay->setVisible(false);
    ppDisplay->setVisible(false);

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

            ppDisplay->setPixmap(QPixmap(QString(myUser["pp_path"].toString())).scaledToHeight(200).scaledToWidth(200));

        }
        else
        {
            ppDisplay->setPixmap(QPixmap(QString(":images/symbol.png")).scaledToHeight(200));


        }

        if(myUser["game1_active"].toString()=="yes")
        {
            Load1->setEnabled(true);
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


void menuWidget::startGameCPU()
{

        QGraphicsView * myView = new QGraphicsView();
        gameScene_1 * scene1 = new gameScene_1();
        *scene1->CPU=true;

        myView->setScene(scene1);
        myView->setFixedSize(960,700);
        myView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        myView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        myView->show();

        this->close();
        delete this;
}

void menuWidget::startGameMultiplayer()
{

        QGraphicsView * myView = new QGraphicsView();
        gameScene_1 * scene1 = new gameScene_1();
        *scene1->CPU=false;

        myView->setScene(scene1);
        myView->setFixedSize(960,700);
        myView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        myView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        myView->show();

        this->close();
        delete this;
}

