#include "viewactivity.h"
#include "ui_viewactivity.h"
#include "activityinitial.h"
#include "globals.h"
#include "QMessageBox"
#include <QHeaderView>

viewactivity::viewactivity(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::viewactivity)
{
    ui->setupUi(this);

    QFont f("Calibri", 12, QFont::Bold);
    ui->courseName->setText(getCourseName());
    ui->courseName->setFont(f);

    QSqlQueryModel *modal1 = new QSqlQueryModel();

    QSqlQuery qry1;// = new QSqlQuery(conn1.mydb);

    qry1.prepare("select activityName from Activity where courseID = ?");
    qry1.addBindValue(courseid);
    qry1.exec();
    modal1->setQuery(qry1);
    ui->activityList->setModel(modal1);

}

viewactivity::~viewactivity()
{
    delete ui;
}

void viewactivity::on_activityList_doubleClicked(const QModelIndex &index)
{
    QString val = ui->activityList->model()->data(index).toString();

    QSqlQuery activity;
    activity.prepare("select activityID from Activity where activityName = ? and courseID = ?");
    activity.addBindValue(val);
    activity.addBindValue(courseid);
    activity.exec();
    while(activity.next()){
        actid = activity.value(0).toInt();
    }
    this->hide();
    activityinitial ah;
    ah.setModal(true);
    ah.exec();
}
