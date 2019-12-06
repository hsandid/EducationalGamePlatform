#include "game2scene.h"
#include <QDebug>
#include <algorithm>    // std::random_shuffle
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <string.h>
#include <menuwidget.h>

/**
 * \file game2scene.cpp
 * \brief Contains game2scene class definition
 *
 * Main game scene for Game 2. It is the container for all
 * visual elements and logic for Game 2.
 */

game2scene::game2scene(QObject *parent) :
    QGraphicsScene(parent)
{

    //Setting random seed based on time
    srand(time(0));

    //Settings the background board
    setBackgroundBrush(QBrush(QImage(":/images/background.jpg").scaledToHeight(768).scaledToWidth(1024)));
    setSceneRect(0,0,1024,768);



    //Need to reset the counter after every movement
    cardSelection = new int();
    *cardSelection=1;

    finalScorePlayer= new int();
    *finalScorePlayer=0;

    turnsPassed = new int();
    *turnsPassed =1;

    cardSelectionAdversary = new int();
    *cardSelectionAdversary=1;

    firstSelection = new int();
    *firstSelection=1;

    caboCaller = new int();
    *caboCaller=3;

    caboCalled = new bool();
    *caboCalled=false;

    lock = new bool();
    *lock=false;

    firstTurn = new bool(true);
    *firstTurn=true;
    cputurn = new bool(false);
    *cputurn = true;

    mystr = new QString("");

    CPU1 =new CPU();
    CPU2 =new CPU();




    drawPileCards = new QVector<int>();
    discardPileCards = new QVector<int>();

    initUI();
    initDrawPile();
    initDiscardPile();
    initAllCards();

    connect(exitButton, SIGNAL(clicked()), this,SLOT(exitgame_n_save()));




}

/**
 * @brief game2scene::load_game()
 *
 * Load existing game
 */


void game2scene::load_game()
{
    *firstTurn=false;
    discardPileCards->clear();
    drawPileCards->clear();

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

            QJsonArray cardvalues_json = myUser["cardvalue"].toArray();
            *playerCard1->cardValue=cardvalues_json[0].toInt();
            *playerCard2->cardValue=cardvalues_json[1].toInt();
            *playerCard3->cardValue=cardvalues_json[2].toInt();
            *playerCard4->cardValue=cardvalues_json[3].toInt();

            *CPU1Card1->cardValue=cardvalues_json[4].toInt();
            *CPU1Card2->cardValue=cardvalues_json[5].toInt();
            *CPU1Card3->cardValue=cardvalues_json[6].toInt();
            *CPU1Card4->cardValue=cardvalues_json[7].toInt();

            *CPU2Card1->cardValue=cardvalues_json[8].toInt();
            *CPU2Card2->cardValue=cardvalues_json[9].toInt();
            *CPU2Card3->cardValue=cardvalues_json[10].toInt();
            *CPU2Card4->cardValue=cardvalues_json[11].toInt();

            QJsonArray CPU1data_json = myUser["CPU1predictions"].toArray();
            for (int i=0;i<12;i++)
            {
                CPU1->CPUdataArray[i]=CPU1data_json[i].toInt();
            }

            QJsonArray CPU2data_json = myUser["CPU2predictions"].toArray();
            for (int i=0;i<12;i++)
            {
                CPU2->CPUdataArray[i]=CPU2data_json[i].toInt();
            }

            QJsonArray discard_json = myUser["discardpile"].toArray();
            for (int i=0;i<discard_json.size();i++)
            {
                discardPileCards->append(discard_json[i].toInt());
            }

            QJsonArray draw_json = myUser["drawpile"].toArray();
            for (int i=0;i<draw_json.size();i++)
            {
                drawPileCards->append(draw_json[i].toInt());
            }


//    QFile file(":/json/boarddata.json");
//    QString fileContents;
//    file.open(QIODevice::ReadOnly | QIODevice::Text);
//    fileContents = file.readAll();
//    file.close();

//    QJsonDocument jsonDoc= QJsonDocument::fromJson(fileContents.toUtf8());
//    QJsonObject obj = jsonDoc.object();



//    QJsonArray snakeInfo = obj["snakes"].toArray();
//    for (int i=0;i<14;i++)
//    {
//        snakePos[i]=snakeInfo[i].toInt();
//    }

//    QJsonArray ladderInfo = obj["ladders"].toArray();
//    for (int i=0;i<12;i++)
//    {
//        ladderPos[i]=ladderInfo[i].toInt();
//    }




//    usernameDisplay->setText("Username : "+userName);
//    fnameDisplay->setText("First Name : "+ myUser["fname"].toString());
//    lnameDisplay->setText("Last Name : "+ myUser["lname"].toString());
//    dobDisplay->setText("Date of Birth : "+ myUser["date_of_birth"].toString());
//    genderDisplay->setText("Gender : "+ myUser["gender"].toString());


QTimer::singleShot(2000,this, SLOT(gameLoop_main()));
}

/**
 * @brief game2scene::startCPUGame()
 *
 * Start new game
 */

void game2scene::startCPUGame()
{
QTimer::singleShot(2000,this, SLOT(gameLoop_main()));
}

/**
 * @brief game2scene::startCPUGame()
 *
 * Exit from in-progress game and save
 */


void game2scene::exitgame_n_save()
{
    //check wincondition

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


        if ( userName!="guest")
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
            myUser.insert(QString("game2_active"),QString("yes"));

            QJsonArray card_values;
            //Get card values array
            card_values.push_back(*playerCard1->cardValue);
            card_values.push_back(*playerCard2->cardValue);
            card_values.push_back(*playerCard3->cardValue);
            card_values.push_back(*playerCard4->cardValue);

            card_values.push_back(*CPU1Card1->cardValue);
            card_values.push_back(*CPU1Card2->cardValue);
            card_values.push_back(*CPU1Card3->cardValue);
            card_values.push_back(*CPU1Card4->cardValue);

            card_values.push_back(*CPU2Card1->cardValue);
            card_values.push_back(*CPU2Card2->cardValue);
            card_values.push_back(*CPU2Card3->cardValue);
            card_values.push_back(*CPU2Card4->cardValue);

            QJsonArray CPU1_values;
            //Get prediction values array CPU1
            for(int a=0;a<12;a++)
            {
                CPU1_values.push_back(CPU1->CPUdataArray[a]);
            }

            QJsonArray CPU2_values;
            //Get prediction values array CPU2
            for(int a=0;a<12;a++)
            {
                CPU2_values.push_back(CPU2->CPUdataArray[a]);
            }

            QJsonArray discard_values;
            //Get discard pile array
            for(int a=0;a<(discardPileCards->size());a++)
            {
                discard_values.push_back(discardPileCards->at(a));
            }

            QJsonArray draw_values;
            //Get draw pile array
            for(int a=0;a<(drawPileCards->size());a++)
            {
                draw_values.push_back(drawPileCards->at(a));
            }

            myUser.insert(QString("cardvalue"),QJsonValue(card_values));
            myUser.insert(QString("CPU1predictions"),QJsonValue(CPU1_values));
            myUser.insert(QString("CPU2predictions"),QJsonValue(CPU2_values));
            myUser.insert(QString("discardpile"),QJsonValue(discard_values));
            myUser.insert(QString("drawpile"),QJsonValue(draw_values));

//            myUser.insert(QString("p1pos"),*player1->position);
//            myUser.insert(QString("p2pos"),*player2->position);
//            if(!*playerTurn)
//            {
//                myUser.insert(QString("turn"),QString("p1"));
//            }
//            else
//            {
//                myUser.insert(QString("turn"),QString("p2"));
//            }
//            if(*CPU)
//            {
//                myUser.insert(QString("cpu"),QString("true"));
//            }
//            else
//            {
//                myUser.insert(QString("cpu"),QString("false"));
//            }
            objTwo.insert(userName,myUser);
            jsonDocTwo.setObject(objTwo);

            file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
            file.write(jsonDocTwo.toJson());
            file.close();
        }

        menuWidget *menu = new menuWidget();
        menu->show();
        QList<QGraphicsView *> views = this->views();
        for (int i=0;i<views.size();i++)
        {
            views.at(i)->close();
            views.at(i)->deleteLater();
        }


}

/**
 * @brief game2scene::initUI()
 *
 * Initialize the UI elements
 */

void game2scene::initUI()
{
    goLeft = new QPushButton("<");
    goRight = new QPushButton(">");
    goLeft->setGeometry(QRect(800, 640,80,40));
    goRight->setGeometry(QRect(880, 640,80,40));

    addWidget(goLeft);
    addWidget(goRight);

    takeDraw = new QPushButton("Draw Pile");
    takeDiscard = new QPushButton("Discard Pile");
    takeDraw->setGeometry(QRect(720, 640,80,40));
    takeDiscard->setGeometry(QRect(640, 640,80,40));

    addWidget(takeDiscard);
    addWidget(takeDraw);

    keep = new QPushButton("Keep Card");
    discard = new QPushButton("Discard Card");
    keep->setGeometry(QRect(640, 688,80,40));
    discard->setGeometry(QRect(720, 688,80,40));

    addWidget(keep);
    addWidget(discard);

    select = new QPushButton("Select Card");
    select->setGeometry(QRect(800, 688,80,40));
    addWidget(select);

    callCabo = new QPushButton("Call Cabo");
    callCabo->setGeometry(QRect(880, 688,80,40));
    addWidget(callCabo);

    exitButton = new QPushButton("Exit to Menu");
    exitButton->setGeometry(QRect(640, 730,320,40));
    addWidget(exitButton);


    //Adding text label
    text = new QGraphicsTextItem("Welcome to Cabo");
    text->setPos(200,536);
    text->setScale(1.2);
    text->setDefaultTextColor(Qt::white);
    addItem(text);

    drawpiletext = new QGraphicsTextItem("Draw Pile");
    drawpiletext->setPos(520,48);
    drawpiletext->setScale(1.5);
    drawpiletext->setDefaultTextColor(Qt::white);
    addItem(drawpiletext);

    discardpiletext = new QGraphicsTextItem("Discard Pile");
    discardpiletext->setPos(400,48);
    discardpiletext->setScale(1.5);
    discardpiletext->setDefaultTextColor(Qt::white);
    addItem(discardpiletext);

    opp1 = new QGraphicsTextItem("CPU 1");
    opp1->setPos(80,520);
    opp1->setScale(1.5);
    opp1->setDefaultTextColor(Qt::white);
    addItem(opp1);

    opp2 = new QGraphicsTextItem("CPU 2");
    opp2->setPos(896,520);
    opp2->setScale(1.5);
    opp2->setDefaultTextColor(Qt::white);
    addItem(opp2);

    //Disabling buttons temporarly
    keep->setEnabled(false);
    takeDiscard->setEnabled(false);
    takeDraw->setEnabled(false);
    discard->setEnabled(false);
    select->setEnabled(false);
    callCabo->setEnabled(false);
    goLeft->setEnabled(false);
    goRight->setEnabled(false);

}

