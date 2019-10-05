#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H

#include <QWidget>
#include <QtWidgets>

class registerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit registerWidget(QWidget *parent = 0);

    QLabel *welcome;
    QLabel *fname;
    QLineEdit *fname_edit;
    QLabel *lname;
    QLineEdit *lname_edit;
    QLabel *username;
    QLineEdit *username_edit;
    QLabel *password;
    QLineEdit *password_edit;
    QLabel *passwordconf;
    QLineEdit *passwordconf_edit;
    QLabel *date_text;
    QDateEdit *date_picker;

    QLabel *gender_text;
    QVBoxLayout *gender_radio;
    QGroupBox *gender_container;
    QRadioButton *male_button;
    QRadioButton *female_button;

    QLabel *pppicture_text;
    QPushButton *add_pppicture;
    QLabel *pppicture;

    QPushButton *cancel;
    QPushButton *confirm;

    QString *filename;
    QFile *tempfile;

    QGridLayout *register_layout;







signals:

public slots:
void selectPicture();


};

#endif // REGISTERWIDGET_H
