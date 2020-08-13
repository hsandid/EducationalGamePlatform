#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QtWidgets>

/**
 *
 * \file  loginWidget.h
 * \brief The loginWidget class
 */

class loginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit loginWidget(QWidget *parent = 0);
    QLabel *test_screen; //!< Text label
    QPushButton *LogINbutton; //!< Menu button to login
    QPushButton *RegisterButton; //!< Menu button to register
    QGridLayout  *test_layout; //!< Main Layout
    QLabel * UserName; //!< Text label
    QLabel * PassWord; //!< Text label
    QLineEdit * UserNameLine; //!< Line edit field
    QLineEdit * PassWordLine; //!< Line edit field
    QLabel * ErrorMessage; //!< Text label
    QPushButton * PlayAsGuestButton; //!< Menu button to play as guest

signals:

public slots:
    void GoToRegisterPage();
    void checkLogin();
    void GoToMainAsGuest();

};

#endif // LOGINWIDGET_H
