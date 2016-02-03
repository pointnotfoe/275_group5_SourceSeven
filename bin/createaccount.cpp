#include "createaccount.h"
#include "ui_createaccount.h"
//#include "manageisntallation.h"
#include  <QDialog>
#include <QMessageBox>


createAccount::createAccount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createAccount)
{
    ui->setupUi(this);

}
createAccount::~createAccount()
{
    delete ui;
}


void createAccount::on_pushButton_2_clicked()
{
    this->destroy();
    createAccount create;
    create.setModal(true);
    create.exec();

}


//void createAccount::on_pushButton_4_clicked() //DON"T
//{
//    ManageIsntallation instal;
//    this->hide();
//    instal.setModal(true);
//    instal.exec();

//}
void createAccount::on_pushButton_5_clicked()
{

    QString eid, name, username, type, password;
    username = ui->lineEdit_user->text();
    name = ui->lineEdit_name->text();
    eid = ui->lineEdit_eid->text();
    password = ui->lineEdit_password->text();


    if(ui->radioButton_TA->isChecked())
        type = ui->radioButton_TA->text();

    else if(ui->radioButton_TM->isChecked())
        type = ui->radioButton_TM->text();

    else if(ui->radioButton_systemadmin->isChecked())
        type = ui->radioButton_systemadmin->text();

    else if(ui->radioButton_adminAssistant->isChecked())
        type = ui->radioButton_adminAssistant->text();

    else if(ui->radioButton_Instructor->isChecked())
        type = ui->radioButton_Instructor->text();

    else if(ui->radioButton_administrator->isChecked())
        type = ui->radioButton_administrator->text();

    else{
        QMessageBox::critical(this,"Type Error","Select Type");
        return;
    }
    bool alpha,numeric = false;
    for(int i = 0; i < password.length(); i++){
        if(password[i] >= '0' && password[i] <= '9')
        {
            numeric=true;
            qDebug() << numeric;
            break;

        }
    }
    for(int i=0;i<password.length();i++){
        if(password[i]>='a' && password[i]<='z')
        {
            alpha=true;
            qDebug() << alpha;
            break;
        }
    }


    QSqlQuery qry1;
    if(password.length()<6 || (alpha==false || numeric==false)){
        QMessageBox::information(this,tr("Password"),tr("Password should be 6 or more alpha-numeric characters"));
    }
    else{

        qry1.prepare("insert into Accounts(empID, name, userType, username, password) "
                     "values (:eid, :name, :type, :username, :password)");
        qry1.bindValue(":eid", eid);
        qry1.bindValue(":name", name);
        qry1.bindValue(":type", type);
        qry1.bindValue(":username", username);
        qry1.bindValue(":password", password);
        if(qry1.exec())
        {
             QMessageBox::critical(this,tr("Save"),tr("Saved"));
        }
        else
        {
            QMessageBox::critical(this,tr("error"),tr("Username exists"));//qry1.lastError().text());

        }
    }



}






void createAccount::on_ManageAccount_clicked()
{
    this->hide();
    ManageAccounts m;
    m.setModal(true);
    m.exec();
}

void createAccount::on_logout_clicked()
{
    this->hide();
    login2 l;
    l.setModal(true);
    l.exec();
}
