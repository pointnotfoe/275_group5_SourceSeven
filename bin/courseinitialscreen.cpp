#include "courseinitialscreen.h"
#include "ui_courseinitialscreen.h"
#include "globals.h"
#include "viewactivity.h"
#include "login2.h"\

QString courseid ;



CourseScreen::CourseScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CourseScreen)
{
    ui->setupUi(this);
    QFont f( "Arial", 10, QFont::Bold);

    ui->courseName->setText(getCourseName());
    ui->courseName->setAlignment(Qt::AlignCenter);
    ui->courseName->setFont(f);


    ui->myName->setText(getName());


    QSqlQueryModel *modal1 = new QSqlQueryModel();
    QSqlQuery qry1;
    qry1.prepare("Select studentID, studentName from CoursesToStudent where courseID = '"+courseid+"' ");
    qry1.exec();
    modal1->setQuery(qry1);
    ui->listofStudent_table->setModel(modal1);



}

CourseScreen::~CourseScreen()
{
    delete ui;
}

void CourseScreen::on_activityButton_clicked()
{
    this->hide();
    ManageActivity m;
    m.setModal(true);
    m.exec();
}

void CourseScreen::on_markButton_clicked()
{
    //this-hide();
    viewactivity v;
    v.setModal(true);
    v.exec();
}

void CourseScreen::on_logoutButton_clicked()
{
    this->hide();
    login2 l;
    l.setModal(true);
    l.exec();
}
