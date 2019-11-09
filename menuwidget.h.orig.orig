#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include <QtWidgets>

class menuWidget : public QWidget
{
    Q_OBJECT
public:
    explicit menuWidget(QWidget *parent = 0);


    //Guest Bool
    bool *isGuest;
    QGridLayout *test_layout;
    QGridLayout *play_layout;
    QGridLayout *profile_layout;
    QGridLayout *history_layout;
    QWidget * play;
    QWidget * profile;
    QWidget * history;
    QTabWidget *tabWidget;
    QLabel * Welcome;
    QLabel * Game1Name;
    QLabel * Game2Name;
    QPushButton * Play1;
    QPushButton * Play1x;
    QPushButton * Play2;
    QPushButton * Play2x;
    QLabel * image1;
    QLabel * image2;
    QPushButton * Load1;
    QPushButton * Load2;
    QPushButton * Logout;


    //Everything related to the profile section

    QLabel *usernameDisplay;
    QLabel *ppDisplay;
    QLabel *fnameDisplay;
    QLabel *lnameDisplay;
    QLabel *dobDisplay;
    QLabel *genderDisplay;


signals:

public slots:
void readFromJsonProfile();
void logout();
void startGameCPU();
void startGameMultiplayer();
void loadGame();



};

#endif // MENUWIDGET_H
