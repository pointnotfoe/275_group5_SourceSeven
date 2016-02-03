#include "instructorselectcoursescreen.h"
#include "ui_instructorselectcoursescreen.h"
#include "courseinitialscreen.h"
#include "globals.h"
#include "changepassword.h"
#include "login2.h"

QString userid;

instructorSelectCourseScreen::instructorSelectCourseScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::instructorSelectCourseScreen)
{
    ui->setupUi(this);

    ui->myName->setText(getName());
    qDebug() << "get username in insSelCour: " << getName();

    QSqlQueryModel *modal1 = new QSqlQueryModel();

    QSqlQuery qry1;// = new QSqlQuery(login::mydb);
    //get userid query
    //qry1->prepare("select rowid from courseInfo where username='"+username+"'");

    qDebug() << "qry1 select courseNumber " <<qry1.prepare("select courseNumber from Courses where InstructorUsername = '"+userid+"'");
    qry1.exec();
    modal1->setQuery(qry1);
    ui->courseList->setModel(modal1);

    //conn1.connClose();
    //int totalCourses = modal1->rowCount();




}
//void instructorSelectCourseScreen::on_courseSel_clicked(int totalCourses)
//{

//}
void on_listView_activated()
{



}
instructorSelectCourseScreen::~instructorSelectCourseScreen()
{
    delete ui;
}



void instructorSelectCourseScreen::on_courseList_doubleClicked(const QModelIndex &index)
{
    QString val = ui->courseList->model()->data(index).toString();
    qDebug() << "val: " << val;

    QSqlQuery courses;// = new QSqlQuery(connc.mydb);
    courses.prepare("select * from Courses where courseNumber = '"+val+"'");
    courses.exec();
    while(courses.next()){
        courseid = courses.value(0).toString();
    }

    this->hide();
    CourseScreen cis;
    cis.setModal(true);
    cis.exec();
}

void instructorSelectCourseScreen::on_pushButton_changePassword_clicked()
{
    this->hide();
    changepassword c;
    c.setModal(true);
    c.exec();
}



void instructorSelectCourseScreen::on_logoutButton_clicked()
{
    this->hide();
    login2 l;
    l.setModal(true);
    l.exec();


}
