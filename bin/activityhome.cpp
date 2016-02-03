#include "activityhome.h"
#include "ui_activityhome.h"
#include "markerhome.h"
#include "activityrubric.h"
#include "globals.h"

QString actid;

activityhome::activityhome(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::activityhome)
{
    ui->setupUi(this);

    ui->myName->setText(getName());
    ui->courseName->setText(getCourseName());
    ui->activityName->setText(getActivityName());

    QSqlQueryModel *model = new QSqlQueryModel();

    QSqlQuery qry;
    QSqlQuery cts;

    cts.prepare("select studentID from CoursesToStudent where courseID = ?");
    cts.addBindValue(courseid);
    cts.exec();

    qry.prepare("select studentName from Students where studentID = ?");

    qry.exec();
    model->setQuery(qry);
    ui->studentList->setModel(model);
}

activityhome::~activityhome()
{
    delete ui;
}

void activityhome::on_pushButton_clicked()
{
    this->hide();
    markerhome mh;
    mh.setModal(true);
    mh.exec();
}

void activityhome::on_studentList_clicked(const QModelIndex &index)
{
    this->hide();
    activityrubric ar;
    ar.setModal(true);
    ar.exec();
}
