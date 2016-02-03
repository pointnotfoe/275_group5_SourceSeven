#ifndef MANAGEACTIVITYSCREEN_H
#define MANAGEACTIVITYSCREEN_H

#include <QDialog>
#include "login.h"
#include "ui_courseinitialscreen.h"
#include "courseinitialscreen.h"
#include "globals.h"
#include "editactivity1.h"
#include "viewactivity.h"

namespace Ui {
class ManageActivity;
}

class ManageActivity : public QDialog
{
    Q_OBJECT

public:
    explicit ManageActivity(QWidget *parent = 0);
    ~ManageActivity();
    void on_pushButton_clicked();//create
    void on_pushButton_4_clicked();//edit

private slots:

    void on_CreateActButton_clicked();

    void on_logout_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_edit_clicked();

    //void on_pushButton_2_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ManageActivity *ui;
};


#endif // MANAGEACTIVITYSCREEN_H




