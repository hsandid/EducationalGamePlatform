#include <QGraphicsScene>
#include <QGraphicsView>
#include <QApplication>
#include <QTimer>
#include "man.h"
#include "mainscene.h"
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv)
{
    srand(time(0));
    QApplication app(argc, argv);
    MainScene *scene= new MainScene();

    QGraphicsView view(scene);

    view.setFixedSize(1000, 1000);
    view.setBackgroundBrush((QImage("background.jpg")).scaled(1000,1000));
    view.setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    view.setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    scene->setSceneRect(0, 0, 1000, 1000);

    view.show();

    return app.exec();
}
