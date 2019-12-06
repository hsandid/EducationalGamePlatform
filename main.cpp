#include <QApplication>
#include "loginwidget.h"


#include "menuwidget.h"
#include "registerwidget.h"

/**
 * \mainpage Final Game submission
 * \author Mehieddine Zeidan
 * \author Hadi Sandid
 * \date 9-10-2019
 */

int main(int argc, char **argv)
{
    QApplication app(argc,argv);

    // Login Page is the first window executed on launch

    loginWidget *login = new loginWidget();
    login->show();

    return app.exec();
}
