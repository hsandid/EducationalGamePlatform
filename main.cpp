#include <QApplication>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include "gamescene_1.cpp"

int main(int argc, char **argv)
{
    QApplication app(argc,argv);
    gameScene_1 * scene1 = new gameScene_1();
    QGraphicsView * myView = new QGraphicsView();
    myView->setScene(scene1);
    myView->setFixedSize(700,700);
    myView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    myView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    myView->show();




    return app.exec();
}