/**
 * @brief game2scene::initDrawPile()
 *
 * Initialize the draw pile
 */

void game2scene::initDrawPile()
{
    for (int i=0;i<4;i++)
    {
        drawPileCards->append(1);
        drawPileCards->append(2);
        drawPileCards->append(3);
        drawPileCards->append(4);
        drawPileCards->append(5);
        drawPileCards->append(6);
        drawPileCards->append(7);
        drawPileCards->append(8);
        drawPileCards->append(9);
        drawPileCards->append(10);
        drawPileCards->append(11);
        drawPileCards->append(12);

    }

    for (int i=0;i<2;i++)
    {
        drawPileCards->append(0);
        drawPileCards->append(13);
    }

    std::random_shuffle(drawPileCards->begin(),drawPileCards->end());



    for(int i=0; i<drawPileCards->size(); i++)
    {
        qDebug()<<drawPileCards->at(i)<<endl;
    }

}

/**
 * @brief game2scene::initDiscardPile()
 *
 * Initialize the discard pile
 */

void game2scene::initDiscardPile()
{

    int temp = drawPileCards->at(drawPileCards->size()-1);
    discardPileCards->append(temp);


    discardPileCard= new card();
    *discardPileCard->cardValue=temp;
    discardPileCard->setCardPic();
    discardPileCard->setPosition(400,80,0);
    addItem(discardPileCard);
    drawPileCards->pop_back();


}

/**
 * @brief game2scene::initAllCards()
 *
 * Initialize all cards on the game scene
 */

void game2scene::initAllCards()
{



    //Player - Card 1
    int temp = drawPileCards->at(drawPileCards->size()-1);
    drawPileCards->pop_back();

    playerCard1 =  new card();
    *playerCard1->cardValue=temp;
    playerCard1->setPosition(120,648,0);
    addItem(playerCard1);


    //Player - Card 2
    temp = drawPileCards->at(drawPileCards->size()-1);
    drawPileCards->pop_back();

    playerCard2 =  new card();
    *playerCard2->cardValue=temp;
    playerCard2->setPosition(240,648,0);
    addItem(playerCard2);


    //Player - Card 3
    temp = drawPileCards->at(drawPileCards->size()-1);
    drawPileCards->pop_back();

    playerCard3 =  new card();
    *playerCard3->cardValue=temp;
    playerCard3->setPosition(360,648,0);
    addItem(playerCard3);


    //Player - Card 4
    temp = drawPileCards->at(drawPileCards->size()-1);
    drawPileCards->pop_back();

    playerCard4 =  new card();
    *playerCard4->cardValue=temp;
    playerCard4->setPosition(480,648,0);
    addItem(playerCard4);



    //CPU1 - Card 1
    temp = drawPileCards->at(drawPileCards->size()-1);
    drawPileCards->pop_back();

    CPU1Card1 =  new card();
    *CPU1Card1->cardValue=temp;
    CPU1Card1->setPosition(160,80,90);
    addItem(CPU1Card1);


    //CPU1 - Card 2
    temp = drawPileCards->at(drawPileCards->size()-1);
    drawPileCards->pop_back();

    CPU1Card2 =  new card();
    *CPU1Card2->cardValue=temp;
    CPU1Card2->setPosition(160,200,90);
    addItem(CPU1Card2);


    //CPU1 - Card 3
    temp = drawPileCards->at(drawPileCards->size()-1);
    drawPileCards->pop_back();

    CPU1Card3 =  new card();
    *CPU1Card3->cardValue=temp;
    CPU1Card3->setPosition(160,320,90);
    addItem(CPU1Card3);


    //CPU1 - Card 4
    temp = drawPileCards->at(drawPileCards->size()-1);
    drawPileCards->pop_back();

    CPU1Card4 =  new card();
    *CPU1Card4->cardValue=temp;
    CPU1Card4->setPosition(160,440,90);
    addItem(CPU1Card4);

    //CPU2 - Card 1
    temp = drawPileCards->at(drawPileCards->size()-1);
    drawPileCards->pop_back();

    CPU2Card1 =  new card();
    *CPU2Card1->cardValue=temp;
    CPU2Card1->setPosition(864,160,-90);
    addItem(CPU2Card1);

    //CPU2 - Card 2
    temp = drawPileCards->at(drawPileCards->size()-1);
    drawPileCards->pop_back();

    CPU2Card2 =  new card();
    *CPU2Card2->cardValue=temp;
    CPU2Card2->setPosition(864,280,-90);
    addItem(CPU2Card2);


    //CPU2 - Card 3
    temp = drawPileCards->at(drawPileCards->size()-1);
    drawPileCards->pop_back();

    CPU2Card3 =  new card();
    *CPU2Card3->cardValue=temp;
    CPU2Card3->setPosition(864,400,-90);
    addItem(CPU2Card3);


    //CPU2 - Card 4
    temp = drawPileCards->at(drawPileCards->size()-1);
    drawPileCards->pop_back();

    CPU2Card4 =  new card();
    *CPU2Card4->cardValue=temp;
    CPU2Card4->setPosition(864,520,-90);
    addItem(CPU2Card4);


    //Adding cross item
    cross = new QGraphicsPixmapItem();
    cross->setPixmap((QPixmap(":/images/cross.png")).scaled(24,24));
    //Change to false !
    cross->setVisible(false);
    //Keep both values for later use !
//    cross->setPos(148,688);
//    cross->setPos(96,104);
    addItem(cross);

    //Adding second cross item
    crossTemp = new QGraphicsPixmapItem();
    crossTemp->setPixmap((QPixmap(":/images/cross.png")).scaled(24,24));
    crossTemp->setVisible(false);
    addItem(crossTemp);



    //Draw Pile card
    temp = drawPileCards->at(drawPileCards->size()-1);
    drawPileCard = new card();
    *drawPileCard->cardValue=temp;

    drawPileCard->setPosition(520,80,0);
    addItem(drawPileCard);

    //Card for player display
    tempPlayerDisplay = new card();
    tempPlayerDisplay->setVisible(false);
    addItem(tempPlayerDisplay);


//    //REMOVE
//    playerCard1->setCardPic();
//    playerCard2->setCardPic();
//    playerCard3->setCardPic();
//    playerCard4->setCardPic();

//    CPU1Card1->setCardPic();
//    CPU1Card2->setCardPic();
//    CPU1Card3->setCardPic();
//    CPU1Card4->setCardPic();

//    CPU2Card1->setCardPic();
//    CPU2Card2->setCardPic();
//    CPU2Card3->setCardPic();
//    CPU2Card4->setCardPic();

//    //REMOVE

}

/**
 * @brief game2scene::gameLoop_main()
 *
 * Main game loop
 */

void game2scene::gameLoop_main()
{

//    //REMOVE
//    playerCard1->setCardPic();
//    playerCard2->setCardPic();
//    playerCard3->setCardPic();
//    playerCard4->setCardPic();

//    CPU1Card1->setCardPic();
//    CPU1Card2->setCardPic();
//    CPU1Card3->setCardPic();
//    CPU1Card4->setCardPic();

//    CPU2Card1->setCardPic();
//    CPU2Card2->setCardPic();
//    CPU2Card3->setCardPic();
//    CPU2Card4->setCardPic();

//    //REMOVE


    if(*firstTurn)
    {
        *firstTurn=false;
        checkTwoCards_startPlayer();
    }
    else if(*caboCalled && *caboCaller==1)
    {
        if(*lock)
        {
            QTimer::singleShot(3000,this, SLOT(checkFinalCabo()));
        }
        else
        {
            *lock=true;
            QTimer::singleShot(3000,this, SLOT(selectPile()));
        }
    }
    else if(*caboCalled && *caboCaller==2)
    {
        if(*lock)
        {
            QTimer::singleShot(3000,this, SLOT(checkFinalCabo()));
        }
        else
        {
            *lock=true;
            *mystr="";
            cpuActions_1();
            text->setPlainText(mystr->toUtf8());
            *discardPileCard->cardShown=false;
            discardPileCard->setCardPic();
            QTimer::singleShot(3000,this, SLOT(selectPile()));
        }
    }
    else
    {
        *turnsPassed=*turnsPassed+1;
        *cputurn=!*cputurn;
        if(*cputurn)
        {
            //Add cpu AI here for both CPU1 and CPU2


            QTimer::singleShot(3000,this, SLOT(cpuTurn()));
        }
        else
        {
           selectPile();
        }

    }

}
/**
 * @brief game2scene::cpuActions_1()
 *
 * CPU1 turn function
 */

