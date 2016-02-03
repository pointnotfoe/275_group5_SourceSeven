//Release 1.0 By Simon Cheng

#include "viewactivityallcourses.h"
#include "ui_viewactivityallcourses.h"
#include "QMessageBox"
#include <QHeaderView>
#include "globals.h"

viewActivityAllCourses::viewActivityAllCourses(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::viewActivityAllCourses)
{
    ui->setupUi(this);

    //Load Coursename ComboBox

    QSqlQueryModel * modal = new QSqlQueryModel();
    QSqlQuery qry;// = new QSqlQuery(conn.mydb);
    if(getUserType()=="Instructor"){
        qry.exec("SELECT courseName from Courses where courseID='"+courseid+"'");
    }
    else{
        qry.prepare("select courseName from Courses");
        qry.exec();
    }
    modal->setQuery(qry);
    ui->comboBox->setModel(modal);
    ui->pushButton_export->setEnabled(false);

}

viewActivityAllCourses::~viewActivityAllCourses()
{
    delete ui;
}

void viewActivityAllCourses::on_comboBox_currentIndexChanged()
{

    QSqlQuery qry;

    QString courseid,course;

    course = ui->comboBox->currentText();

    qry.exec("select courseID from Courses where courseName='"+course+"'");
    while(qry.next()){
        courseid = qry.value(0).toString();
    }


    //activity table
    QSqlQueryModel * modal = new QSqlQueryModel();
    QSqlQuery qry2;//= new QSqlQuery(conn2.mydb);
    qry2.prepare("select activityname from activity where courseid='"+courseid+"'");
    qry2.exec();
    modal->setQuery(qry2);
    ui->tableView->setModel(modal);

}

void viewActivityAllCourses::on_tableView_activated(const QModelIndex &index)

{
    QString val = ui->tableView->model()->data(index).toString();

    QSqlQuery qry;
    QString group;
    qry.prepare("select * from activity where activityname='"+val+"'");
    qry.exec();
    while(qry.next()){
        ui->label_activityname->setText(val);
        ui->label_type->setText(qry.value(3).toString());
        ui->label_language->setText(qry.value(4).toString());
        group = qry.value(6).toString();
        if(group=="1"){
            ui->label_group->setText("Group Activity");
        }
        else{
            ui->label_group->setText("Individual Activity");
        }
    }

    //GET COURSE ID
    QString courseid,course,activity,activityid,rubricid;
    course = ui->comboBox->currentText();
    qry.exec("select courseid from courses where coursename='"+course+"'");
    while(qry.next()){
        courseid = qry.value(0).toString();
        qDebug()<<"CourseID:" << courseid;
    }
    //Get activity name
    activity = ui->label_activityname->text();

    qDebug()<<"activityname:" << activity;

    //Get activity ID from activity name and courseid
    qry.exec("select activityID from activity where courseid='"+courseid+"' and activityName='"+activity+"'");
    while(qry.next()){
        activityid= qry.value(0).toString();
        qDebug()<<"aID:" << activityid;
    }
    qDebug() << "I AM HERE!!!";

    //Get rubric ID from activityID and courseID
    qry.exec("select rubricID from Rubric where activityID='"+activityid+"'");
    while(qry.next()){
        rubricid = qry.value(0).toString();
        qDebug()<<"rID:" << rubricid;
    }
    //show items based on rubricID

    QSqlQueryModel * modal = new QSqlQueryModel();
    QSqlQuery qry2;// = new QSqlQuery(conn2.mydb);
    qry2.prepare("select itemDescription,maximumNumPoints from Items where rubricID='"+rubricid+"'");
    qry2.exec();
    modal->setQuery(qry2);
    ui->tableView_2->setModel(modal);
    ui->tableView_2->verticalHeader()->hide();
    ui->tableView_2->horizontalHeader()->hide();

    ui->pushButton_export->setEnabled(true);

}


void viewActivityAllCourses::on_pushButton_export_clicked()
{
    //Get the courseid by getting name of course and activity id

    QSqlQuery qry;
    QSqlQuery qry2;

    QString courseid,course,activity,activityid,studentid,rubricid,grade;

    course = ui->comboBox->currentText();

    qry.exec("select courseID from courses where coursename='"+course+"'");
    while(qry.next()){
        courseid = qry.value(0).toString();
    }

    //Get activity name
    activity = ui->label_activityname->text();

    qDebug()<<"activityname:" << activity;

    //Get activity ID from activity name and courseid
    qry.exec("select activityID from activity where courseid='"+courseid+"' and activityName='"+activity+"'");
    while(qry.next()){
        activityid= qry.value(0).toString();
        qDebug()<<"aID:"<< activityid;
    }
    qDebug()<<"EXPORT:";
    qDebug()<<"course:" << courseid;
    qDebug()<<"activity:" << activity;
    qDebug()<<"AID:" << activityid;




    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Activity Student Grades"), "",
        tr("CSV (*.csv);;All Files (*)"));

    if (fileName != "") {
            QFile file(fileName);

            if (file.open(QIODevice::ReadWrite)) {
                QTextStream stream(&file);


                qry.exec("select studentID from CoursesToStudent where courseid='"+courseid+"'");
                while(qry.next()){
                    studentid= qry.value(0).toString();
                    stream << studentid;
                    qry2.exec("select rubricID,grade from ItemsToStudent where courseid='"+courseid+"' and studentID='"+studentid+"'");
                    while(qry2.next()){
                        stream <<',';
                        grade= qry2.value(1).toString();
                        qDebug()<<"grade:" << grade;
                        stream << grade;
                    }
                    stream << endl;
                }
                file.flush();
                file.close();
            }
            else {
                QMessageBox::critical(this, tr("Error"), tr("Error writing to file"));
                return;
            }
        }
}

void viewActivityAllCourses::on_pushButton_Back_clicked()
{
    this->hide();
    if(getUserType()=="Instructor"){
        ManageActivity m;
        m.setModal(true);
        m.exec();
    }
    else{
        administratorScreen as;
        as.setModal(true);
        as.exec();
    }
}
