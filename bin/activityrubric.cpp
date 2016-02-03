#include "activityrubric.h"
#include "ui_activityrubric.h"
#include "activityinitial.h"
#include "login.h"
#include <vector>
#include "globals.h"
#include <QDesktopServices>
#include <QUrl>

using namespace std;

QString studentid;
QString rubricid;

// ---------------------BONUS---------------------
// checks if user has sufficient privileges to mark
bool isValid(const QString &s){
    QString type = s;

    QSqlQuery qry;
    qry.prepare("select userType from Accounts where username = ?");
    qry.addBindValue(userid);
    qry.exec();
    qry.next();

    QString check = qry.value(0).toString();

    if(check == "TA" || check == "TM"){
        if(type == "TA" || type == "TM"){
            return true;
        }
        else{
            return false;
        }
    }
    else if(check == "Instructor"){
        if(type == "Administrator"){
            return false;
        }
        else{
            return true;
        }
    }
    else{
        return true;
    }
}

activityrubric::activityrubric(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::activityrubric)
{
    ui->setupUi(this);

    ui->studentName->setText(getStudentName());

    ui->activityName->setText(getActivityName());

    // Generating rubric table
    qDebug() << "rubricid: " << rubricid;

    QSqlRelationalTableModel *model = new QSqlRelationalTableModel();
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    model->setTable("Items");
    model->setRelation(0, QSqlRelation("ItemsToStudent", "itemID", "grade"));

    qDebug() << "studentid: " << studentid;
    qDebug() << "courseid: " << courseid;
    model->setFilter(QString("rubricID = %1 and studentID = %2").arg(rubricid).arg(studentid));
    model->select();

    model->setHeaderData(0, Qt::Horizontal, tr("Grade"));
    model->setHeaderData(1, Qt::Horizontal, tr("Criteria"));
    model->setHeaderData(2, Qt::Horizontal, tr("Max Points"));

    model->database().transaction();

    ui->rubricTable->setModel(model);
    ui->rubricTable->hideColumn(3);

}

activityrubric::~activityrubric()
{
    delete ui;
}

//void activityrubric::on_submTable_doubleClicked()
//{
//    // Generating links for submission table
//    QSqlQuery sol;
//    QSqlQuery subdir;
//    QSqlQuery subfile;

//    sol.prepare("select solutionPath from ActivityToSolution where activityID = ?");
//    sol.addBindValue(actid);
//    sol.exec();
//    sol.next();

//    subdir.prepare("select directoryPath from Rubric where activityID = ?");
//    subdir.addBindValue(actid);
//    subdir.exec();
//    subdir.next();

//    subfile.prepare("select nameOfFile from Activity where activityID = ?");
//    subfile.addBindValue(actid);
//    subfile.exec();
//    subfile.next();

//    QString solfile = sol.value(0).toString();
//    QString subm = subdir.value(0).toString();

//    subm += "/";
//    subm += subfile.value(0).toString();

//    QDesktopServices::openUrl(QUrl::fromLocalFile(subm));
//    QDesktopServices::openUrl(QUrl::fromLocalFile(solfile));

//}

void activityrubric::on_saveButton_pressed()
{
    // check if changes can be made
    QSqlQuery check;
    check.prepare("select userType from ModifiedBy where rubricID = ?");
    check.addBindValue(rubricid);
    check.exec();
    check.next();


    qDebug() << "Is Valid" << isValid(check.value(0).toString());
//    if(!isValid(check.value(0).toString())){
//        QMessageBox::critical(this,tr("Insufficient privileges."),check.lastError().text());
//    }
//    else{
        QAbstractItemModel *view = ui->rubricTable->model();

        vector<int> grades;
        vector<int> itemid;
        for(int i = 0; i < view->rowCount(); i++){
            grades.push_back(view->data(view->index(i, 0)).toInt());
        }
        QSqlQuery gii;
        gii.prepare("select rubricID from Rubric where activityID = ?");
        gii.addBindValue(actid);
        gii.exec();
        gii.next();

        QString rid = gii.value(0).toString();
        qDebug() << rid;

        QSqlQuery gia;
        gia.prepare("select itemID from Items where rubricID = ?");
        gia.addBindValue(rid);
        gia.exec();
        while(gia.next()){
            itemid.push_back(gia.value(0).toInt());
        }

        QSqlQuery upd;
        for(unsigned n = 0; n < itemid.size(); n++){
            upd.prepare("update ItemsToStudent set grade = ? where itemID = ? and studentID = ?");
            upd.addBindValue(grades.at(n));
            upd.addBindValue(itemid.at(n));
            upd.addBindValue(studentid);
            qDebug() << "itemID: " << itemid.at(n);
            upd.exec();
        }
        qDebug() << itemid.size();

        // insert new data into table ModifiedBy
        QSqlQuery lmb;
        lmb.prepare("update ModifiedBy set userType = ? where rubricID = ? and studentID = ? and courseID = ?");
        lmb.addBindValue(getUserType());
        lmb.addBindValue(rid);
        lmb.addBindValue(studentid);
        lmb.addBindValue(courseid);
        lmb.exec();
   // }
}

void activityrubric::on_closeButton_clicked()
{
    this->hide();
}

void activityrubric::on_subFiles_clicked()
{
    // Generating links for submission table
    QSqlQuery sol;
    QSqlQuery subdir;
    QSqlQuery subfile;

    sol.prepare("select solutionPath from ActivityToSolution where activityID = ?");
    sol.addBindValue(actid);
    sol.exec();
    sol.next();

    subdir.prepare("select directoryPath from Rubric where activityID = ?");
    subdir.addBindValue(actid);
    subdir.exec();
    subdir.next();

    subfile.prepare("select nameOfFile from Activity where activityID = ?");
    subfile.addBindValue(actid);
    subfile.exec();
    subfile.next();

    QString solfile = sol.value(0).toString();
    QString subm = subdir.value(0).toString();

    subm += "/";
    subm += subfile.value(0).toString();

    QDesktopServices::openUrl(QUrl::fromLocalFile(subm));
    QDesktopServices::openUrl(QUrl::fromLocalFile(solfile));
}