void game2scene::cpuActions_1()
{
    srand(time(0)^3);
    int tempx=0;
    int temp=0;
    int temp2=0;
    int dazz =0;


    //CPU1 turn
    temp=CPU1->callCabo(*turnsPassed);

    if(temp==1&&!*caboCalled)
    {
        //CPU1 has called cabo
        //Change text and set caboCalled variable
        *caboCaller=1;
        *caboCalled=true;
        mystr->append("CPU1 calls Cabo!");


    }
    else
    {
        temp=CPU1->discard(discardPileCards->at(discardPileCards->size()-1));
        tempx = discardPileCards->at(discardPileCards->size()-1);

        if(temp==1)
        {
    //    take from discard / pos1
            //Update cards
            temp2=*CPU1Card1->cardValue;
            *CPU1Card1->cardValue=tempx;
            discardPileCards->pop_back();
            discardPileCards->append(temp2);

            //Update predictions
            CPU1->CPUdataArray[0]= tempx;
            mystr->append("CPU1 takes a card from discard pile, ");

        }
        else if (temp==2)
        {
    //    take from discard / pos2
            //Update cards
            temp2=*CPU1Card2->cardValue;
            *CPU1Card2->cardValue=tempx;
            discardPileCards->pop_back();
            discardPileCards->append(temp2);

            //Update predictions
            CPU1->CPUdataArray[1]= tempx;
            mystr->append("CPU1 takes a card from discard pile, ");
        }
        else if (temp==3)
        {
    //    take from discard / pos3
            //Update cards
            temp2=*CPU1Card3->cardValue;
            *CPU1Card3->cardValue=tempx;
            discardPileCards->pop_back();
            discardPileCards->append(temp2);

            //Update predictions
            CPU1->CPUdataArray[2]= tempx;
            mystr->append("CPU1 takes a card from discard pile, ");
        }
        else if(temp==4)
        {
    //    take from discard / pos4
            //Update cards
            temp2=*CPU1Card4->cardValue;
            *CPU1Card4->cardValue=tempx;
            discardPileCards->pop_back();
            discardPileCards->append(temp2);

            //Update predictions
            CPU1->CPUdataArray[3]= tempx;
            mystr->append("CPU1 takes a card from discard pile, ");
        }
        else
        {
            temp=CPU1->draw(drawPileCards->at(drawPileCards->size()-1));
            tempx =drawPileCards->at(drawPileCards->size()-1);

            if(temp==1)
            {
        //    take from draw / pos1
                temp2=*CPU1Card1->cardValue;
                *CPU1Card1->cardValue=tempx;
                drawPileCards->pop_back();
                drawPileCards->append(temp2);

                //Update predictions
                CPU1->CPUdataArray[0]= tempx;

            }
            else if (temp==2)
            {
        //    take from draw / pos2
                //    take from draw / pos1
                        temp2=*CPU1Card2->cardValue;
                        *CPU1Card2->cardValue=tempx;
                        drawPileCards->pop_back();
                        drawPileCards->append(temp2);

                        //Update predictions
                        CPU1->CPUdataArray[1]= tempx;
            }
            else if (temp==3)
            {
        //    take from draw / pos3
                //    take from draw / pos1
                        temp2=*CPU1Card3->cardValue;
                        *CPU1Card3->cardValue=tempx;
                        drawPileCards->pop_back();
                        drawPileCards->append(temp2);

                        //Update predictions
                        CPU1->CPUdataArray[2]= tempx;
            }
            else if(temp==4)
            {
        //    take from draw / pos4
                //    take from draw / pos1
                        temp2=*CPU1Card4->cardValue;
                        *CPU1Card4->cardValue=tempx;
                        drawPileCards->pop_back();
                        drawPileCards->append(temp2);

                        //Update predictions
                        CPU1->CPUdataArray[3]= tempx;
            }
            else if(temp==5)
            {
                int myval=0;
                myval = *CPU1->temp1;

        // 5 : peek - val1 and put in discard pile
                //Update predictions
                if(myval==1)
                {
                CPU1->CPUdataArray[0]= *CPU1Card1->cardValue;
                }
                else if (myval==2)
                {
                CPU1->CPUdataArray[1]= *CPU1Card2->cardValue;
                }
                else if (myval ==3)
                 {
                    CPU1->CPUdataArray[2]= *CPU1Card3->cardValue;
                }
                else if (myval==4)
                {
                    CPU1->CPUdataArray[3]= *CPU1Card4->cardValue;
                }

            }
            else if(temp==6)
            {

                // 6 : spy - val1 and put in discard pile
                        //Update cards

                        //Update predictions
                int myval=0;
                myval = *CPU1->temp1;

                if(myval==1)
                {
                CPU1->CPUdataArray[4]= *playerCard1->cardValue;
                }
                else if (myval==2)
                {
                CPU1->CPUdataArray[5]= *playerCard2->cardValue;
                }
                else if (myval ==3)
                 {
                    CPU1->CPUdataArray[6]= *playerCard3->cardValue;
                }
                else if (myval==4)
                {
                    CPU1->CPUdataArray[7]= *playerCard4->cardValue;
                }
                else if(myval==5)
                {
                CPU1->CPUdataArray[8]= *CPU2Card1->cardValue;
                }
                else if (myval==6)
                {
                CPU1->CPUdataArray[9]= *CPU2Card2->cardValue;
                }
                else if (myval ==7)
                 {
                    CPU1->CPUdataArray[10]= *CPU2Card3->cardValue;
                }
                else if (myval==8)
                {
                    CPU1->CPUdataArray[11]= *CPU2Card4->cardValue;
                }


            }
            else if(temp==7)
            {
        // 7 : swap- val1 / val2 and put in discard pile
                //Update cards

                //Update predictions
                int temp1=0;
                int temp2=0;
                int tempx=0;
                int tempy=0;
                tempx=*CPU1->temp1;
                tempy=*CPU1->temp2;
                dazz=tempy;

                if(tempy==1)
                {
                    temp1=*playerCard1->cardValue;

                }


                else if (tempy==2)
                {
                    temp1=*playerCard2->cardValue;
                }


                else if (tempy==3 )
                {
                    temp1=*playerCard3->cardValue;
                }

                else if (tempy==4  )
                {
                    temp1=*playerCard4->cardValue;
                }
                else if (tempy==5)
                {
                    temp1=*CPU2Card1->cardValue;
                }


                else if (tempy==6 )
                {
                    temp1=*CPU2Card2->cardValue;
                }

                else if (tempy==7 )
                {
                    temp1=*CPU2Card3->cardValue;
                }
                else if (tempy==8)
                {
                    temp1=*CPU2Card4->cardValue;
                }



                 if(tempx==1)
                 {
                     temp2=*CPU1Card1->cardValue;
                     *CPU1Card1->cardValue=temp1;
                     CPU1->CPUdataArray[0]=temp1;
                 }


                 else if ( tempx==2)
                 {
                     temp2=*CPU1Card2->cardValue;
                     *CPU1Card2->cardValue=temp1;
                     CPU1->CPUdataArray[1]=temp1;

                 }


                 else if (tempx==3 )
                 {
                     temp2=*CPU1Card3->cardValue;
                     *CPU1Card3->cardValue=temp1;
                     CPU1->CPUdataArray[2]=temp1;
                 }

                 else if (tempx==4)
                 {
                     temp2=*CPU1Card4->cardValue;
                     *CPU1Card4->cardValue=temp1;
                     CPU1->CPUdataArray[3]=temp1;
                 }

                 if(tempy==1)
                 {
                     *playerCard1->cardValue=temp2;
                     CPU1->CPUdataArray[4]=temp1;

                 }


                 else if (tempy==2)
                 {
                      *playerCard2->cardValue=temp2;
                     CPU1->CPUdataArray[5]=temp1;
                 }


                 else if (tempy==3 )
                 {
                     *playerCard3->cardValue=temp2;
                     CPU1->CPUdataArray[6]=temp1;
                 }

                 else if (tempy==4  )
                 {
                      *playerCard4->cardValue=temp2;
                     CPU1->CPUdataArray[7]=temp1;
                 }
                 else if (tempy==5)
                 {
                      *CPU2Card1->cardValue=temp2;
                     CPU1->CPUdataArray[8]=temp1;
                 }


                 else if (tempy==6 )
                 {
                     *CPU2Card2->cardValue=temp2;
                     CPU1->CPUdataArray[9]=temp1;
                 }

                 else if (tempy==7 )
                 {
                     *CPU2Card3->cardValue=temp2;
                     CPU1->CPUdataArray[10]=temp1;
                 }
                 else if (tempy==8)
                 {
                     *CPU2Card4->cardValue=temp2;
                     CPU1->CPUdataArray[11]=temp1;
                 }
            }
            else if(temp==0)
            {
        // 0 : do not take from draw and put in discard pile

                int mayval=0;
                mayval=drawPileCards->at(drawPileCards->size()-1);
                drawPileCards->pop_back();
                discardPileCards->append(mayval);
            }

            if(temp==0 )
            {
                mystr->append("CPU1 takes from draw pile and discard it, ");
            }
            else if( temp==1 || temp==2 || temp==3 || temp==4)
            {
                mystr->append("CPU1 takes a card from the draw pile, ");
            }
            else if(temp==5)
            {
                mystr->append("CPU1 takes a peek at one of his cards, ");
            }
            else if(temp==6)
            {
                mystr->append("CPU1 takes a peek at another player's cards, ");
            }
            else if(temp==7)
            {
                if (dazz<=4)
                {
                    mystr->append("CPU1 swaps a card with the human player, ");
                }
                else
                {
                    mystr->append("CPU1 swaps a card with CPU2, ");
                }
            }
        }


    }



    checkDrawPile_amount_CPUs();
}

/**
 * @brief game2scene::cpuActions_2()
 *
 * CPU2 turn function
 */

