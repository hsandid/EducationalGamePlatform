#include <QApplication>
#include "gamescene_1.h"

// Get rid of these


int main(int argc, char **argv)
{
    QApplication app(argc,argv);

    // Login Page is the first window executed on launch

     QGraphicsView * myView = new QGraphicsView();
    gameScene_1 * scene1 = new gameScene_1();
	myView->setScene(scene1);
    myView->setFixedSize(960,700);
    myView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    myView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    myView->show();


    return app.exec();
}
