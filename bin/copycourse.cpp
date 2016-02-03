//Release 1.0 By Simon Cheng

#include "copycourse.h"
#include "ui_copycourse.h"
#include <QMessageBox>


copycourse::copycourse(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::copycourse)
{
    ui->setupUi(this);

    //Load Coursename ComboBox

    QSqlQueryModel * modal = new QSqlQueryModel();
    QSqlQuery qry;// = new QSqlQuery(conn.mydb);
    qry.prepare("select coursename from Courses");
    qry.exec();
    modal->setQuery(qry);
    ui->comboBox_existingCourse->setModel(modal);
}

copycourse::~copycourse()
{
    delete ui;
}

void copycourse::on_pushButton_clicked()
{

    int valid = 0;

    //Get values from the boxes
    QString courseid,coursename,coursenumber,instructor,startDate,endDate,TA1,TA2,TA3,TA4,TA5,TM1,TM2,TM3,TM4,TM5;

    coursename = ui->lineEdit_newCourseName->text();
    coursenumber = ui->lineEdit_newCourseNumber->text();
    instructor = ui->label_InstID->text();
    startDate = ui->lineEdit_newCourseStartDate->text();
    endDate = ui->lineEdit_newCourseEndDate->text();

    //get TA employee ID from labels
    TA1 = ui->label_TA1ID->text();
    TA2 = ui->label_TA2ID->text();
    TA3 = ui->label_TA3ID->text();
    TA4 = ui->label_TA4ID->text();
    TA5 = ui->label_TA5ID->text();
    TM1 = ui->label_TM1ID->text();
    TM2 = ui->label_TM2ID->text();
    TM3 = ui->label_TM3ID->text();
    TM4 = ui->label_TM4ID->text();
    TM5 = ui->label_TM5ID->text();


    QSqlQuery qry;

    //Get instructor username from ID
    qry.prepare ("select username from accounts where empid= '"+instructor+"'");
    qry.exec();
    while(qry.next()){
        instructor= qry.value(0).toString();
    }
    qry.prepare("insert into courses(coursename,coursenumber,startdate,enddate,instructorusername)values ('"+coursename+"','"+coursenumber+"','"+startDate+"','"+endDate+"','"+instructor+"')");

    if(qry.exec( )){
        QMessageBox::information(this,tr("Copy"), tr("Copied"));
        valid = 1;
    }
    else{
        QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }

    //find courseid
    qry.prepare("select courseid from courses where coursenumber='"+coursenumber+"' and coursename='"+coursename+"' and startdate='"+startDate+"' and enddate='"+endDate+"'" );
    if(qry.exec()){
        while(qry.next())
         courseid = qry.value(0).toString();
    }

    //convert TA from empid to username
    if(TA1!=""){
        qry.prepare ("select username from accounts where empid= '"+TA1+"'");
        qry.exec();
        while(qry.next()){
            TA1 = qry.value(0).toString();
        }
    }
    if(TA2!=""){
        qry.prepare ("select username from accounts where empid= '"+TA2+"'");
        qry.exec();
        while(qry.next()){
            TA2 = qry.value(0).toString();
        }
    }
    if(TA3!=""){
        qry.prepare ("select username from accounts where empid= '"+TA3+"'");
        qry.exec();
        while(qry.next()){
            TA3 = qry.value(0).toString();
        }
    }
    if(TA4!=""){
        qry.prepare ("select username from accounts where empid= '"+TA4+"'");
        qry.exec();
        while(qry.next()){
            TA4 = qry.value(0).toString();
        }
    }
    if(TA5!=""){
        qry.prepare ("select username from accounts where empid= '"+TA5+"'");
        qry.exec();
        while(qry.next()){
            TA5 = qry.value(0).toString();
        }
    }

    if(TM1!=""){
        qry.prepare ("select username from accounts where empid= '"+TM1+"'");
        qry.exec();
        while(qry.next()){
            TM1 = qry.value(0).toString();
        }
    }
    if(TM2!=""){
        qry.prepare ("select username from accounts where empid= '"+TM2+"'");
        qry.exec();
        while(qry.next()){
            TM2 = qry.value(0).toString();
        }
    }
    if(TM3!=""){
        qry.prepare ("select username from accounts where empid= '"+TM3+"'");
        qry.exec();
        while(qry.next()){
            TM3 = qry.value(0).toString();
        }
    }
    if(TM4!=""){
        qry.prepare ("select username from accounts where empid= '"+TM4+"'");
        qry.exec();
        while(qry.next()){
            TM4 = qry.value(0).toString();
        }
    }
    if(TM5!=""){
        qry.prepare ("select username from accounts where empid= '"+TM5+"'");
        qry.exec();
        while(qry.next()){
            TM5 = qry.value(0).toString();
        }
    }


    //Insert only non-empty TA and TM
    if(TA1!=""){
        qry.exec("insert into CoursesToTATM(courseid,tatmusername)values ('"+courseid+"','"+TA1+"')");
    }
    if(TA2!=""){
        qry.exec("insert into CoursesToTATM(courseid,tatmusername)values ('"+courseid+"','"+TA2+"')");
    }
    if(TA3!=""){
        qry.exec("insert into CoursesToTATM(courseid,tatmusername)values ('"+courseid+"','"+TA3+"')");
    }
    if(TA4!=""){
        qry.exec("insert into CoursesToTATM(courseid,tatmusername)values ('"+courseid+"','"+TA4+"')");
    }
    if(TA5!=""){
        qry.exec("insert into CoursesToTATM(courseid,tatmusername)values ('"+courseid+"','"+TA5+"')");
    }
    if(TM1!=""){
        qry.exec("insert into CoursesToTM(courseid,tmusername)values ('"+courseid+"','"+TM1+"')");
    }
    if(TM2!=""){
        qry.exec("insert into CoursesToTM(courseid,tmusername)values ('"+courseid+"','"+TM2+"')");
    }
    if(TM3!=""){
        qry.exec("insert into CoursesToTM(courseid,tmusername)values ('"+courseid+"','"+TM3+"')");
    }
    if(TM4!=""){
        qry.exec("insert into CoursesToTM(courseid,tmusername)values ('"+courseid+"','"+TM4+"')");
    }
    if(TM5!=""){
        qry.exec("insert into CoursesToTM(courseid,tmusername)values ('"+courseid+"','"+TM5+"')");
    }

    if(valid==1){
        this->hide();
        AdminAssistMain adminassistant;
        adminassistant.setModal(true);
        adminassistant.exec();
    }

}

