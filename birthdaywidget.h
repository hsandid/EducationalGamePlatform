#ifndef BIRTHDAYWIDGET_H
#define BIRTHDAYWIDGET_H

#include <QWidget>
#include <QtWidgets>

class birthdaywidget : public QWidget
{
    Q_OBJECT
public:
    explicit birthdaywidget(QWidget *parent = 0);
    QVBoxLayout *layout;
    QLabel *bdtext;
    QPushButton *conf;
signals:

public slots:
    void confirmExit();

};

#endif // BIRTHDAYWIDGET_H