void game2scene::cpuActions_2()
{

    srand(time(0));
    int tempx=0;
    int temp=0;
    int temp2=0;
    int dazz =0;



    //CPU2 turn

    temp=CPU2->callCabo(*turnsPassed);

    if(temp==1&&!*caboCalled )
    {
        //CPU2 has called cabo
        //Change text and set caboCalled variable
        *caboCaller=2;
        *caboCalled=true;
        mystr->append("CPU2 calls Cabo!");

    }
    else
    {
        temp=CPU2->discard(discardPileCards->at(discardPileCards->size()-1));
        tempx = discardPileCards->at(discardPileCards->size()-1);

        if(temp==1)
        {
    //    take from discard / pos1
            //Update cards
            temp2=*CPU2Card1->cardValue;
            *CPU2Card1->cardValue=tempx;
            discardPileCards->pop_back();
            discardPileCards->append(temp2);

            //Update predictions
            CPU2->CPUdataArray[0]= tempx;
            mystr->append("CPU2 takes a card from discard pile, ");

        }
        else if (temp==2)
        {
    //    take from discard / pos2
            //Update cards
            temp2=*CPU2Card2->cardValue;
            *CPU2Card2->cardValue=tempx;
            discardPileCards->pop_back();
            discardPileCards->append(temp2);

            //Update predictions
            CPU2->CPUdataArray[1]= tempx;
            mystr->append("CPU2 takes a card from discard pile, ");
        }
        else if (temp==3)
        {
    //    take from discard / pos3
            //Update cards
            temp2=*CPU2Card3->cardValue;
            *CPU2Card3->cardValue=tempx;
            discardPileCards->pop_back();
            discardPileCards->append(temp2);

            //Update predictions
            CPU2->CPUdataArray[2]= tempx;
            mystr->append("CPU2 takes a card from discard pile, ");
        }
        else if(temp==4)
        {
    //    take from discard / pos4
            //Update cards
            temp2=*CPU2Card4->cardValue;
            *CPU2Card4->cardValue=tempx;
            discardPileCards->pop_back();
            discardPileCards->append(temp2);

            //Update predictions
            CPU2->CPUdataArray[3]= tempx;
            mystr->append("CPU2 takes a card from discard pile, ");
        }

        else
        {
            temp=CPU2->draw(drawPileCards->at(drawPileCards->size()-1));
            tempx =drawPileCards->at(drawPileCards->size()-1);

            if(temp==1)
            {
        //    take from draw / pos1
                temp2=*CPU2Card1->cardValue;
                *CPU2Card1->cardValue=tempx;
                drawPileCards->pop_back();
                drawPileCards->append(temp2);

                //Update predictions
                CPU2->CPUdataArray[0]= tempx;

            }
            else if (temp==2)
            {
        //    take from draw / pos2
                //    take from draw / pos1
                        temp2=*CPU2Card2->cardValue;
                        *CPU2Card2->cardValue=tempx;
                        drawPileCards->pop_back();
                        drawPileCards->append(temp2);

                        //Update predictions
                        CPU2->CPUdataArray[1]= tempx;
            }
            else if (temp==3)
            {
        //    take from draw / pos3
                //    take from draw / pos1
                        temp2=*CPU2Card3->cardValue;
                        *CPU2Card3->cardValue=tempx;
                        drawPileCards->pop_back();
                        drawPileCards->append(temp2);

                        //Update predictions
                        CPU2->CPUdataArray[2]= tempx;
            }
            else if(temp==4)
            {
        //    take from draw / pos4
                //    take from draw / pos1
                        temp2=*CPU2Card4->cardValue;
                        *CPU2Card4->cardValue=tempx;
                        drawPileCards->pop_back();
                        drawPileCards->append(temp2);

                        //Update predictions
                        CPU2->CPUdataArray[3]= tempx;
            }
            else if(temp==5)
            {
                int myval=0;
                myval = *CPU2->temp1;

        // 5 : peek - val1 and put in discard pile
                //Update predictions
                if(myval==1)
                {
                CPU2->CPUdataArray[0]= *CPU2Card1->cardValue;
                }
                else if (myval==2)
                {
                CPU2->CPUdataArray[1]= *CPU2Card2->cardValue;
                }
                else if (myval ==3)
                 {
                    CPU2->CPUdataArray[2]= *CPU2Card3->cardValue;
                }
                else if (myval==4)
                {
                    CPU2->CPUdataArray[3]= *CPU2Card4->cardValue;
                }

            }
            else if(temp==6)
            {

                // 6 : spy - val1 and put in discard pile
                        //Update cards

                        //Update predictions
                int myval=0;
                myval = *CPU2->temp1;

                if(myval==1)
                {
                CPU2->CPUdataArray[4]= *playerCard1->cardValue;
                }
                else if (myval==2)
                {
                CPU2->CPUdataArray[5]= *playerCard2->cardValue;
                }
                else if (myval ==3)
                 {
                    CPU2->CPUdataArray[6]= *playerCard3->cardValue;
                }
                else if (myval==4)
                {
                    CPU2->CPUdataArray[7]= *playerCard4->cardValue;
                }
                else if(myval==5)
                {
                CPU2->CPUdataArray[8]= *CPU1Card1->cardValue;
                }
                else if (myval==6)
                {
                CPU2->CPUdataArray[9]= *CPU1Card2->cardValue;
                }
                else if (myval ==7)
                 {
                    CPU2->CPUdataArray[10]= *CPU1Card3->cardValue;
                }
                else if (myval==8)
                {
                    CPU2->CPUdataArray[11]= *CPU1Card4->cardValue;
                }


            }
            else if(temp==7)
            {
        // 7 : swap- val1 / val2 and put in discard pile
                //Update cards

                //Update predictions
                int temp1=0;
                int temp2=0;
                int tempx=0;
                int tempy=0;
                tempx=*CPU2->temp1;
                tempy=*CPU2->temp2;
                dazz=tempy;

                if(tempy==1)
                {
                    temp1=*playerCard1->cardValue;

                }


                else if (tempy==2)
                {
                    temp1=*playerCard2->cardValue;
                }


                else if (tempy==3 )
                {
                    temp1=*playerCard3->cardValue;
                }

                else if (tempy==4  )
                {
                    temp1=*playerCard4->cardValue;
                }
                else if (tempy==5)
                {
                    temp1=*CPU1Card1->cardValue;
                }


                else if (tempy==6 )
                {
                    temp1=*CPU1Card2->cardValue;
                }

                else if (tempy==7 )
                {
                    temp1=*CPU1Card3->cardValue;
                }
                else if (tempy==8)
                {
                    temp1=*CPU1Card4->cardValue;
                }



                 if(tempx==1)
                 {
                     temp2=*CPU2Card1->cardValue;
                     *CPU2Card1->cardValue=temp1;
                     CPU2->CPUdataArray[0]=temp1;
                 }


                 else if ( tempx==2)
                 {
                     temp2=*CPU2Card2->cardValue;
                     *CPU2Card2->cardValue=temp1;
                     CPU2->CPUdataArray[1]=temp1;

                 }


                 else if (tempx==3 )
                 {
                     temp2=*CPU2Card3->cardValue;
                     *CPU2Card3->cardValue=temp1;
                     CPU2->CPUdataArray[2]=temp1;
                 }

                 else if (tempx==4)
                 {
                     temp2=*CPU2Card4->cardValue;
                     *CPU2Card4->cardValue=temp1;
                     CPU2->CPUdataArray[3]=temp1;
                 }

                 if(tempy==1)
                 {
                     *playerCard1->cardValue=temp2;
                     CPU2->CPUdataArray[4]=temp1;

                 }


                 else if (tempy==2)
                 {
                      *playerCard2->cardValue=temp2;
                     CPU2->CPUdataArray[5]=temp1;
                 }


                 else if (tempy==3 )
                 {
                     *playerCard3->cardValue=temp2;
                     CPU2->CPUdataArray[6]=temp1;
                 }

                 else if (tempy==4  )
                 {
                      *playerCard4->cardValue=temp2;
                     CPU2->CPUdataArray[7]=temp1;
                 }
                 else if (tempy==5)
                 {
                      *CPU1Card1->cardValue=temp2;
                     CPU2->CPUdataArray[8]=temp1;
                 }


                 else if (tempy==6 )
                 {
                     *CPU1Card2->cardValue=temp2;
                     CPU2->CPUdataArray[9]=temp1;
                 }

                 else if (tempy==7 )
                 {
                     *CPU1Card3->cardValue=temp2;
                     CPU2->CPUdataArray[10]=temp1;
                 }
                 else if (tempy==8)
                 {
                     *CPU1Card4->cardValue=temp2;
                     CPU2->CPUdataArray[11]=temp1;
                 }
            }
            else if(temp==0)
            {
        // 0 : do not take from draw and put in discard pile

                int mayval=0;
                mayval=drawPileCards->at(drawPileCards->size()-1);
                drawPileCards->pop_back();
                discardPileCards->append(mayval);
            }

            if(temp==0 )
            {
                mystr->append("CPU2 takes from draw pile and discard it, ");
            }
            else if( temp==1 || temp==2 || temp==3 || temp==4)
            {
                mystr->append("CPU2 takes a card from the draw pile, ");
            }
            else if(temp==5)
            {
                mystr->append("CPU2 takes a peek at one of his cards, ");
            }
            else if(temp==6)
            {
                mystr->append("CPU2 takes a peek at another player's cards, ");
            }
            else if(temp==7)
            {
                if (dazz<=4)
                {
                    mystr->append("CPU2 swaps a card with the human player, ");
                }
                else
                {
                    mystr->append("CPU2 swaps a card with CPU1, ");
                }
            }
        }


    }



    checkDrawPile_amount_CPUs();


}

/**
 * @brief game2scene::cpuTurn()
 *
 * Handle CPU1 and CPU2 turn
 */

void game2scene::cpuTurn()
{
    *mystr= "";
    cpuActions_1();
    cpuActions_2();
    text->setPlainText(mystr->toUtf8());
    *discardPileCard->cardShown=false;
    discardPileCard->setCardPic();
    QTimer::singleShot(6000,this, SLOT(gameLoop_main()));

}

/**
 * @brief game2scene::goLeftMoveAdv()
 *
 * Move left when selecting between adversary cards
 */

void game2scene::goLeftMoveAdv()
{
    cross->setFocus();



    *cardSelectionAdversary= *cardSelectionAdversary-1;
    if (*cardSelectionAdversary==0)
    {
        *cardSelectionAdversary=8;
    }

    qDebug() << *cardSelectionAdversary<<endl;

            if(*cardSelectionAdversary==1)
            {
                cross->setPos(96,104);

            }


            if (*cardSelectionAdversary==2 )
            {
                cross->setPos(96,224);

            }


            if (*cardSelectionAdversary==3 )
            {
                cross->setPos(96,344);

            }

             if (*cardSelectionAdversary==4 )
            {
                cross->setPos(96,464);

            }


             if (*cardSelectionAdversary==5 )
            {
                 cross->setPos(904,104);

            }


             if (*cardSelectionAdversary==6 )
            {
                cross->setPos(904,224);

            }


             if (*cardSelectionAdversary==7 )
            {
                cross->setPos(904,344);

            }


             if (*cardSelectionAdversary==8 )
            {
                cross->setPos(904,464);

            }




}

/**
 * @brief game2scene::goRightMoveAdv()
 *
 * Move right when selecting between adversary cards
 */

void game2scene::goRightMoveAdv()
{
    cross->setFocus();


    *cardSelectionAdversary= *cardSelectionAdversary+1;
    if (*cardSelectionAdversary==9)
    {
        *cardSelectionAdversary=1;
    }

    qDebug() << *cardSelectionAdversary<<endl;


            if(*cardSelectionAdversary==1)
            {
                cross->setPos(96,104);

            }


            if (*cardSelectionAdversary==2 )
            {
                cross->setPos(96,224);

            }


            if (*cardSelectionAdversary==3 )
            {
                cross->setPos(96,344);

            }

             if (*cardSelectionAdversary==4 )
            {
                cross->setPos(96,464);

            }


             if (*cardSelectionAdversary==5 )
            {
                 cross->setPos(904,104);

            }


             if (*cardSelectionAdversary==6 )
            {
                cross->setPos(904,224);

            }


             if (*cardSelectionAdversary==7 )
            {
                cross->setPos(904,344);

            }


             if (*cardSelectionAdversary==8 )
            {
                cross->setPos(904,464);

            }



}

