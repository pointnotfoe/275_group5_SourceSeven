#include "editactivity1.h"
#include "ui_editactivity1.h"
#include "editactivity.h"

QString value;
QString rubID;

editActivity1::editActivity1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editActivity1)
{
    ui->setupUi(this);
    QSqlQuery qry;
    qry.prepare("SELECT activityName from Activity where courseID = ?");
    qry.addBindValue(courseid);
    qry.exec();
    QSqlQueryModel *modal1 = new QSqlQueryModel();
    modal1->setQuery(qry);
    ui->activityList->setModel(modal1);
}

editActivity1::~editActivity1()
{
    delete ui;
}

void editActivity1::on_activityList_activated(const QModelIndex &index)
{
    QString val1 = ui->activityList->model()->data(index).toString();
    ui->label_3->setText(val1);
    value = ui->label_3->text();

    qDebug() << "val: " << value;
    QSqlQuery qry;
    qry.prepare("select activityID from Activity where activityName='"+value+"'");
    qry.exec();
    qDebug() << ui->activityList->currentIndex().data().toString();
    qDebug() << "val: " << value;
    //QSqlQuery qry;
    qry.prepare("select activityID from Activity where activityName='"+value+"'and courseID='"+courseid+"'");
    qry.exec();
    qry.next();
    QString actID = qry.value(0).toString();
    qry.prepare("select rubricID from Rubric where activityID='"+actID+"'");
    qry.exec();
    qDebug() << "debug: " << qry.next();
    rubID =qry.value(0).toString();
    rubricid=rubID;
    qDebug() << "actID: " <<  actID;
    qDebug() << "rubID: " << rubID;


}

void editActivity1::on_pushButton_delete_clicked()
{
    qDebug() << "val: " << value;
    QSqlQuery qry;
    qry.prepare("select activityID from Activity where activityName='"+value+"'and courseID='"+courseid+"'");
    qry.exec();
    qry.next();
    QString actID = qry.value(0).toString();
    qry.prepare("select rubricID from Rubric where activityID='"+actID+"'");
    qry.exec();
    qry.next();
    QString rubID =qry.value(0).toString();
    rubricid=rubID;
    qDebug() << "actID: " <<  actID;
    qDebug() << "rubID: " << rubID;

    qry.prepare("DELETE from ActivityToSolution where activityID='"+actID+"'");
    qry.exec();
    qry.prepare("DELETE from Items where rubricID='"+rubID+"'");
    qry.exec();
    qry.prepare("DELETE from Rubric where rubricID='"+rubID+"'");
    qry.exec();
    qry.prepare("DELETE from Activity where activityName='"+value+"' and courseID='"+courseid+"'");
    qDebug() << courseid;

    qry.exec();
    qry.prepare("DELETE from ItemsToStudent where rubricID='"+rubID+"' and courseID='"+courseid+"'");
    if(qry.exec())
    {
        QMessageBox::information(this,"Delete","Deleted");
    }
    qry.prepare("SELECT activityName from Activity where courseID = '"+courseid+"'");
    qry.exec();
    QSqlQueryModel *modal1 = new QSqlQueryModel();
    modal1->setQuery(qry);
    ui->activityList->setModel(modal1);


}

void editActivity1::on_pushButton_select_clicked()
{
    this->hide();
    editactivity e;
    e.setModal(true);
    e.exec();
}
