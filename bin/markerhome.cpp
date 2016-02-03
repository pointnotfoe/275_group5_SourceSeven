#include "markerhome.h"
#include "ui_markerhome.h"
#include "viewactivity.h"
#include <vector>
#include "login.h"
#include "globals.h"

using namespace std;

markerhome::markerhome(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::markerhome)
{
    ui->setupUi(this);

    ui->myName->setText(getName());

    QSqlQuery qry;
    QSqlQuery getcourse;
    vector<QString> mycourses;
    vector<QString> showcourses;

    if(getUserType() == "TA"){
        qry.prepare("select courseID from CoursesToTATM where TATMUsername = ?");
    }
    else if(getUserType() == "TM"){
        qry.prepare("select courseID from CoursesToTM where TMUsername = ?");
    }
    qry.addBindValue(userid);
    qry.exec();

    while(qry.next())
        mycourses.push_back(qry.value(0).toString());

    for(unsigned i = 0; i < mycourses.size(); i++){
        getcourse.prepare("select courseNumber from Courses where courseID = ?");
        getcourse.addBindValue(mycourses.at(i));
        getcourse.exec();
        getcourse.next();
        showcourses.push_back(getcourse.value(0).toString());
    }

    for(unsigned n = 0; n < showcourses.size(); n++){
        ui->courseList->addItem(showcourses.at(n));
    }

}

markerhome::~markerhome()
{
    delete ui;
}

void markerhome::on_logoutButton_clicked()
{
    this->hide();
    login2 l;
    l.setModal(true);
    l.exec();
}

void markerhome::on_courseList_itemDoubleClicked()
{
    QString val = ui->courseList->currentItem()->text();

    QSqlQuery courses;
    courses.prepare("select * from Courses where courseNumber = ?");
    courses.addBindValue(val);
    courses.exec();
    while(courses.next()){
        courseid = courses.value(0).toString();
    }

    this->hide();
    viewactivity va;
    va.setModal(true);
    va.exec();
}