/**
 * @brief game2scene::goLeftMove()
 *
 * Move left when selecting between player cards
 */

void game2scene::goLeftMove()
{
    cross->setFocus();

    *cardSelection= *cardSelection-1;
    if (*cardSelection==0)
    {
        *cardSelection=4;
    }

    qDebug() << *cardSelection<<endl;


        if(*cardSelection==1 )
        {
            cross->setPos(148,688);

        }


        if (*cardSelection==2 )
        {
            cross->setPos(264,688);

        }


        if (*cardSelection==3 )
        {
            cross->setPos(384,688);

        }

         if (*cardSelection==4 )
        {
            cross->setPos(504,688);

        }


}

/**
 * @brief game2scene::goRightMove()
 *
 * Move right when selecting between player cards
 */

void game2scene::goRightMove()
{
    cross->setFocus();

    *cardSelection= *cardSelection+1;
    if (*cardSelection==5)
    {
        *cardSelection=1;
    }

    qDebug() << *cardSelection<<endl;

            if(*cardSelection==1 )
            {
                cross->setPos(148,688);

            }


            if (*cardSelection==2 )
            {
                cross->setPos(264,688);

            }


            if (*cardSelection==3 )
            {
                cross->setPos(384,688);

            }

             if (*cardSelection==4 )
            {
                cross->setPos(504,688);

            }
}

/**
 * @brief game2scene::checkTwoCards_startPlayer()
 *
 * Let the player check two of his cards (Phase1)
 */

void game2scene::checkTwoCards_startPlayer()
{

    select->setEnabled(true);
    goLeft->setEnabled(true);
    goRight->setEnabled(true);

    text->setPlainText("Select two cards to check on your deck");
    cross->setPos(148,688);
    *cardSelection=1;
    cross->setVisible(true);



    connect(goLeft, SIGNAL(clicked()), this,SLOT(goLeftMove()));
    connect(goRight, SIGNAL(clicked()), this,SLOT(goRightMove()));
    connect(select, SIGNAL(clicked()), this,SLOT(getTwoCards_checkPhase1()));

}

/**
 * @brief game2scene::checkOneCards_startPlayer()
 *
 * Let the player check one of his cards (Phase1)
 */

void game2scene::checkOneCards_startPlayer()
{

    select->setEnabled(true);
    goLeft->setEnabled(true);
    goRight->setEnabled(true);

    text->setPlainText("Select one card to check on your deck");
    cross->setPos(148,688);
    *cardSelection=1;
    cross->setVisible(true);



    connect(goLeft, SIGNAL(clicked()), this,SLOT(goLeftMove()));
    connect(goRight, SIGNAL(clicked()), this,SLOT(goRightMove()));
    connect(select, SIGNAL(clicked()), this,SLOT(getOneCards_checkPhase1()));

}

/**
 * @brief game2scene::checkOneCards_checkPhase1()
 *
 * Let the player check one of his cards (Phase2)
 */

void game2scene::getOneCards_checkPhase1()
{


    qDebug() << "p2 "<<*cardSelection<<" "<<*firstSelection<<endl;


    if(*cardSelection==1)
    {
        playerCard1->setCardPic();
    }


    else if (*cardSelection==2)
    {
        playerCard2->setCardPic();
    }


    else if (*cardSelection==3 )
    {
        playerCard3->setCardPic();
    }

    else if (*cardSelection==4  )
    {
        playerCard4->setCardPic();
    }


      cross->setVisible(false);
      select->setEnabled(false);
      goLeft->setEnabled(false);
      goRight->setEnabled(false);

      qDebug() << "p2 "<< *firstSelection<<" "<< *cardSelection<<endl;

      disconnect(goLeft, SIGNAL(clicked()), this,SLOT(goLeftMove()));
      disconnect(goRight, SIGNAL(clicked()), this,SLOT(goRightMove()));
      disconnect(select, SIGNAL(clicked()), this,SLOT(getOneCards_checkPhase1()));
      QTimer::singleShot(2000,this, SLOT(getOneCards_checkPhase2()));

}

/**
 * @brief game2scene::getOneCards_checkPhase2()
 *
 * Let the player check one of his cards (Phase2)
 */

void game2scene::getOneCards_checkPhase2()
{


    qDebug() << "p2 "<<*cardSelection<<" "<<*firstSelection<<endl;


    if(*cardSelection==1)
    {
        playerCard1->setCardPic();
    }


    else if (*cardSelection==2)
    {
        playerCard2->setCardPic();
    }


    else if (*cardSelection==3 )
    {
        playerCard3->setCardPic();
    }

    else if (*cardSelection==4  )
    {
        playerCard4->setCardPic();
    }



      select->setEnabled(false);
      goLeft->setEnabled(false);
      goRight->setEnabled(false);

      qDebug() << "p2 "<< *firstSelection<<" "<< *cardSelection<<endl;


//      QTimer::singleShot(2000,this, SLOT(checkOneCards_startPlayer()));
      //Add callback to main game loop
      //Add callback to card check
      QTimer::singleShot(2000,this, SLOT(checkDrawPile_amount()));

}

/**
 * @brief game2scene::getTwoCards_checkPhase1()
 *
 * Let the player check two of his cards (Phase2)
 */

void game2scene::getTwoCards_checkPhase1()
{

    crossTemp->setVisible(true);


 if(*cardSelection==1 )
 {
     crossTemp->setPos(148,600);
     *firstSelection=1;


 }


 if (*cardSelection==2 )
 {
     crossTemp->setPos(264,600);
     *firstSelection=2;


 }


 if (*cardSelection==3 )
 {
     crossTemp->setPos(384,600);
     *firstSelection=3;


 }

  if (*cardSelection==4 )
 {
     crossTemp->setPos(504,600);
     *firstSelection=4;

 }

   qDebug() << "p1 "<<*cardSelection<<" "<< *firstSelection<<endl;
   *cardSelection=1;
  cross->setPos(148,688);

  disconnect(select, SIGNAL(clicked()), this,SLOT(getTwoCards_checkPhase1()));
  connect(select, SIGNAL(clicked()), this,SLOT(getTwoCards_checkPhase2()));

  return;
}

/**
 * @brief game2scene::getTwoCards_checkPhase2()
 *
 * Let the player check two of his cards (Phase3)
 */

void game2scene::getTwoCards_checkPhase2()
{


    qDebug() << "p2 "<<*cardSelection<<" "<<*firstSelection<<endl;

 if(*cardSelection!=*firstSelection)
 {
    crossTemp->setVisible(false);
    cross->setVisible(false);

    if(*cardSelection==1)
    {
        playerCard1->setCardPic();
    }


    else if (*cardSelection==2)
    {
        playerCard2->setCardPic();
    }


    else if (*cardSelection==3 )
    {
        playerCard3->setCardPic();
    }

    else if (*cardSelection==4  )
    {
        playerCard4->setCardPic();
    }

     if(*firstSelection==1)
     {
         playerCard1->setCardPic();
     }


     else if ( *firstSelection==2)
     {
         playerCard2->setCardPic();
     }


     else if (*firstSelection==3 )
     {
         playerCard3->setCardPic();
     }

     else if (*firstSelection==4)
     {
         playerCard4->setCardPic();
     }

      select->setEnabled(false);
      goLeft->setEnabled(false);
      goRight->setEnabled(false);

      qDebug() << "p2 "<< *firstSelection<<" "<< *cardSelection<<endl;

      disconnect(select, SIGNAL(clicked()), this,SLOT(getTwoCards_checkPhase2()));
      QTimer::singleShot(2000,this, SLOT(getTwoCards_checkPhase3()));
 }
}

/**
 * @brief game2scene::getTwoCards_checkPhase3()
 *
 * Let the player check two of his cards (Phase4)
 */

void game2scene::getTwoCards_checkPhase3()
{

    if(*cardSelection==1)
    {
        playerCard1->setCardPic();
    }


    else if (*cardSelection==2)
    {
        playerCard2->setCardPic();
    }


    else if (*cardSelection==3 )
    {
        playerCard3->setCardPic();
    }

    else if (*cardSelection==4  )
    {
        playerCard4->setCardPic();
    }

     if(*firstSelection==1)
     {
         playerCard1->setCardPic();
     }


     else if ( *firstSelection==2)
     {
         playerCard2->setCardPic();
     }


     else if (*firstSelection==3 )
     {
         playerCard3->setCardPic();
     }

     else if (*firstSelection==4)
     {
         playerCard4->setCardPic();
     }

     qDebug() << "p3 "<<*cardSelection<<" "<< *firstSelection<<endl;
    *cardSelection=1;
     cross->setPos(148,688);

     qDebug() << "p3 "<<*cardSelection<<" "<< *firstSelection<<endl;


     disconnect(goLeft, SIGNAL(clicked()), this,SLOT(goLeftMove()));
     disconnect(goRight, SIGNAL(clicked()), this,SLOT(goRightMove()));
     //Add callback to main game loop
     QTimer::singleShot(2000,this, SLOT(gameLoop_main()));

}

/**
 * @brief game2scene::swapCard_withenemy_phase1()
 *
 * Let the player swap one of his cards with an opponent (Phase1)
 */

void game2scene::swapCard_withenemy_phase1()
{

    select->setEnabled(true);
    goLeft->setEnabled(true);
    goRight->setEnabled(true);
    cross->setPos(148,688);
    cross->setVisible(true);
    *cardSelection=1;
    *cardSelectionAdversary=1;

    text->setPlainText("Swap a card with another player");


    connect(goLeft, SIGNAL(clicked()), this,SLOT(goLeftMove()));
    connect(goRight, SIGNAL(clicked()), this,SLOT(goRightMove()));
    connect(select, SIGNAL(clicked()), this,SLOT(swapCard_withenemy_phase2()));

}

/**
 * @brief game2scene::swapCard_withenemy_phase2()
 *
 * Let the player swap one of his cards with an opponent (Phase2)
 */

