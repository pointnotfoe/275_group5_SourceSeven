#include "activityinitial.h"
#include "ui_activityinitial.h"
#include "markerhome.h"
#include "comparison.h"
#include "activityrubric.h"
#include "globals.h"

int actid;

activityinitial::activityinitial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::activityinitial)
{
    ui->setupUi(this);

    ui->myName->setText(getName());
    ui->courseName->setText(getCourseName());
    ui->activityName->setText(getActivityName());

    QSqlQueryModel *model = new QSqlQueryModel();

    QSqlQuery cts;

    qDebug() << actid;
    cts.prepare("select CoursesToStudent.studentName, ModifiedBy.userType "
                "from CoursesToStudent "
                "left join ModifiedBy "
                "on CoursesToStudent.studentID = ModifiedBy.studentID "
                "where ModifiedBy.activityID = ?");
    cts.addBindValue(actid);
    cts.exec();

    model->setQuery(cts);
    model->setHeaderData(0, Qt::Horizontal, tr("Student Name"));
    model->setHeaderData(1, Qt::Horizontal, tr("Modified By"));

    ui->studentList->setModel(model);
}

activityinitial::~activityinitial()
{
    delete ui;
}

void activityinitial::on_studentList_doubleClicked(const QModelIndex &index)
{
    QString val = ui->studentList->model()->data(index).toString();
    qDebug() << val;

    // get studentID from table CoursesToStudent
    // info will be used for activityrubric
    QSqlQuery qry;
    qry.prepare("select studentID from CoursesToStudent where studentName = ?");
    qry.addBindValue(val);
    qry.exec();
    qry.next();

    // get rubricID from table Rubric
    QSqlQuery rid;
    rid.prepare("select rubricID from Rubric where activityID = ?");
    rid.addBindValue(actid);
    rid.exec();
    rid.next();
    qDebug() << "rid.value(0).toInt(): " << rid.value(0).toInt();

    // save rubricid for global use
    rubricid = rid.value(0).toString();

    // save studentid for global use
    studentid = qry.value(0).toString();
    qDebug() << studentid;

    // check if regular or programming
    QString c_assign = getTypeAssignment();
    if(c_assign == "Regular"){
        activityrubric ar;
        ar.setModal(true);
        ar.exec();
    }
    else if(c_assign == "Programming"){
        comparison c;
        c.setModal(true);
        c.exec();
    }

}
