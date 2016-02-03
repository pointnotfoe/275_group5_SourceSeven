#include "login2.h"
#include "ui_login2.h"




login2::login2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login2)
{
    ui->setupUi(this);
}

login2::~login2()
{
    delete ui;
}

void login2::on_pushButton_clicked()
{
    QString temp;
    bool isblocked;
    QString username, password, type;
    username = ui->userLine->text();
    password = ui->passLine->text();
    QSqlQuery qry;
    int attempt=0;

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
            ui->status->setText("username and password is correct");
            //qry.prepare ("select userType from Accounts where username ='"+username+"'");
            qry.prepare ("select * from Accounts where username = '"+username+"'");
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
            else if(type=="System Admin")
            {
                this->hide();
                createAccount c;
                c.setModal(true);
                c.exec();

            }

            else if(type=="Administrator")
            {
                this->hide();
                administratorScreen a;
                a.setModal(true);
                a.exec();

            }
            else if(type=="TA" || type=="TM")
            {
                this->hide();
                markerhome m;
                m.setModal(true);
                m.exec();
            }

            else{
            this->hide();
            AdminAssistMain adminassistant;
            adminassistant.setModal(true);
            adminassistant.exec();
            }
        }
        if(count>1){
            ui->status->setText("username and password duplicate");
            if(attempt==0)//check if first try
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
        if(count<1){
            ui->status->setText("username and password is incorrect");
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
        ui->status->setText("Wrong");
    }
    }
    else
        ui->status->setText("Blocked");
}
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
