#include "loginwidget.h"
#include "menuwidget.h"
#include "registerwidget.h"

loginWidget::loginWidget(QWidget *parent) :
    QWidget(parent)
{
    // Here shall be designed the login screen
    // ALL CODE HERE SHALL BE CONSIDERED TEMPLATE
    // This is Mehiedinne's part

    test_screen = new QLabel("Welcome To Our GameSystem");
    LogINbutton = new QPushButton("Login");
    RegisterButton = new QPushButton("Register");
    UserName = new QLabel("Username");
    UserNameLine = new QLineEdit();
    PassWord = new QLabel("Password");
    PassWordLine= new QLineEdit();
    ErrorMessage = new QLabel("");
	 PlayAsGuestButton = new QPushButton("Play As Guest");
    test_layout = new QGridLayout ();

    test_layout->addWidget(test_screen,0,0,2,3,Qt::AlignCenter);
    test_layout->addWidget(UserName,3,0);
    test_layout->addWidget(UserNameLine,3,1,1,2);
    test_layout->addWidget(PassWord,4,0);
    test_layout->addWidget(PassWordLine,4,1,1,2);
    test_layout->addWidget(ErrorMessage,5,0,1,3,Qt::AlignCenter);
    test_layout->addWidget(RegisterButton,6,0,1,1);
    test_layout->addWidget(LogINbutton,6,1,1,1);
    test_layout->addWidget(PlayAsGuestButton,6,2,1,1);


    this->setLayout(test_layout);

    QObject::connect(LogINbutton,SIGNAL(clicked()),this,SLOT(checkLogin()));
    QObject::connect(RegisterButton,SIGNAL(clicked()),this,SLOT(GoToRegisterPage()));
    QObject::connect(PlayAsGuestButton,SIGNAL(clicked()),this,SLOT(GoToMainAsGuest()));

}


void loginWidget::checkLogin()
{
        QFile file;
        QString fileContents;
        file.setFileName("userdata.json");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        fileContents = file.readAll();
        file.close();

        QJsonDocument jsonDoc= QJsonDocument::fromJson(fileContents.toUtf8());
        QJsonObject obj = jsonDoc.object();
        

        if(obj.contains(UserNameLine->text().replace(" ","")))
        {
            QJsonObject myUser = obj[UserNameLine->text().replace(" ","")].toObject();
        if (myUser["password"].toString()==PassWordLine->text())
        {
            //Add login attributes

            QFile config("config.json");
            config.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
            QJsonObject myuser;
            myuser.insert(QString("loggedon"),UserNameLine->text().replace(" ",""));
            QJsonDocument JsonDocument;
            JsonDocument.setObject(myuser);
            config.write(JsonDocument.toJson());
            config.close();

            menuWidget *menu = new menuWidget();
            menu->show();
            this->close();
            delete this;
        }
        else
        {
           ErrorMessage->setText("Username/Password do not match any account");
        }
        }
        else
        {
            ErrorMessage->setText("Username/Password do not match any account");
        }










//            if (UserNameLine->text() == username && PassWordLine->text() == password)
//            {
//                menuWidget *menuInit = new menuWidget();
//                menuInit->show();
//                this->close();
//            }



}

void loginWidget::GoToRegisterPage()
{
registerWidget *registerInit = new registerWidget();
registerInit->show();
this->close();
delete this;
}

void loginWidget::GoToMainAsGuest()
{
    QFile config("config.json");
    config.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    QJsonObject myuser;
    myuser.insert(QString("loggedon"),QString("guest"));
    QJsonDocument JsonDocument;
    JsonDocument.setObject(myuser);
    config.write(JsonDocument.toJson());
    config.close();

    menuWidget *menu = new menuWidget();
    menu->show();
    this->close();
    delete this;
}
