#include <QApplication>
#include"gamebuttonwid.cpp"
int main(int argc, char **argv)
{
QApplication app (argc, argv);
gamebuttonWid * widget=new gamebuttonWid ();
widget->show();

return app.exec();
}
