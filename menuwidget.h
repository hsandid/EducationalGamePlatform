#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include <QtWidgets>

/**
 * \brief The menuWidget class
 * \file menuwidget.h
 */

class menuWidget : public QWidget
{
    Q_OBJECT
public:
    explicit menuWidget(QWidget *parent = 0);


    //Guest Bool
    bool *isGuest; //!< Bool which denotes whether the logged in user is a guest
    QGridLayout *test_layout; //!< Main Layout
    QGridLayout *play_layout; //!< Tab Layout
    QGridLayout *profile_layout; //!< Tab Layout
    QVBoxLayout *history_layout; //!< Tab Layout
    QWidget * play; //!< Tab Widget
    QWidget * profile; //!< Tab Widget
    QWidget * history; //!< Tab Widget
    QTabWidget *tabWidget; //!< Main Tab Widget
    QLabel * Welcome; //!< Text label
    QLabel * Game1Name; //!< Text label
    QLabel * Game2Name; //!< Text label
    QPushButton * Play1; //!< Button which opens Game1 VS CPU
    QPushButton * Play1x; //!< Button which opens Game1 Multiplayer
    QPushButton * Play2; //!< Button which opens Game2
    QPushButton * Play2x; //!< Button which opens Game2
    QLabel * image1; //!< Image in menu
    QLabel * image2; //!< Image in menu
    QPushButton * Load1; //!< Button which loads Game1 save
    QPushButton * Load2; //!< Button which loads Game2 save
    QPushButton * Logout; //!< Button which returns to logon menu

    QTextEdit *history_info; //!< Text associated to player history


    //Everything related to the profile section

    QLabel *usernameDisplay; //!< Personnal Info display (username)
    QLabel *ppDisplay; //!< Personnal Info display (profile picture)
    QLabel *fnameDisplay; //!< Personnal Info display (fname)
    QLabel *lnameDisplay;//!< Personnal Info display (lname)
    QLabel *dobDisplay;//!< Personnal Info display (date of birth)
    QLabel *genderDisplay;//!< Personnal Info display (gender)


signals:

public slots:
void readFromJsonProfile();
void logout();
void startGameCPU();
void startGameCPU_2();
void startGameMultiplayer();
void loadGame();
void loadGame_2();



};

#endif // MENUWIDGET_H