void game2scene::swapCard_withenemy_phase2()
{

    crossTemp->setVisible(true);


 if(*cardSelection==1 )
 {
     crossTemp->setPos(148,600);
     *firstSelection=1;


 }


 if (*cardSelection==2 )
 {
     crossTemp->setPos(264,600);
     *firstSelection=2;


 }


 if (*cardSelection==3 )
 {
     crossTemp->setPos(384,600);
     *firstSelection=3;


 }

  if (*cardSelection==4 )
 {
     crossTemp->setPos(504,600);
     *firstSelection=4;

 }

   qDebug() << "p1 "<<*cardSelection<<" "<< *firstSelection<<endl;
   *cardSelectionAdversary=1;
   cross->setPos(96,104);

  disconnect(select, SIGNAL(clicked()), this,SLOT(swapCard_withenemy_phase2()));
  disconnect(goLeft, SIGNAL(clicked()), this,SLOT(goLeftMove()));
  disconnect(goRight, SIGNAL(clicked()), this,SLOT(goRightMove()));
  connect(goLeft, SIGNAL(clicked()), this,SLOT(goLeftMoveAdv()));
  connect(goRight, SIGNAL(clicked()), this,SLOT(goRightMoveAdv()));
  connect(select, SIGNAL(clicked()), this,SLOT(swapCard_withenemy_phase3()));

}

/**
 * @brief game2scene::swapCard_withenemy_phase3()
 *
 * Let the player swap one of his cards with an opponent (Phase3)
 */

void game2scene::swapCard_withenemy_phase3()
{


    qDebug() << "p2 "<<*cardSelection<<" "<<*firstSelection<<endl;


    crossTemp->setVisible(false);
    cross->setVisible(false);

    int temp1=0;
    int temp2=0;

    if(*cardSelectionAdversary==1)
    {
        temp1=*CPU1Card1->cardValue;

    }


    else if (*cardSelectionAdversary==2)
    {
        temp1=*CPU1Card2->cardValue;
    }


    else if (*cardSelectionAdversary==3 )
    {
        temp1=*CPU1Card3->cardValue;
    }

    else if (*cardSelectionAdversary==4  )
    {
        temp1=*CPU1Card4->cardValue;
    }
    else if (*cardSelectionAdversary==5)
    {
        temp1=*CPU2Card1->cardValue;
    }


    else if (*cardSelectionAdversary==6 )
    {
        temp1=*CPU2Card2->cardValue;
    }

    else if (*cardSelectionAdversary==7 )
    {
        temp1=*CPU2Card3->cardValue;
    }
    else if (*cardSelectionAdversary==8)
    {
        temp1=*CPU2Card4->cardValue;
    }



     if(*firstSelection==1)
     {
         temp2=*playerCard1->cardValue;
         *playerCard1->cardValue=temp1;

         CPU1->CPUdataArray[4]=temp1;
         CPU2->CPUdataArray[4]=temp1;
     }


     else if ( *firstSelection==2)
     {
         temp2=*playerCard2->cardValue;
         *playerCard2->cardValue=temp1;
         CPU1->CPUdataArray[5]=temp1;
         CPU2->CPUdataArray[5]=temp1;

     }


     else if (*firstSelection==3 )
     {
         temp2=*playerCard3->cardValue;
         *playerCard3->cardValue=temp1;
         CPU1->CPUdataArray[6]=temp1;
         CPU2->CPUdataArray[6]=temp1;
     }

     else if (*firstSelection==4)
     {
         temp2=*playerCard4->cardValue;
         *playerCard4->cardValue=temp1;
         CPU1->CPUdataArray[7]=temp1;
         CPU2->CPUdataArray[7]=temp1;
     }

     if(*cardSelectionAdversary==1)
     {
         *CPU1Card1->cardValue=temp2;
         CPU1->CPUdataArray[0]=temp2;
         CPU2->CPUdataArray[8]=temp2;

     }


     else if (*cardSelectionAdversary==2)
     {
          *CPU1Card2->cardValue=temp2;
         CPU1->CPUdataArray[1]=temp2;
         CPU2->CPUdataArray[9]=temp2;
     }


     else if (*cardSelectionAdversary==3 )
     {
         *CPU1Card3->cardValue=temp2;
         CPU1->CPUdataArray[2]=temp2;
         CPU2->CPUdataArray[10]=temp2;
     }

     else if (*cardSelectionAdversary==4  )
     {
          *CPU1Card4->cardValue=temp2;
         CPU1->CPUdataArray[3]=temp2;
         CPU2->CPUdataArray[11]=temp2;
     }
     else if (*cardSelectionAdversary==5)
     {
          *CPU2Card1->cardValue=temp2;
         CPU2->CPUdataArray[0]=temp2;
         CPU1->CPUdataArray[8]=temp2;
     }


     else if (*cardSelectionAdversary==6 )
     {
         *CPU2Card2->cardValue=temp2;
         CPU2->CPUdataArray[1]=temp2;
         CPU1->CPUdataArray[9]=temp2;
     }

     else if (*cardSelectionAdversary==7 )
     {
         *CPU2Card3->cardValue=temp2;
         CPU2->CPUdataArray[2]=temp2;
         CPU1->CPUdataArray[10]=temp2;
     }
     else if (*cardSelectionAdversary==8)
     {
         *CPU2Card4->cardValue=temp2;
         CPU2->CPUdataArray[3]=temp2;
         CPU1->CPUdataArray[11]=temp2;
     }

      select->setEnabled(false);
      goLeft->setEnabled(false);
      goRight->setEnabled(false);

      qDebug() << "p2 "<< *firstSelection<<" "<< *cardSelection<<endl;

      disconnect(goLeft, SIGNAL(clicked()), this,SLOT(goLeftMoveAdv()));
      disconnect(goRight, SIGNAL(clicked()), this,SLOT(goRightMoveAdv()));
      disconnect(select, SIGNAL(clicked()), this,SLOT(swapCard_withenemy_phase3()));
//      QTimer::singleShot(2000,this, SLOT(swapCard_withenemy_phase1()));
      //Add callback to main game loop
      //Add callback to card check
      QTimer::singleShot(2000,this, SLOT(checkDrawPile_amount()));
}

/**
 * @brief game2scene::spyCard_withenemy_phase1()
 *
 * Let the player spy on the card of an opponent (Phase1)
 */

void game2scene::spyCard_withenemy_phase1()
{

    select->setEnabled(true);
    goLeft->setEnabled(true);
    goRight->setEnabled(true);
    cross->setPos(96,104);
    cross->setVisible(true);
    *cardSelection=1;
    *cardSelectionAdversary=1;

    text->setPlainText("Spy on another player's card");


    connect(goLeft, SIGNAL(clicked()), this,SLOT(goLeftMoveAdv()));
    connect(goRight, SIGNAL(clicked()), this,SLOT(goRightMoveAdv()));
    connect(select, SIGNAL(clicked()), this,SLOT(spyCard_withenemy_phase2()));

}

/**
 * @brief game2scene::spyCard_withenemy_phase2()
 *
 * Let the player spy on the card of an opponent (Phase2)
 */

void game2scene::spyCard_withenemy_phase2()
{

    disconnect(goLeft, SIGNAL(clicked()), this,SLOT(goLeftMoveAdv()));
    disconnect(goRight, SIGNAL(clicked()), this,SLOT(goRightMoveAdv()));
    disconnect(select, SIGNAL(clicked()), this,SLOT(spyCard_withenemy_phase2()));

    select->setEnabled(false);
    goLeft->setEnabled(false);
    goRight->setEnabled(false);

       cross->setVisible(false);

       if(*cardSelectionAdversary==1)
       {
           CPU1Card1->setCardPic();

       }


       else if (*cardSelectionAdversary==2)
       {
           CPU1Card2->setCardPic();
       }


       else if (*cardSelectionAdversary==3 )
       {
           CPU1Card3->setCardPic();
       }

       else if (*cardSelectionAdversary==4  )
       {
           CPU1Card4->setCardPic();
       }
       else if (*cardSelectionAdversary==5)
       {
           CPU2Card1->setCardPic();
       }


       else if (*cardSelectionAdversary==6 )
       {
           CPU2Card2->setCardPic();
       }

       else if (*cardSelectionAdversary==7 )
       {
           CPU2Card3->setCardPic();
       }
       else if (*cardSelectionAdversary==8)
       {
          CPU2Card4->setCardPic();
       }

       QTimer::singleShot(2000,this, SLOT(spyCard_withenemy_phase3()));

}

/**
 * @brief game2scene::spyCard_withenemy_phase3()
 *
 * Let the player spy on the card of an opponent (Phase3)
 */


void game2scene::spyCard_withenemy_phase3()
{


       if(*cardSelectionAdversary==1)
       {
           CPU1Card1->setCardPic();

       }


       else if (*cardSelectionAdversary==2)
       {
           CPU1Card2->setCardPic();
       }


       else if (*cardSelectionAdversary==3 )
       {
           CPU1Card3->setCardPic();
       }

       else if (*cardSelectionAdversary==4  )
       {
           CPU1Card4->setCardPic();
       }
       else if (*cardSelectionAdversary==5)
       {
           CPU2Card1->setCardPic();
       }


       else if (*cardSelectionAdversary==6 )
       {
           CPU2Card2->setCardPic();
       }

       else if (*cardSelectionAdversary==7 )
       {
           CPU2Card3->setCardPic();
       }
       else if (*cardSelectionAdversary==8)
       {
          CPU2Card4->setCardPic();
       }

//       QTimer::singleShot(2000,this, SLOT(spyCard_withenemy_phase1()));
       //Add callback to main game loop
       //Add callback to card check
       QTimer::singleShot(2000,this, SLOT(checkDrawPile_amount()));

}

/**
 * @brief game2scene::checkFinalCabo()
 *
 * Final cabo check with scores being displayed
 */

