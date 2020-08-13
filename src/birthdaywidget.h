#ifndef BIRTHDAYWIDGET_H
#define BIRTHDAYWIDGET_H

#include <QWidget>
#include <QtWidgets>

/**
 *
 * \file birthdaywidget.h
 * \brief The birthdaywidget class
 */


class birthdaywidget : public QWidget
{
    Q_OBJECT
public:
    explicit birthdaywidget(QWidget *parent = 0);
    QVBoxLayout *layout; //!< VBox Layout
    QLabel *bdtext; //!< Main text
    QPushButton *conf; //!< Main Button

signals:

public slots:
    void confirmExit();

};

#endif // BIRTHDAYWIDGET_H
