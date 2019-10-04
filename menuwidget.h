#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include <QtWidgets>

class menuWidget : public QWidget
{
    Q_OBJECT
public:
    explicit menuWidget(QWidget *parent = 0);

    QLabel *test_screen;
    QPushButton *button;
    QGridLayout *test_layout;

signals:

public slots:
    void GoToLoginPage();


};

#endif // MENUWIDGET_H
