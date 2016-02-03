#include "rubric.h"
#include "ui_rubric.h"
#include "globals.h"

QString actname;
int itemid;

rubric::rubric(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rubric)
{
    ui->setupUi(this);

    ui->lineEdit_Point1->setValidator(new QIntValidator());
    ui->lineEdit_Point2->setValidator(new QIntValidator());
    ui->lineEdit_Point3->setValidator(new QIntValidator());

}

rubric::~rubric()
{
    delete ui;
}

void rubric::on_pushButton_6_clicked() //LOGOUT
{
    this->hide();
    login2 l;
    l.setModal(true);
    l.exec();
}
void rubric::on_pushButton_path_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                   "/home",QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    qDebug() << "directoryPath: " << dir;
    ui->label_submissionPath->setText(dir);

}
void rubric::on_pushButton_showTotal_clicked()
{
    int total = ui->lineEdit_Point1->text().toInt() + ui->lineEdit_Point2->text().toInt() + ui->lineEdit_Point3->text().toInt();
    QString showTotal = QString::number(total);
    ui->label_showTotal->setText(showTotal);
}


void rubric::on_pushButton_finish_clicked()
{

    //get actid
    QSqlQuery aid;
    qDebug() << actname;
    qDebug() << courseid;
    aid.prepare("select activityID from Activity where activityName = ? and courseID = ?");
    aid.addBindValue(actname);
    aid.addBindValue(courseid);
    aid.exec();
    aid.next();
    qDebug() << aid.value(0).toInt();
    actid = aid.value(0).toInt();
    qDebug() << "actid: " << actid;


    QString c1,c2,c3;
    int p1,p2,p3;
    p1 = ui->lineEdit_Point1->text().toInt();
    p2 = ui->lineEdit_Point2->text().toInt();
    p3 = ui->lineEdit_Point3->text().toInt();
    c1 = ui->lineEdit_crit1->text();
    c2 = ui->lineEdit_crit2->text();
    c3 = ui->lineEdit_crit3->text();
    //---------------------------------------------------
    //Directory Path, numberofTests if programming else 0
    //----------------------------------------------------

    QSqlQuery qry;
    qry.prepare("INSERT into Rubric(numberOfTests, directoryPath, description, activityID) VALUES ('0', :dirPath,'Description',(SELECT MAX(activityID) FROM Activity))");
    qry.bindValue(":dirPath", ui->label_submissionPath->text());
    qry.exec();
    qry.next();

    QSqlQuery gii;
    qDebug() << "activity name: " << actname;
    gii.prepare("Select activityID from Activity where activityName = ?");
    gii.addBindValue(actname);
    gii.exec();
    gii.next();
    int temp = gii.value(0).toInt();
    qDebug() << "temp: " << temp;
    gii.prepare("select rubricID from Rubric where activityID = ?");
    gii.addBindValue(temp);
    gii.exec();
    gii.next();
    int rid = gii.value(0).toInt();
    qDebug() << "Rubric ID: " << rid;

    // Initializing queries for creating items for table Items & ItemsToStudent
    QSqlQuery qry1,qry2,qry3,qry4,qry5,qry6,gsid;

    qry1.prepare("INSERT into Items(itemDescription, maximumNumPoints, rubricID) VALUES (:c1,:p1,(SELECT MAX(rubricID) FROM Rubric))");
    qry1.bindValue(":c1", c1);
    qry1.bindValue(":p1", p1);
    qry2.prepare("INSERT into Items(itemDescription, maximumNumPoints, rubricID) VALUES (:c2,:p2,(SELECT MAX(rubricID) FROM Rubric))");
    qry2.bindValue(":c2", c2);
    qry2.bindValue(":p2", p2);
    qry3.prepare("INSERT into Items(itemDescription, maximumNumPoints, rubricID) VALUES (:c3,:p3,(SELECT MAX(rubricID) FROM Rubric))");
    qry3.bindValue(":c3", c3);
    qry3.bindValue(":p3", p3);
    if(qry1.exec() && qry2.exec() && qry3.exec()){

        // Get itemID
        QSqlQuery iid;
        iid.prepare("select itemID from Items where rubricID = ?");
        iid.addBindValue(rid);
        iid.exec();
        iid.next();
        itemid = iid.value(0).toInt();
        qDebug() << "itemid: " << itemid;

    }

    // make rows for table ItemsToStudent
    QSqlQuery mb;
    gsid.prepare("select * from CoursesToStudent where courseID = ?");
    gsid.addBindValue(courseid);
    gsid.exec();
    qDebug() << "rid: " << rid;
    qDebug() << "actid: " << actid;
    while(gsid.next()){
        qDebug() << "test";
        // make rows for table ModifiedBy
        mb.prepare("insert into ModifiedBy(rubricID, studentID, courseID, activityID) values (?, ?, ?, ?)");
        mb.addBindValue(rid);
        mb.addBindValue(gsid.value(1).toInt());
        mb.addBindValue(gsid.value(0).toInt());
        mb.addBindValue(actid);
        mb.exec();

        qry4.prepare("INSERT into ItemsToStudent(itemID, studentID, courseID, rubricID, grade) VALUES (?, ?, ?, ?, '0')");
        qry4.addBindValue(itemid+0);
        qry4.addBindValue(gsid.value(1).toInt());
        qry4.addBindValue(gsid.value(0).toInt());
        qry4.addBindValue(rid);
        qry4.exec();
        qry5.prepare("INSERT into ItemsToStudent(itemID, studentID, courseID, rubricID, grade) VALUES (?, ?, ?, ?, '0')");
        qry5.addBindValue(itemid+1);
        qry5.addBindValue(gsid.value(1).toInt());
        qry5.addBindValue(gsid.value(0).toInt());
        qry5.addBindValue(rid);
        qry5.exec();
        qry6.prepare("INSERT into ItemsToStudent(itemID, studentID, courseID, rubricID, grade) VALUES (?, ?, ?, ?, '0')");
        qry6.addBindValue(itemid+2);
        qry6.addBindValue(gsid.value(1).toInt());
        qry6.addBindValue(gsid.value(0).toInt());
        qry6.addBindValue(rid);
        qry6.exec();
    }
    QMessageBox::information(this,"Save","Saved");

    this->hide();
    ManageActivity m;
    m.setModal(true);
    m.exec();
}
