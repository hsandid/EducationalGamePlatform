#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QtWidgets>

class loginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit loginWidget(QWidget *parent = 0);

    QLabel *test_screen;
    QPushButton *LogINbutton;
    QPushButton *RegisterButton;
    QGridLayout  *test_layout;
    QLabel * UserName;
    QLabel * PassWord;
    QLineEdit * UserNameLine;
    QLineEdit * PassWordLine;
signals:

public slots:
    void GoToRegisterPage();
    void GoToMainPage();

};

#endif // LOGINWIDGET_H
