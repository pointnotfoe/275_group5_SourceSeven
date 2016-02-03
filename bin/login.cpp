using namespace std;

#include "login.h"
#include "ui_login.h"
#include "globals.h"
#include <conio.h>
#include <windows.h>
#include <string>

int attempt=0;
QString temp;

login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);

    QFont f("Calibri", 12, QFont::Bold);

    ui->titleName->setText("Streamlined Grading System");
    ui->titleName->setAlignment(Qt::AlignCenter);
    ui->titleName->setFont(f);
    ui->label->setText("Connected...");

}

login::~login()
{
    delete ui;
}

//void login::on_loginButton_clicked()
//{
//    QString username, password, type;
//    username = ui->userLine->text();
//    password = ui->passLine->text();
//    QSqlQuery qry;
//    qry.prepare("select * from Accounts where username = '"+username+"' and password = '"+password+"'");

//    if(qry.exec()){
//        int count = 0;
//        while(qry.next()){
//            count++;
//        }
//        if(count == 1){
//            qry.prepare ("select * from Accounts where username = '"+username+"'");
//            qry.exec();
//            while(qry.next()){
//                userid = qry.value(1).toString();
//                //type = qry.value(3).toString();
//                type = qry.value(4).toString();

//            }
//            qDebug() << "type:" << type;
//            qDebug() << "username:" << userid;
//            if(type == "Instructor"){ //instructor


//                //connClose();
//                this->hide();
//                instructorSelectCourseScreen instructor;
//                instructor.setModal(true);
//                instructor.exec();

//            }
//            else if(type=="System Admin")
//            {
//                //connClose();
//                this->hide();
//                createAccount c;
//                c.setModal(true);
//                c.exec();

//            }
//            else{
//                //connClose();
//                this->hide();
//                AdminAssistMain adminassistant;
//                adminassistant.setModal(true);
//                adminassistant.exec();
//            }
//        }
//        if(count > 1){
//            ui->status->setText("Username and password duplicate.");
//            ui->status->setStyleSheet("QLabel{ color: red; }");
//        }
//        if(count < 1){
//            ui->status->setText("Username or password is incorrect.");
//            ui->status->setStyleSheet("QLabel{ color: red; }");
//        }
//    }
//    else{
//        ui->status->setText("Abort!!");
//    }
//    connClose();
//}

//void login::on_passLine_returnPressed()
//{
//    QString username, password, type;
//    username = ui->userLine->text();
//    password = ui->passLine->text();
//    QSqlQuery qry;
//    qry.prepare("select * from Accounts where username = '"+username+"' and password = '"+password+"'");

//    if(qry.exec()){
//        int count = 0;
//        while(qry.next()){
//            count++;
//        }
//        if(count == 1){
//            qry.prepare ("select * from Accounts where username = '"+username+"'");
//            qry.exec();
//            while(qry.next()){
//                userid = qry.value(1).toString();
//                type = qry.value(4).toString();
//            }
//            qDebug() << "username:" << userid;
//            qDebug() << "type:" << type;
//            if(type == "Instructor"){ //instructor


//                //connClose();
//                this->hide();
//                instructorSelectCourseScreen instructor;
//                instructor.setModal(true);
//                instructor.exec();

//            }
//            else if(type=="System Admin")
//            {
//                //connClose();
//                this->hide();
//                createAccount c;
//                c.setModal(true);
//                c.exec();

//            }
//            else{
//                //connClose();
//                this->hide();
//                AdminAssistMain adminassistant;
//                adminassistant.setModal(true);
//                adminassistant.exec();
//            }
//        }
//        if(count > 1){
//            ui->status->setText("Username and password duplicate.");
//            ui->status->setStyleSheet("QLabel{ color: red; }");
//        }
//        if(count < 1){
//            ui->status->setText("Username or password is incorrect.");
//            ui->status->setStyleSheet("QLabel{ color: red; }");
//        }
//    }
//    else{
//        ui->status->setText("Abort!!");
//    }
//}

void login::on_loginButton_clicked()
{
    bool isblocked;
    QString username,password,type;
    username = ui->lineEdit_username->text();
    password = ui->lineEdit_password->text();


    QSqlQuery qry;

    qry.prepare ("select isblocked from Accounts where username ='"+username+"'");
    qry.exec();
    while(qry.next()){
        isblocked = qry.value(0).toBool();
    }
    if(isblocked!=1)//check if account is blocked
    {
    qry.prepare("select * from Accounts where username='"+username + "' and password='"+password + "'");


    if(qry.exec()){
        int count=0;
        while(qry.next()){
            count++;
        }
        if(count==1){
            ui->label->setText("username and password is correct");
            //qry.prepare ("select userType from Accounts where username ='"+username+"'");
            qry.prepare ("select * from Accounts where username = ?");
            qry.addBindValue(username);
            qry.exec();
            while(qry.next()){
                userid = qry.value(1).toString();
                type = qry.value(4).toString();
            }
            qDebug() << "type:" << type;
            if(type == "Instructor"){ //instructor
                this->hide();
                instructorSelectCourseScreen instructor;
                instructor.setModal(true);
                instructor.exec();
            }
            else if(type == "System Admin")
            {
                this->hide();
                createAccount c;
                c.setModal(true);
                c.exec();

            }

            else if(type == "Administrator")
            {
                this->hide();
                administratorScreen a;
                a.setModal(true);
                a.exec();

            }

            else if(type == "TA" || type == "TM"){
                this->hide();
                markerhome mh;
                mh.setModal(true);
                mh.exec();
            }

            else{
            this->hide();
            AdminAssistMain adminassistant;
            adminassistant.setModal(true);
            adminassistant.exec();
            }
        }
        if(count>1){
            ui->label->setText("username and password duplicate");
            if(attempt == 0)//check if first try
            {
            temp = username;
            }
            attempt++;
            if((attempt == 5)&&(temp == username))
            {
                qry.prepare ("update Accounts set isblocked='1' where username ='"+username+"'");
                qry.exec();
                while(qry.next()){
                }
            }
        }
        if(count<1){
            ui->label->setText("username and password is incorrect");
            if(attempt==0)
            {
            temp=username;
            }
            attempt++;
            if((attempt==5)&&(temp==username))
            {
                qry.prepare ("update Accounts set isblocked='1' where username ='"+username+"'");
                qry.exec();
                while(qry.next()){
                }
            }
        }
    }
    else{
        ui->label->setText("wrong");
    }
    }
    else
        ui->label->setText("Blocked");
}
