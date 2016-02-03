#include "administratorscreen.h"
#include "ui_administratorscreen.h"
#include "coursehomescreen.h"
#include "changepassword.h"
#include "globals.h"



administratorScreen::administratorScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::administratorScreen)

{
    ui->setupUi(this);
    ui->myname->setText(getName());

    QSqlQueryModel *modal1 = new QSqlQueryModel();
    QSqlQuery qry1;
    qry1.prepare("Select courseNumber, InstructorUsername from Courses ");
    qry1.exec();
    modal1->setQuery(qry1);
    ui->listofcourses->setModel(modal1);


}

administratorScreen::~administratorScreen()
{
    delete ui;
}



void administratorScreen::on_logoutButton_clicked()
{
    this->hide();
    login2 l;
    l.setModal(true);
    l.exec();
}

void administratorScreen::on_changepasswordButton_clicked()
{
    this->hide();
    changepassword c;
    c.exec();
}

void administratorScreen::on_listofcourses_doubleClicked(const QModelIndex &index)
{
    QString val = ui->listofcourses->model()->data(index).toString();

    QSqlQuery course;// = new QSqlQuery(connc.mydb);
    course.prepare("select * from Courses where courseNumber = '"+val+"'");
    course.exec();
    while(course.next()){
        courseid = course.value(0).toString();
    }

    this->hide();
    Coursehomescreen c;
    c.setModal(true);
    c.exec();
}