void game2scene::checkFinalCabo()
{



    //Display all cards face up

    *playerCard1->cardShown=false;
    *playerCard2->cardShown=false;
    *playerCard3->cardShown=false;
    *playerCard4->cardShown=false;

    *CPU1Card1->cardShown=false;
    *CPU1Card2->cardShown=false;
    *CPU1Card3->cardShown=false;
    *CPU1Card4->cardShown=false;

    *CPU2Card1->cardShown=false;
    *CPU2Card2->cardShown=false;
    *CPU2Card3->cardShown=false;
    *CPU2Card4->cardShown=false;

    playerCard1->setCardPic();
    playerCard2->setCardPic();
    playerCard3->setCardPic();
    playerCard4->setCardPic();

    CPU1Card1->setCardPic();
    CPU1Card2->setCardPic();
    CPU1Card3->setCardPic();
    CPU1Card4->setCardPic();

    CPU2Card1->setCardPic();
    CPU2Card2->setCardPic();
    CPU2Card3->setCardPic();
    CPU2Card4->setCardPic();


    //Get total points per player
    int scorePlayer=0;
    int scoreCPU1=0;
    int scoreCPU2=0;

    scorePlayer+= *playerCard1->cardValue;
    scorePlayer+= *playerCard2->cardValue;
    scorePlayer+= *playerCard3->cardValue;
    scorePlayer+= *playerCard4->cardValue;

    scoreCPU1 += *CPU1Card1->cardValue;
    scoreCPU1 += *CPU1Card2->cardValue;
    scoreCPU1 += *CPU1Card3->cardValue;
    scoreCPU1 += *CPU1Card4->cardValue;

    scoreCPU2 += *CPU2Card1->cardValue;
    scoreCPU2 += *CPU2Card2->cardValue;
    scoreCPU2 += *CPU2Card3->cardValue;
    scoreCPU2 += *CPU2Card4->cardValue;


    //Check who called CABO and apply procedure

    if(scorePlayer<scoreCPU1 && scorePlayer<scoreCPU2)
    {
        scorePlayer=0;
    }

    else if(scoreCPU1<scorePlayer && scoreCPU1<scoreCPU2)
    {
        scoreCPU1=0;
    }
    else if(scoreCPU2<scorePlayer && scoreCPU2<scoreCPU1)
    {
        scoreCPU2=0;
    }

    //Tie events
    //PLayer
    if(scorePlayer<scoreCPU1 && scorePlayer==scoreCPU2 && *caboCaller==0)
    {
        scorePlayer=0;
    }
    else if(scorePlayer<scoreCPU1 && scorePlayer==scoreCPU2 && *caboCaller!=0)
    {
        scorePlayer=0;
        scoreCPU2=0;
    }

    if(scorePlayer<scoreCPU2 && scorePlayer==scoreCPU1 && *caboCaller==0)
    {
        scorePlayer=0;
    }
    else if(scorePlayer<scoreCPU2 && scorePlayer==scoreCPU1 && *caboCaller!=0)
    {
        scorePlayer=0;
        scoreCPU1=0;
    }
    //CPU1
    if(scoreCPU1<scoreCPU2 && scorePlayer==scoreCPU1 && *caboCaller==1)
    {
        scoreCPU1=0;
    }
    else if(scoreCPU1<scoreCPU2 && scorePlayer==scoreCPU1 && *caboCaller!=1)
    {
        scorePlayer=0;
        scoreCPU1=0;
    }

    if(scoreCPU1<scorePlayer && scoreCPU2==scoreCPU1 && *caboCaller==1)
    {
        scoreCPU1=0;
    }
    else if(scoreCPU1<scorePlayer && scoreCPU2==scoreCPU1 && *caboCaller!=1)
    {
        scoreCPU2=0;
        scoreCPU1=0;
    }

    //CPU2
    if(scoreCPU2<scoreCPU1 && scorePlayer==scoreCPU2 && *caboCaller==2)
    {
        scoreCPU2=0;
    }
    else if(scoreCPU2<scoreCPU1 && scorePlayer==scoreCPU2 && *caboCaller!=2)
    {
       scorePlayer=0;
       scoreCPU2=0;
    }

    if(scoreCPU2<scorePlayer && scoreCPU2==scoreCPU1 && *caboCaller==2)
    {
        scoreCPU2=0;
    }
    else if(scoreCPU2<scorePlayer && scoreCPU2==scoreCPU1 && *caboCaller!=2)
    {
        scoreCPU2=0;
        scoreCPU1=0;
    }

    if(scorePlayer!=0 && *caboCaller==0)
    {
        scorePlayer=scorePlayer+5;
    }

    if(scoreCPU1!=0 && *caboCaller==1)
    {
        scoreCPU1=scoreCPU1+5;
    }

    if(scoreCPU2!=0 && *caboCaller==2)
    {
        scoreCPU2=scoreCPU2+5;
    }
    text->setScale(1.3);
    *finalScorePlayer=scorePlayer;
    text->setPlainText("Game over; Player: "+ QString::number(scorePlayer).toUtf8()+"pts, CPU1 : "+QString::number(scoreCPU1).toUtf8()+"pts, CPU2: "+QString::number(scoreCPU2).toUtf8()+"pts");

    keep->setEnabled(false);
    takeDiscard->setEnabled(false);
    takeDraw->setEnabled(false);
    discard->setEnabled(false);
    select->setEnabled(false);
    callCabo->setEnabled(false);
    goLeft->setEnabled(false);
    goRight->setEnabled(false);

    disconnect(exitButton, SIGNAL(clicked()), this,SLOT(exitgame_n_save()));
    connect(exitButton, SIGNAL(clicked()), this,SLOT(endgame_exit()));
}

/**
 * @brief game2scene::endgame_exit()
 *
 * Exit state when cabo has been called
 */


void game2scene::endgame_exit()
{
    //check wincondition

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


        if ( userName!="guest")
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
            myUser.insert(QString("game2_active"),QString("no"));

            QJsonArray win = myUser["game2_win"].toArray();
            win.append(QJsonValue(*finalScorePlayer));
            myUser.insert(QString("game2_win"),QJsonValue(win));


//            QJsonArray card_values;
//            //Get card values array
//            card_values.push_back(*playerCard1->cardValue);
//            card_values.push_back(*playerCard2->cardValue);
//            card_values.push_back(*playerCard3->cardValue);
//            card_values.push_back(*playerCard4->cardValue);

//            card_values.push_back(*CPU1Card1->cardValue);
//            card_values.push_back(*CPU1Card2->cardValue);
//            card_values.push_back(*CPU1Card3->cardValue);
//            card_values.push_back(*CPU1Card4->cardValue);

//            card_values.push_back(*CPU2Card1->cardValue);
//            card_values.push_back(*CPU2Card2->cardValue);
//            card_values.push_back(*CPU2Card3->cardValue);
//            card_values.push_back(*CPU2Card4->cardValue);

//            QJsonArray CPU1_values;
//            //Get prediction values array CPU1
//            for(int a=0;a<12;a++)
//            {
//                CPU1_values.push_back(CPU1->CPUdataArray[a]);
//            }

//            QJsonArray CPU2_values;
//            //Get prediction values array CPU2
//            for(int a=0;a<12;a++)
//            {
//                CPU2_values.push_back(CPU2->CPUdataArray[a]);
//            }

//            QJsonArray discard_values;
//            //Get discard pile array
//            for(int a=0;a<(discardPileCards->size());a++)
//            {
//                discard_values.push_back(discardPileCards->at(a));
//            }

//            QJsonArray draw_values;
//            //Get draw pile array
//            for(int a=0;a<(drawPileCards->size());a++)
//            {
//                draw_values.push_back(drawPileCards->at(a));
//            }





            objTwo.insert(userName,myUser);
            jsonDocTwo.setObject(objTwo);

            file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
            file.write(jsonDocTwo.toJson());
            file.close();
        }

        menuWidget *menu = new menuWidget();
        menu->show();
        QList<QGraphicsView *> views = this->views();
        for (int i=0;i<views.size();i++)
        {
            views.at(i)->close();
            views.at(i)->deleteLater();
        }


}

/**
 * @brief game2scene::selectPile()
 *
 * Let the user select between the discard and draw pile
 */

void game2scene::selectPile()
{
    takeDiscard->setEnabled(true);
    takeDraw->setEnabled(true);
    if(*caboCalled)
    {
        callCabo->setEnabled(false);
    }
    else
    {
        callCabo->setEnabled(true);
    }


    text->setPlainText("Select an action");

    connect(takeDiscard, SIGNAL(clicked()), this,SLOT(discardAction()));
    connect(takeDraw, SIGNAL(clicked()), this,SLOT(drawAction()));
    connect(callCabo, SIGNAL(clicked()), this,SLOT(caboCall()));
}

/**
 * @brief game2scene::caboCall()
 *
 * Function called when the player calls cabo
 */

void game2scene::caboCall()
{
    takeDiscard->setEnabled(false);
    takeDraw->setEnabled(false);
    callCabo->setEnabled(false);
    *caboCaller=0;
    disconnect(takeDiscard, SIGNAL(clicked()), this,SLOT(discardAction()));
    disconnect(takeDraw, SIGNAL(clicked()), this,SLOT(drawAction()));
    disconnect(callCabo, SIGNAL(clicked()), this,SLOT(caboCall()));

    //Let cpu1 and cpu2 have their turn
    //Add cpu AI here for both CPU1 and CPU2
    *mystr= "";
    cpuActions_1();
    cpuActions_2();
    text->setPlainText(mystr->toUtf8());
    *discardPileCard->cardShown=false;
    discardPileCard->setCardPic();
    //check final cabo

    QTimer::singleShot(6000,this, SLOT(checkFinalCabo()));
}

/**
 * @brief game2scene::discardAction()
 *
 * Function called when the player picks a card from the discard pile
 */

void game2scene::discardAction()
{
    takeDiscard->setEnabled(false);
    takeDraw->setEnabled(false);
    callCabo->setEnabled(false);
    disconnect(takeDiscard, SIGNAL(clicked()), this,SLOT(discardAction()));
    disconnect(takeDraw, SIGNAL(clicked()), this,SLOT(drawAction()));
    disconnect(callCabo, SIGNAL(clicked()), this,SLOT(caboCall()));

    select->setEnabled(true);
    goLeft->setEnabled(true);
    goRight->setEnabled(true);

    text->setPlainText("Select card to swap with discard pile");
    cross->setPos(148,688);
    *cardSelection=1;
    cross->setVisible(true);



    connect(goLeft, SIGNAL(clicked()), this,SLOT(goLeftMove()));
    connect(goRight, SIGNAL(clicked()), this,SLOT(goRightMove()));
    connect(select, SIGNAL(clicked()), this,SLOT(selectandswap_discard()));
}

/**
 * @brief game2scene::selectandswap_discard()
 *
 * Function called when the player picks a card from the discard pile
 */

