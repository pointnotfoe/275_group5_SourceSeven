#include "changeinfo.h"
#include "ui_changeinfo.h"
#include "createaccount.h"
#include <QDialog>
#include <QMessageBox>
#include "globals.h"


changeinfo::changeinfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changeinfo)
{
    ui->setupUi(this);
}

changeinfo::~changeinfo()
{
    delete ui;
}

void changeinfo::on_pushButton_confirm_clicked()
{
    QString username,eid,name,type;
    username=ui->lineEdit_username->text();
    eid=ui->lineEdit_eid->text();
    name=ui->lineEdit_name->text();
    //qDebug() << "tuser: " << tuser;
    //ui->label_user->setText(tuser);


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




    QSqlQuery qry1;
    qry1.prepare("SELECT count(username) from Accounts where username='"+username+"'");
    qry1.exec();
    qry1.next();
    int count = qry1.value(0).toInt();
    qry1.prepare("update Accounts set empID='"+eid+"',name='"+name+"',userType='"+type+"' where username='"+username + "' ");

    if(count==1)
    {
         qry1.exec();
         QMessageBox::critical(this,tr("Save"),tr("updated"));

         this->hide();

    }
    else
    {
        QMessageBox::critical(this,tr("error"),tr("Enter correct username"));

    }
}
