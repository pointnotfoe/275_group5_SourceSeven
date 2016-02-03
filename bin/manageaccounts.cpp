#include "manageaccounts.h"
#include "ui_manageaccounts.h"
//#include "manageisntallation.h"
#include "createaccount.h"
#include "changepassword.h"
#include "changeinfo.h"
//#include "mainwindow.h"
#include "globals.h"


QString val;//value collector from table

ManageAccounts::ManageAccounts(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageAccounts)
{
    ui->setupUi(this);
    QSqlQueryModel * modal= new QSqlQueryModel();
    QSqlQuery qry;
    //QSqlQuery* qry=new QSqlQuery();
    qry.prepare("select empID, username, name, isblocked from Accounts");

    qry.exec();
    modal->setQuery(qry);
    ui->tableView->setModel(modal);
    //conn.connClose();
    qDebug()<<(modal->rowCount());

}
ManageAccounts::~ManageAccounts()
{
    delete ui;
}

void ManageAccounts::on_pushButton_2_clicked()
{    this->hide();

    createAccount create;
    create.setModal(true);
    create.exec();
}

void ManageAccounts::on_pushButton_3_clicked()
{
    //l.connClose();
    this->hide();
    ManageAccounts m;
    m.setModal(true);
    m.exec();
}

//void ManageAccounts::on_pushButton_4_clicked()
//{    this->hide();

//    ManageIsntallation instal;
//    instal.setModal(true);
//   instal.exec();

//}




void ManageAccounts::on_pushButton_clicked()
{
    this->hide();
    login2 log;
    log.setModal(true);
    log.exec();
}

void ManageAccounts::on_radioButton_systemAdmin_clicked()
{
    QString type = ui->radioButton_systemAdmin->text();
    QSqlQueryModel * modal= new QSqlQueryModel();
    QSqlQuery qry;//=new QSqlQuery(conn.mydb);
    qry.prepare("select empID,name,username from Accounts where userType = '"+type+"'");

    qry.exec();
    modal->setQuery(qry);
    ui->tableView->setModel(modal);
    qDebug()<<(modal->rowCount());
}




void ManageAccounts::on_radioButton_administrator_clicked()
{
    QString type = ui->radioButton_administrator->text();
    QSqlQueryModel * modal= new QSqlQueryModel();
    QSqlQuery qry;//=new QSqlQuery(conn.mydb);
   qry.prepare("select empID,name,username from Accounts where userType = '"+type+"'");

    qry.exec();
    modal->setQuery(qry);
    ui->tableView->setModel(modal);
    qDebug()<<(modal->rowCount());
}




void ManageAccounts::on_radioButton_adminAssistant_clicked()
{
    QString type = ui->radioButton_adminAssistant->text();
    QSqlQueryModel * modal= new QSqlQueryModel();
    QSqlQuery qry;//=new QSqlQuery(conn.mydb);
    qry.prepare("select empID,name,username from Accounts where userType = '"+type+"'");

    qry.exec();
    modal->setQuery(qry);
    ui->tableView->setModel(modal);
    qDebug()<<(modal->rowCount());
}



void ManageAccounts::on_radioButton_instructor_clicked()
{
    QString type = ui->radioButton_instructor->text();
    QSqlQueryModel * modal= new QSqlQueryModel();
    QSqlQuery qry;//=new QSqlQuery(conn.mydb);
    qry.prepare("select empID,name,username from Accounts where userType = '"+type+"'");

    qry.exec();
    modal->setQuery(qry);
    ui->tableView->setModel(modal);
    qDebug()<<(modal->rowCount());


}

void ManageAccounts::on_radioButton_TA_clicked()
{

    QSqlQueryModel * modal= new QSqlQueryModel();
    QSqlQuery qry;;//=new QSqlQuery(conn.mydb);
    qry.prepare("select empID,name,username, userType from Accounts where userType = 'TA' or userType ='TM'");

    qry.exec();
    modal->setQuery(qry);
    ui->tableView->setModel(modal);
    //qDebug()<<(modal->rowCount());
}



void ManageAccounts::on_radioButton_showAll_clicked()
{
    QSqlQueryModel * modal= new QSqlQueryModel();
    QSqlQuery qry;//=new QSqlQuery(conn.mydb);
    qry.prepare("select empID,name,userType,username from Accounts");

    qry.exec();
    modal->setQuery(qry);
    ui->tableView->setModel(modal);
    qDebug()<<(modal->rowCount());
}



void ManageAccounts::on_pushButton_go_clicked() //Search
{
    QString eid;
    eid = ui->lineEdit_eid->text();
    QSqlQueryModel * modal= new QSqlQueryModel();
    QSqlQuery qry;//=new QSqlQuery(conn.mydb);
    qry.prepare("select empID, name,userType,username from Accounts where empID = '"+eid+"'");

    qry.exec();
    modal->setQuery(qry);
    ui->tableView->setModel(modal);
    qDebug()<<(modal->rowCount());
}

void ManageAccounts::on_tableView_activated(const QModelIndex &index)
{
    QString vale=ui->tableView->model()->data(index).toString();
    val=vale;
    ui->label_edit->setText(val);


}

void ManageAccounts::on_pushButton_confirm_clicked()
{
    QSqlQuery qry;


    QSqlQuery que;
    if(ui->radioButton_reset->isChecked())
    {   //QString tempo="5050";

        qry.prepare ("update Accounts set password='"+val+"' where username ='"+val+"'");
        qry.exec();
        while(que.next()){
        }
        //this->hide();
        changepassword log;
        log.setModal(true);
        log.exec();

      }
   //  else
     //    QMessageBox::critical(this,tr("error::"),que.lastError().text());

    else if(ui->radioButton_block->isChecked())
    {
        que.prepare ("update Accounts set isblocked='1' where username ='"+val+"'");
        que.exec();
        while(que.next()){
        }
    }
    else if(ui->radioButton_unblock->isChecked())
    {
        que.prepare ("update Accounts set isblocked='0' where username ='"+val+"'");
        if(que.exec())
        {
        while(que.next()){
        }
        }
        else
            QMessageBox::critical(this,tr("error::"),que.lastError().text());

    }
    else if(ui->radioButton_delete->isChecked())
    {
        que.prepare ("Delete from Accounts where username ='"+val+"'");
        if(que.exec())
        {
        while(que.next()){
        }
        }
        else
            QMessageBox::critical(this,tr("error::"),que.lastError().text());

    }
    else if(ui->radioButton_emp->isChecked())
    {
        //this->hide();
        changeinfo log;
        log.setModal(true);
        log.exec();
        //tuser = ui->label_edit->text();

      }
    else
        QMessageBox::critical(this,tr("Save"),tr("Select an edit type first"));

}
