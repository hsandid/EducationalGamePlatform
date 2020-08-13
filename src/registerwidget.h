#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H

#include <QWidget>
#include <QtWidgets>

/**
 *
 * \file registerWidget.h
 * \brief The registerWidget class
 */

class registerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit registerWidget(QWidget *parent = 0);
    bool isSelected; //!< bool associated to profile picture selected
    QLabel *welcome; //!< text label
    QLabel *fname; //!< text label
    QLineEdit *fname_edit; //!< personal info input (fname)
    QLabel *lname; //!< text label
    QLineEdit *lname_edit; //!< personal info input (lname)
    QLabel *username; //!< text label
    QLineEdit *username_edit; //!< personal info input (username)
    QLabel *password;//!< text label
    QLineEdit *password_edit; //!< personal info input (password)
    QLabel *passwordconf;//!< text label
    QLineEdit *passwordconf_edit;//!< personal info input (password confirmation)
    QLabel *date_text; //!< text label
    QDateEdit *date_picker; //!< personal info input (date picker)
    QLabel *error_message;//!< text label

    QLabel *gender_text; //!< text label
    QVBoxLayout *gender_radio; //!< Layout element
    QGroupBox *gender_container; //!< Layout element
    QRadioButton *male_button; //!< Radio button
    QRadioButton *female_button; //!< Radio button

    QLabel *pppicture_text; //!< text label
    QPushButton *add_pppicture; //!< Button to open prompt to add picture
    QLabel *pppicture; //!< Picture display

    QPushButton *cancel; //!< Cancel button
    QPushButton *confirm; //!< Confirm button

    QString *filename; //!< Selected profile picture path
    QFile *tempfile; //!< Loaded profile picture

    QGridLayout *register_layout; //!< Main layout


signals:

public slots:
void selectPicture();
void cancelRegistration();
void confirmRegistration();
void checkConditions();
bool passCheck();


};

#endif // REGISTERWIDGET_H
