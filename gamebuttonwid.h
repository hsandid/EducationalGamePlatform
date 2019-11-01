#ifndef GAMEBUTTONWID_H
#define GAMEBUTTONWID_H

#include <QWidget>
#include <QtWidgets>

class gamebuttonWid : public QWidget
{
    Q_OBJECT
public:
     explicit gamebuttonWid (QWidget *parent = 0);
 private:
    QLabel *image1;
    QPushButton* SinglePlayer;
    QPushButton *Multiplayer;
    QGridLayout *layout;


};

#endif // GAMEBUTTONWID_H
