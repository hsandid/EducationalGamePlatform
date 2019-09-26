#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QTimer>
#include "man.h"

class MainScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MainScene(QGraphicsScene *parent= 0) ;
    QTimer* timer;
    basket* theBasket;
signals:

public slots:
    void update();
};

#endif // MAINSCENE_H
