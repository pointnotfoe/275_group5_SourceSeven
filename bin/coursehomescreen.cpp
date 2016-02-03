#include "coursehomescreen.h"
#include "ui_coursehomescreen.h"
#include "globals.h"
#include "viewactivity.h"
#include"viewactivityallcourses.h"


Coursehomescreen::Coursehomescreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Coursehomescreen)
{
    ui->setupUi(this);
    ui->coursename->setText(getCourseName());

    QSqlQueryModel *modal1 = new QSqlQueryModel();
    QSqlQuery qry1;
    qry1.prepare("Select studentID, studentName from CoursesToStudent where courseID = '"+courseid+"' ");
    qry1.exec();
    modal1->setQuery(qry1);
    ui->listofStudents->setModel(modal1);



    QSqlQueryModel *modal5 = new QSqlQueryModel();
    QSqlQuery qry5;
    qry5.prepare("Select TATMUsername from CoursesToTATM where courseID = '"+courseid+"'");
    qry5.exec();
    modal5->setQuery(qry5);
    ui->listofTA->setModel(modal5);


     QSqlQueryModel *g7 = new QSqlQueryModel();
     QSqlQuery qry7;
     qry7.prepare("Select TMUsername from CoursesToTM where courseID = '"+courseid+"'");
     qry7.exec();
     g7->setQuery(qry7);
     ui->listofTM->setModel(g7);







}

Coursehomescreen::~Coursehomescreen()
{
    delete ui;
}

void Coursehomescreen::on_markbutton_clicked()
{
    //this-hide();
    viewactivity v;
    v.setModal(true);
    v.exec();


}

void Coursehomescreen::on_activitiesbutton_clicked()
{
   this->hide();
    viewActivityAllCourses v;
    v.setModal(true);
    v.exec();


}

void Coursehomescreen::on_logoutbutton_clicked()
{

    this->hide();
    login2 l;
    l.show();

}

void Coursehomescreen::on_backbutton_clicked()
{
    this->hide();
    administratorScreen a;
    a.exec();
}
