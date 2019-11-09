#include <QApplication>
#include "loginwidget.h"

// Get rid of these
#include "menuwidget.h"
#include "registerwidget.h"

int main(int argc, char **argv)
{
    QApplication app(argc,argv);

    // Login Page is the first window executed on launch

    loginWidget *login = new loginWidget();
    login->show();

    return app.exec();
}
