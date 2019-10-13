#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include <QtWidgets>

class menuWidget : public QWidget
{
    Q_OBJECT
public:
    explicit menuWidget(QWidget *parent = 0);


    QGridLayout *test_layout;
    QGridLayout *play_layout;
    QGridLayout *profile_layout;
    QWidget * play;
    QWidget * profile;
    QTabWidget *tabWidget;
    QLabel * Welcome;
    QLabel * Game1Name;
    QLabel * Game2Name;
    QPushButton * Play1;
    QPushButton * Play2;
    QPixmap * image1;
    QPixmap * image2;
    QPushButton * Load1;
    QPushButton * Load2;


signals:

public slots:



};

#endif // MENUWIDGET_H