void copycourse::on_pushButton_back_clicked()
{
    this->hide();
    AdminAssistMain adminassistant;
    adminassistant.setModal(true);
    adminassistant.exec();
}

void copycourse::on_comboBox_existingCourse_currentIndexChanged()
{
    //Clear TA
    ui->label_TA1->setText("");
    ui->label_TA2->setText("");
    ui->label_TA3->setText("");
    ui->label_TA4->setText("");
    ui->label_TA5->setText("");

    ui->label_TA1ID->setText("");
    ui->label_TA2ID->setText("");
    ui->label_TA3ID->setText("");
    ui->label_TA4ID->setText("");
    ui->label_TA5ID->setText("");
    //Clear TM
    ui->label_TM1->setText("");
    ui->label_TM2->setText("");
    ui->label_TM3->setText("");
    ui->label_TM4->setText("");
    ui->label_TM5->setText("");

    ui->label_TM1ID->setText("");
    ui->label_TM2ID->setText("");
    ui->label_TM3ID->setText("");
    ui->label_TM4ID->setText("");
    ui->label_TM5ID->setText("");


    QString coursename=ui->comboBox_existingCourse->currentText();


    int count = 0;
    int count2 = 0;
    QString inst,courseid;
    QString TA1temp,TA2temp,TA3temp,TA4temp,TA5temp;
    QString instun,TA1un,TA2un,TA3un,TA4un,TA5un; // store username
    QString TM1temp,TM2temp,TM3temp,TM4temp,TM5temp;
    QString TM1un,TM2un,TM3un,TM4un,TM5un; // store username

    QSqlQuery qry;
    qry.prepare("select * from courses where coursename='"+coursename+"'");


    if(qry.exec( )){
        while(qry.next()){

           courseid = qry.value(0).toString();
           ui->label_courseNumber->setText(qry.value(2).toString());
           ui->label_startDate->setText(qry.value(3).toString());
           ui->label_endDate->setText(qry.value(4).toString());
           inst = qry.value(5).toString();
           instun = qry.value(5).toString();


    }
    }
    else{
        QMessageBox::critical(this,tr("Error::"),qry.lastError().text());
    }

    //Set empID for instructor from username
    qry.prepare ("select empid from accounts where username= '"+inst+"'");
    qry.exec();
    while(qry.next()){
        inst = qry.value(0).toString();
    }
    ui->label_InstID->setText(inst);

    //Get the name from empid for instructor and display
    qry.prepare ("select name from accounts where empid= '"+inst+"'");
    qry.exec();
    while(qry.next()){
        inst = qry.value(0).toString();
    }
    ui->label_instructor->setText(inst);

    //Get TA username using courseid
    qry.prepare("select tatmusername from coursestotatm where courseid='"+courseid+"'");

    if(qry.exec( )){
           while( qry.next()){
               qDebug() << "count:" << count ;
               count=count+1;
               if(count==1){
                   TA1temp = qry.value(0).toString();
                   TA1un = qry.value(0).toString();
               }
               else if (count==2){
                   TA2temp = qry.value(0).toString();
                   TA2un = qry.value(0).toString();

               }
               else if (count==3){
                   TA3temp = qry.value(0).toString();
                   TA3un = qry.value(0).toString();

               }
               else if (count==4){
                   TA4temp = qry.value(0).toString();
                   TA3un = qry.value(0).toString();

               }
               else if (count==5){
                   TA5temp = qry.value(0).toString();
                   TA5un = qry.value(0).toString();
               }
           }
    }

    //Get TM username using courseid
    qry.prepare("select TMUsername from CoursesToTM where courseid='"+courseid+"'");

    if(qry.exec( )){
           while( qry.next()){
               qDebug() << "count2:" << count2 ;
               count2=count2+1;
               if(count2==1){
                   TM1temp = qry.value(0).toString();
                   TM1un = qry.value(0).toString();

               }
               else if (count2==2){
                   TM2temp = qry.value(0).toString();
                   TM2un = qry.value(0).toString();

               }
               else if (count2==3){
                   TM3temp = qry.value(0).toString();
                   TM3un = qry.value(0).toString();

               }
               else if (count2==4){
                   TM4temp = qry.value(0).toString();
                   TM4un = qry.value(0).toString();

               }
               else if (count2==5){
                   TM5temp = qry.value(0).toString();
                   TM5un = qry.value(0).toString();

               }
           }
    }



    qDebug() << "TA1:" << TA1temp << " TA2:" << TA2temp << " TA3:" <<TA3temp << " TA4:" <<TA4temp << " TA5:" <<TA5temp;

    //Get the employee id from username for TA and TM and display
    if(TA1temp!=""){
        qry.prepare ("select empid from accounts where username= '"+TA1temp+"'");
        qry.exec();
        while(qry.next()){
            TA1temp = qry.value(0).toString();
        }
        ui->label_TA1ID->setText(TA1temp);
    }
    if(TA2temp!=""){
        qry.prepare ("select empid from accounts where username= '"+TA2temp+"'");
        qry.exec();
        while(qry.next()){
            TA2temp = qry.value(0).toString();
        }
        ui->label_TA2ID->setText(TA2temp);
    }
    if(TA3temp!=""){
        qry.prepare ("select empid from accounts where username= '"+TA3temp+"'");
        qry.exec();
        while(qry.next()){
            TA3temp = qry.value(0).toString();
        }
        ui->label_TA3ID->setText(TA3temp);
    }
    if(TA4temp!=""){
        qry.prepare ("select empid from accounts where username= '"+TA4temp+"'");
        qry.exec();
        while(qry.next()){
            TA4temp = qry.value(0).toString();
        }
        ui->label_TA4ID->setText(TA4temp);
    }
    if(TA5temp!=""){
        qry.prepare ("select empid from accounts where username= '"+TA5temp+"'");
        qry.exec();
        while(qry.next()){
            TA5temp = qry.value(0).toString();
        }
        ui->label_TA5ID->setText(TA5temp);
    }

    if(TM1temp!=""){
        qry.prepare ("select empid from accounts where username= '"+TM1temp+"'");
        qry.exec();
        while(qry.next()){
            TM1temp = qry.value(0).toString();
        }
        ui->label_TM1ID->setText(TM1temp);
    }
    if(TM2temp!=""){
        qry.prepare ("select empid from accounts where username= '"+TM2temp+"'");
        qry.exec();
        while(qry.next()){
            TM2temp = qry.value(0).toString();
        }
        ui->label_TM2ID->setText(TM2temp);
    }
    if(TM3temp!=""){
        qry.prepare ("select empid from accounts where username= '"+TM3temp+"'");
        qry.exec();
        while(qry.next()){
            TM3temp = qry.value(0).toString();
        }
        ui->label_TM3ID->setText(TM3temp);
    }
    if(TM4temp!=""){
        qry.prepare ("select empid from accounts where username= '"+TM4temp+"'");
        qry.exec();
        while(qry.next()){
            TM4temp = qry.value(0).toString();
        }
        ui->label_TM4ID->setText(TM4temp);
    }
    if(TM5temp!=""){
        qry.prepare ("select empid from accounts where username= '"+TM5temp+"'");
        qry.exec();
        while(qry.next()){
            TM5temp = qry.value(0).toString();
        }
        ui->label_TM5ID->setText(TM5temp);
    }

    //Get the name from empid for TA and TM and display
    if(TA1temp!=""){
        qry.prepare ("select name from accounts where empid= '"+TA1temp+"'");
        qry.exec();
        while(qry.next()){
            TA1temp = qry.value(0).toString();
        }
        ui->label_TA1->setText(TA1temp);
    }
    if(TA2temp!=""){
        qry.prepare ("select name from accounts where empid= '"+TA2temp+"'");
        qry.exec();
        while(qry.next()){
            TA2temp = qry.value(0).toString();
        }
        ui->label_TA2->setText(TA2temp);
    }
    if(TA3temp!=""){
        qry.prepare ("select name from accounts where empid= '"+TA3temp+"'");
        qry.exec();
        while(qry.next()){
            TA3temp = qry.value(0).toString();
        }
        ui->label_TA3->setText(TA3temp);
    }
    if(TA4temp!=""){
        qry.prepare ("select name from accounts where empid= '"+TA4temp+"'");
        qry.exec();
        while(qry.next()){
            TA4temp = qry.value(0).toString();
        }
        ui->label_TA4->setText(TA4temp);
    }
    if(TA5temp!=""){
        qry.prepare ("select name from accounts where empid= '"+TA5temp+"'");
        qry.exec();
        while(qry.next()){
            TA5temp = qry.value(0).toString();
        }
        ui->label_TA5->setText(TA5temp);
    }

    if(TM1temp!=""){
        qry.prepare ("select name from accounts where empid= '"+TM1temp+"'");
        qry.exec();
        while(qry.next()){
            TM1temp = qry.value(0).toString();
        }
        ui->label_TM1->setText(TM1temp);
    }
    if(TM2temp!=""){
        qry.prepare ("select name from accounts where empid= '"+TM2temp+"'");
        qry.exec();
        while(qry.next()){
            TM2temp = qry.value(0).toString();
        }
        ui->label_TM2->setText(TM2temp);
    }
    if(TM3temp!=""){
        qry.prepare ("select name from accounts where empid= '"+TM3temp+"'");
        qry.exec();
        while(qry.next()){
            TM3temp = qry.value(0).toString();
        }
        ui->label_TM3->setText(TM3temp);
    }
    if(TM4temp!=""){
        qry.prepare ("select name from accounts where empid= '"+TM4temp+"'");
        qry.exec();
        while(qry.next()){
            TM4temp = qry.value(0).toString();
        }
        ui->label_TM4->setText(TM4temp);
    }
    if(TM5temp!=""){
        qry.prepare ("select name from accounts where empid= '"+TM5temp+"'");
        qry.exec();
        while(qry.next()){
            TM5temp = qry.value(0).toString();
        }
        ui->label_TM5->setText(TM5temp);
    }

}



