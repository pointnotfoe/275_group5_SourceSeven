#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QtSql>
#include <QDialog>
#include <QDebug>
#include <QFileInfo>
#include "adminassistmain.h"
#include "instructorselectcoursescreen.h"
#include "manageactivityscreen.h"
#include "createactivity.h"
#include "createaccount.h"
#include "administratorscreen.h"

#include "QSqlDatabase"
#include <QStringList>


namespace Ui {
class login;
}

class login : public QMainWindow
{
    Q_OBJECT
public:
    QSqlDatabase mydb;
    bool connOpen(){
        //MS SQL
        mydb = QSqlDatabase::addDatabase("QODBC");
        mydb.setConnectOptions();
        mydb.setDatabaseName("Driver={SQL Server Native Client 11.0};Server=cypress.csil.sfu.ca;Database=c275g05A;Uid=c275g05;Pwd=en2Y2QnbhraE77tG;");

        //LOCAL DATABASE
//        mydb = QSqlDatabase::addDatabase("QSQLITE");
//        mydb.setDatabaseName("C:/Users/eds/Documents/CMPT/275/database/database 3.db3"); //EDWARD PC
//        //mydb.setDatabaseName("C:/Users/Danish Khakwani/Desktop/SMSMerged/database2.db3"); //DANISH PC
        if(mydb.open()){
                qDebug() << "Opened!";
                return true;
            }
            else{
                qDebug() << "Error = " << mydb.lastError().text();

                return false;
            }

    }
//    void connClose(){
//        mydb.close();
//        //mydb.removeDatabase(QSqlDatabase::defaultConnection);
//    }

public:
    explicit login(QWidget *parent = 0);
    ~login();

private slots:
    void on_loginButton_clicked();
//    void on_passLine_returnPressed();

//    void on_lineEdit_password_returnPressed();

private:
    Ui::login *ui;

};

#endif // LOGIN_H