void game2scene::selectandswap_discard()
{

    int temp = discardPileCards->at(discardPileCards->size()-1);
    int temp2=0;


    if(*cardSelection==1)
    {
        temp2=*playerCard1->cardValue;
        *playerCard1->cardValue=temp;
        discardPileCards->pop_back();
        discardPileCards->append(temp2);
        CPU1->CPUdataArray[4]=temp;
        CPU2->CPUdataArray[4]=temp;

    }


    else if (*cardSelection==2)
    {
        temp2=*playerCard2->cardValue;
        *playerCard2->cardValue=temp;
        discardPileCards->pop_back();
        discardPileCards->append(temp2);
        CPU1->CPUdataArray[5]=temp;
        CPU2->CPUdataArray[5]=temp;
    }


    else if (*cardSelection==3 )
    {
        temp2=*playerCard3->cardValue;
        *playerCard3->cardValue=temp;
        discardPileCards->pop_back();
        discardPileCards->append(temp2);
        CPU1->CPUdataArray[6]=temp;
        CPU2->CPUdataArray[6]=temp;
    }

    else if (*cardSelection==4  )
    {
        temp2=*playerCard4->cardValue;
        *playerCard4->cardValue=temp;
        discardPileCards->pop_back();
        discardPileCards->append(temp2);
        CPU1->CPUdataArray[7]=temp;
        CPU2->CPUdataArray[7]=temp;
    }

    *discardPileCard->cardValue=temp2;
    *discardPileCard->cardShown=false;
    discardPileCard->setCardPic();

      cross->setVisible(false);
      select->setEnabled(false);
      goLeft->setEnabled(false);
      goRight->setEnabled(false);

      qDebug() << "p2 "<< *firstSelection<<" "<< *cardSelection<<endl;

      disconnect(goLeft, SIGNAL(clicked()), this,SLOT(goLeftMove()));
      disconnect(goRight, SIGNAL(clicked()), this,SLOT(goRightMove()));
      disconnect(select, SIGNAL(clicked()), this,SLOT(selectandswap_discard()));

      //Add callback to main game loop
      QTimer::singleShot(2000,this, SLOT(gameLoop_main()));
}

/**
 * @brief game2scene::drawAction()
 *
 * Function called when the player picks a card from the draw pile
 */

void game2scene::drawAction()
{
    takeDiscard->setEnabled(false);
    takeDraw->setEnabled(false);
    callCabo->setEnabled(false);
    disconnect(takeDiscard, SIGNAL(clicked()), this,SLOT(discardAction()));
    disconnect(takeDraw, SIGNAL(clicked()), this,SLOT(drawAction()));
    disconnect(callCabo, SIGNAL(clicked()), this,SLOT(caboCall()));

    // Display picked card
    int temp = drawPileCards->at(drawPileCards->size()-1);
    *tempPlayerDisplay->cardValue=temp;
    *tempPlayerDisplay->cardShown=false;
    tempPlayerDisplay->setCardPic();
    tempPlayerDisplay->setPosition(456,424,0);
    tempPlayerDisplay->setVisible(true);




    // If action card, discard then call the respective action
        if(temp==7 || temp==8)
        {
            tempPlayerDisplay->setVisible(false);

            temp = drawPileCards->at(drawPileCards->size()-1);
            drawPileCards->pop_back();
            discardPileCards->append(temp);

             *discardPileCard->cardValue=temp;
            *discardPileCard->cardShown=false;
            discardPileCard->setCardPic();

            text->setPlainText("PEEK card received!");

            QTimer::singleShot(4000,this, SLOT(checkOneCards_startPlayer()));
        }
        else if(temp==9 || temp==10)
        {
            tempPlayerDisplay->setVisible(false);
            temp = drawPileCards->at(drawPileCards->size()-1);
            drawPileCards->pop_back();
            discardPileCards->append(temp);

             *discardPileCard->cardValue=temp;
            *discardPileCard->cardShown=false;
            discardPileCard->setCardPic();

            text->setPlainText("SPY card received!");

            QTimer::singleShot(4000,this, SLOT(spyCard_withenemy_phase1()));
        }

        else if(temp==11 || temp==12)
        {

            tempPlayerDisplay->setVisible(false);
            temp = drawPileCards->at(drawPileCards->size()-1);
            drawPileCards->pop_back();
            discardPileCards->append(temp);

             *discardPileCard->cardValue=temp;
            *discardPileCard->cardShown=false;
            discardPileCard->setCardPic();

            text->setPlainText("SWAP card received!");

            QTimer::singleShot(4000,this, SLOT(swapCard_withenemy_phase1()));
        }
    // If none, enable the user to either replace one of his cards or discard it to the discard pile
        else
        {
            connect(keep, SIGNAL(clicked()), this,SLOT(keepcard_action()));
            connect(discard, SIGNAL(clicked()), this,SLOT(discardcard_action()));
            keep->setEnabled(true);
            discard->setEnabled(true);
        }
}

/**
 * @brief game2scene::discardcard_action()
 *
 * Function called when the player picks a card from the draw pile and discards it
 */

void game2scene::discardcard_action()
{
    disconnect(keep, SIGNAL(clicked()), this,SLOT(keepcard_action()));
    disconnect(discard, SIGNAL(clicked()), this,SLOT(discardcard_action()));

    keep->setEnabled(false);
    discard->setEnabled(false);

    tempPlayerDisplay->setVisible(false);

    int temp = drawPileCards->at(drawPileCards->size()-1);
    drawPileCards->pop_back();
    discardPileCards->append(temp);

     *discardPileCard->cardValue=temp;
    *discardPileCard->cardShown=false;
    discardPileCard->setCardPic();

    //Add callback to card check
    QTimer::singleShot(2000,this, SLOT(checkDrawPile_amount()));


}

/**
 * @brief game2scene::keepcard_action()
 *
 * Keep card selected from draw pile
 */

void game2scene::keepcard_action()
{

    disconnect(keep, SIGNAL(clicked()), this,SLOT(keepcard_action()));
    disconnect(discard, SIGNAL(clicked()), this,SLOT(discardcard_action()));

    keep->setEnabled(false);
    discard->setEnabled(false);



    select->setEnabled(true);
    goLeft->setEnabled(true);
    goRight->setEnabled(true);

    text->setPlainText("Select card to swap with draw pile");
    cross->setPos(148,688);
    *cardSelection=1;
    cross->setVisible(true);



    connect(goLeft, SIGNAL(clicked()), this,SLOT(goLeftMove()));
    connect(goRight, SIGNAL(clicked()), this,SLOT(goRightMove()));
    connect(select, SIGNAL(clicked()), this,SLOT(keepcard_action_phase1()));
}

/**
 * @brief game2scene::keepcard_action_phase1()
 *
 * Keep card selected from draw pile
 */

void game2scene::keepcard_action_phase1()
{



    int temp = drawPileCards->at(drawPileCards->size()-1);
    int temp2=0;


    if(*cardSelection==1)
    {
        temp2=*playerCard1->cardValue;
        *playerCard1->cardValue=temp;
        drawPileCards->pop_back();
        drawPileCards->append(temp2);
        CPU1->CPUdataArray[4]=99;
        CPU2->CPUdataArray[4]=99;

    }


    else if (*cardSelection==2)
    {
        temp2=*playerCard2->cardValue;
        *playerCard2->cardValue=temp;
        drawPileCards->pop_back();
        drawPileCards->append(temp2);
        CPU1->CPUdataArray[5]=99;
        CPU2->CPUdataArray[5]=99;
    }


    else if (*cardSelection==3 )
    {
        temp2=*playerCard3->cardValue;
        *playerCard3->cardValue=temp;
        drawPileCards->pop_back();
        drawPileCards->append(temp2);
        CPU1->CPUdataArray[6]=99;
        CPU2->CPUdataArray[6]=99;
    }

    else if (*cardSelection==4  )
    {
        temp2=*playerCard4->cardValue;
        *playerCard4->cardValue=temp;
        drawPileCards->pop_back();
        drawPileCards->append(temp2);
        CPU1->CPUdataArray[7]=99;
        CPU2->CPUdataArray[7]=99;
    }

      tempPlayerDisplay->setVisible(false);
      cross->setVisible(false);
      select->setEnabled(false);
      goLeft->setEnabled(false);
      goRight->setEnabled(false);

      qDebug() << "p2 "<< *firstSelection<<" "<< *cardSelection<<endl;

      disconnect(goLeft, SIGNAL(clicked()), this,SLOT(goLeftMove()));
      disconnect(goRight, SIGNAL(clicked()), this,SLOT(goRightMove()));
      disconnect(select, SIGNAL(clicked()), this,SLOT(keepcard_action_phase1()));

      //Add callback to card check
      QTimer::singleShot(2000,this, SLOT(checkDrawPile_amount()));
}

/**
 * @brief game2scene::checkDrawPile_amount()
 *
 * Check if the draw pile has run out
 */

void game2scene::checkDrawPile_amount()
{

    qDebug()<<"Size of the draw pile: "<<drawPileCards->size()<<". Size of the discard pile: "<<discardPileCards->size()<<endl;
     qDebug()<<"CPU1 data : ";
    for(int k=0;k<12;k++)
    {
    qDebug()<<CPU1->CPUdataArray[k]<<" ";
    }

    qDebug()<<endl;

    qDebug()<<"CPU2 data : ";
   for(int k=0;k<12;k++)
   {
   qDebug()<<CPU2->CPUdataArray[k]<<" ";
   }
   qDebug()<<endl;
    if(drawPileCards->size()==0)
    {
        text->setPlainText("No cards in draw pile. Shuffling...");
        int temp = discardPileCards->at(discardPileCards->size()-1);
        for(int i=0;i<discardPileCards->size()-1;i++)
        {
            drawPileCards->append(discardPileCards->at(i));
        }
        discardPileCards->clear();
        discardPileCards->append(temp);

        //Add callback to main loop with delay
        QTimer::singleShot(2000,this, SLOT(gameLoop_main()));
    }
    else
    {
        //Add callback to main loop
        gameLoop_main();
    }


}

/**
 * @brief game2scene::checkDrawPile_amount_CPUs()
 *
 * Check if the draw pile has run out without any turn delay
 */

void game2scene::checkDrawPile_amount_CPUs()
{

    qDebug()<<"Size of the draw pile: "<<drawPileCards->size()<<". Size of the discard pile: "<<discardPileCards->size()<<endl;
     qDebug()<<"CPU1 data : ";
    for(int k=0;k<12;k++)
    {
    qDebug()<<CPU1->CPUdataArray[k]<<" ";
    }

    qDebug()<<endl;

    qDebug()<<"CPU2 data : ";
   for(int k=0;k<12;k++)
   {
   qDebug()<<CPU2->CPUdataArray[k]<<" ";
   }
   qDebug()<<endl;

    if(drawPileCards->size()==0)
    {
        int temp = discardPileCards->at(discardPileCards->size()-1);
        for(int i=0;i<discardPileCards->size()-1;i++)
        {
            drawPileCards->append(discardPileCards->at(i));
        }
        discardPileCards->clear();
        discardPileCards->append(temp);
    }



}
