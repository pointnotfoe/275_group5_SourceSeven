#include "viewact.h"
#include "ui_viewact.h"

viewact::viewact(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::viewact)
{
    ui->setupUi(this);

    QSqlQuery qry;


    //activity table
    QSqlQueryModel * modal = new QSqlQueryModel();
    QSqlQuery qry2;//= new QSqlQuery(conn2.mydb);
    qry2.prepare("select activityname from activity where courseid='"+courseid+"'");
    qry2.exec();
    modal->setQuery(qry2);
    ui->tableView->setModel(modal);


    //ui->tableView->verticalHeader()->hide();
    //ui->tableView->horizontalHeader()->hide();
    //ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
}

viewact::~viewact()
{
    delete ui;
}

void viewact::on_tableView_activated(const QModelIndex &index)
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

    /*

    //GET COURSE ID
    QString courseid,course,activity,activityid,rubricid;
    course = ui->comboBox->currentText();
    qry.exec("select courseid from courses where coursename='"+course+"'");
    while(qry.next()){
        courseid = qry.value(0).toString();
        qDebug()<<"CourseID:" << courseid;
    }
    */

    QString activityid,rubricid,activity;

    //Get activity name
    activity = ui->label_activityname->text();

    qDebug()<<"activityname:" << activity;

    //Get activity ID from activity name and courseid
    qry.exec("select activityID from Activity where courseid='"+courseid+"' and activityName='"+activity+"'");
    while(qry.next()){
        activityid= qry.value(0).toString();
        qDebug()<<"aID:" << activityid;
    }

    //Get rubric ID from activityID and courseID
    qry.exec("select rubricID from Activity where courseID='"+courseid+"' and activityID='"+activityid+"'");
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
