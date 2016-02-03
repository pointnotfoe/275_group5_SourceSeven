#ifndef CREATEACCOUNT_H
#define CREATEACCOUNT_H

#include <QDialog>
//#include "login.h"
#include "manageaccounts.h"
#include "QString"
#include <string.h>

namespace Ui {
class createAccount;
}

class createAccount : public QDialog
{
    Q_OBJECT

public:

    explicit createAccount(QWidget *parent = 0);


    ~createAccount();
private slots:



    void on_pushButton_2_clicked();

//    void on_pushButton_4_clicked();

//    void on_buttonBox_accepted();

    void on_pushButton_5_clicked();



    //void on_radioButton_systemadmin_clicked();

//    void on_pushButton_clicked();





    void on_ManageAccount_clicked();

    void on_logout_clicked();

private:
    Ui::createAccount *ui;
};


#endif // CREATEACCOUNT_H


