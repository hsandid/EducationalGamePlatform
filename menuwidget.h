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

signals:

public slots:



};

#endif // MENUWIDGET_H
