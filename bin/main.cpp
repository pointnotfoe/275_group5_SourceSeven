#include "login.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QStringList>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setConnectOptions();
    db.setDatabaseName("Driver={SQL Server Native Client 11.0};Server=cypress.csil.sfu.ca;Database=c275g05A;Uid=c275g05;Pwd=en2Y2QnbhraE77tG;");
    if(db.open()){
        qDebug() << "Opened!";
    }
    else{
        qDebug() << "Error = " << db.lastError().text();
        db.close();
    }
    login w;
    w.show();

    return a.exec();

}
