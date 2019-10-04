#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H

#include <QWidget>
#include <QtWidgets>

class registerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit registerWidget(QWidget *parent = 0);

    QGridLayout *grid_01;
    QVBoxLayout *vbox_radio;

    QLabel *welcome_text;
    QLabel *fname_text;
    QLabel *lname_text;
    QLabel *username_text;
    QLabel *gender_text;
    QLabel *date_of_birth_text;
    QLabel *password_text;
    QLabel *password_confirm_text;
    QLabel *profile_picture_text;
    QLabel *error_message_text;

    QLineEdit *fname_edit;
    QLineEdit *lname_edit;
    QLineEdit *username_edit;
    QLineEdit *password_edit;
    QLineEdit *password_confirm_edit;

    QDateEdit *date_of_birth_date_edit;

    QRadioButton *male_radio_button;
    QRadioButton *female_radio_button;

    QPushButton *select_picture_button;
    QPushButton *cancel_button;
    QPushButton *confirm_button;



signals:

public slots:



};

#endif // REGISTERWIDGET_H
