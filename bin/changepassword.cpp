#include "changepassword.h"
#include "ui_changepassword.h"
#include "login.h"
#include "login2.h"
#include "createaccount.h"
#include <QDialog>
#include <QMessageBox>

changepassword::changepassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changepassword)
{
    ui->setupUi(this);
}

changepassword::~changepassword()
{
    delete ui;
}

void changepassword::on_pushButton_confirm_clicked()
{


    QString username,newPassword,password;
    username=ui->lineEdit_username->text();
    newPassword=ui->lineEdit_newPassword->text();
    password=ui->lineEdit_oldPassword->text();




    QSqlQuery qry1;
    qry1.prepare("update Accounts set password='"+newPassword+"' where username='"+username + "' and password='"+password + "' ");

    if(qry1.exec( ))
    {
         QMessageBox::critical(this,tr("Save"),tr("updated"));

         this->hide();
         login2 log;
         log.setModal(true);
         log.exec();
    }
    else
    {
        QMessageBox::critical(this,tr("error"),qry1.lastError().text());

    }



}

/*void changepassword::on_pushButton_back_clicked()
{
    this->hide();
    instructorSelectCourseScreen c;
    c.setModal(true);
    c.exec();
}
*/
