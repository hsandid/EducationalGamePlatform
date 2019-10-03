#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H

#include <QWidget>
#include <QtWidgets>

class registerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit registerWidget(QWidget *parent = 0);

    QLabel *test_screen;
    QPushButton *button;
    QVBoxLayout *test_layout;

signals:

public slots:
    void GoToLoginPage();


};

#endif // REGISTERWIDGET_H
