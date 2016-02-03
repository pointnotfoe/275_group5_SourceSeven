#include "createactivity.h"
#include "manageactivityscreen.h"
#include "ui_manageactivityscreen.h"
#include "viewactivityallcourses.h"



//#include "editactivity.h"

ManageActivity::ManageActivity(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageActivity)
{
    ui->setupUi(this);


}

ManageActivity::~ManageActivity()
{
    delete ui;
}

void ManageActivity::on_CreateActButton_clicked()
{
        this->hide();
        CreateActivity c;
        c.setModal(true);
        c.exec();
}


void ManageActivity::on_logout_clicked()
{
    this->hide();
    login2 l;
    l.setModal(true);
    l.exec();
}



void ManageActivity::on_pushButton_5_clicked()//BACK BUTTON
{
    this->hide();
    CourseScreen s;
    s.setModal(true);
    s.exec();





    //c.ui->myName->setText(getUsername());
    //ui->myName->setText(getUsername());
    //qDebug() << getName();


//    conn1.connOpen();

//    QSqlQueryModel *modal1 = new QSqlQueryModel();

//    QSqlQuery* qry1 = new QSqlQuery(conn1.mydb);
//    //get userid query
//    //qry1->prepare("select rowid from courseInfo where username='"+username+"'");

//    qry1->prepare("select courseNumber from Courses where InstructorUsername = '"+userid+"'");
//    qry1->exec();
//    modal1->setQuery(*qry1);
//   // ui->comboBox_Course->setModel(modal1);
//    //ui->listWidget->setModel(modal1);
//    CourseScreen l;
//    //l.ui->courseList->setModel(modal1);
//    l.ui->activityTable->setModel(modal1);
//    l.exec();
}

void ManageActivity::on_pushButton_edit_clicked()
{
    this->hide();
    editActivity1 e;
    e.setModal(true);
    e.exec();
}


void ManageActivity::on_pushButton_2_clicked()
{

    viewActivityAllCourses v;
    v.setModal(true);
    v.exec();
}
