#include "editrubric.h"
#include "ui_editrubric.h"

QString rid;
editrubric::editrubric(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editrubric)
{
    ui->setupUi(this);

    ui->lineEdit_Point1->setValidator(new QIntValidator());
    ui->lineEdit_Point2->setValidator(new QIntValidator());
    ui->lineEdit_Point3->setValidator(new QIntValidator());
    QSqlQuery qry,qry1;
    qDebug() << "ActivityName: " << value;
    qry.prepare("SELECT activityID from Activity where activityName = '"+value+"'");
    qry.exec();
    qry.next();
    QString actid = qry.value(0).toString();
    //qry1.prepare("SELECT rubricID from Rubric where activityID ='"+actid+"'");
    qry1.prepare("SELECT rubricID from Rubric where activityID='"+actid+"'");
    qry1.exec();
    qry1.next();
    rid = qry1.value(0).toString();
    qDebug() << "Activity ID" << actid;
    //qry.prepare("Select ")
    qDebug() << "Rubric ID: " << rid;
    qry.prepare("Select itemDescription, maximumNumPoints from Items where rubricID='"+rid+"'");
    qDebug() << qry.value(0).toString();
    qDebug() << qry.value(1).toString();
    qry.exec();
    qry.next();
    ui->lineEdit_crit1->setText(qry.value(0).toString());
    ui->lineEdit_Point1->setText(qry.value(1).toString());
    qry.next();
    qDebug() << qry.value(0).toString();
    ui->lineEdit_crit2->setText(qry.value(0).toString());
     ui->lineEdit_Point2->setText(qry.value(1).toString());

    qry.next();
    ui->lineEdit_crit3->setText(qry.value(0).toString());

    ui->lineEdit_Point3->setText(qry.value(1).toString());
}

editrubric::~editrubric()
{
    delete ui;
}

void editrubric::on_pushButton_6_clicked() //LOGOUT
{
    this->hide();
    login2 l;
    l.setModal(true);
    l.exec();
}

void editrubric::on_pushButton_showTotal_clicked()
{
    int total = ui->lineEdit_Point1->text().toInt() + ui->lineEdit_Point2->text().toInt() + ui->lineEdit_Point3->text().toInt();
    QString showTotal = QString::number(total);
    ui->label_showTotal->setText(showTotal);
}

void editrubric::on_pushButton_finish_clicked()
{
    QString c1,c2,c3;
    QString p1,p2,p3;
    p1 = ui->lineEdit_Point1->text();
    p2 = ui->lineEdit_Point2->text();
    p3 = ui->lineEdit_Point3->text();
    c1 = ui->lineEdit_crit1->text();
    c2 = ui->lineEdit_crit2->text();
    c3 = ui->lineEdit_crit3->text();

    qDebug() << "RUBRIC ID ----------- " << rid;
    //QSqlQuery gii;
    qDebug() << "activity name: " << value;
//    gii.prepare("Select activityID from Activity where activityName ='"+value+"'");
//    gii.exec();
//    gii.next();
//    actID = gii.value(0).toString();
//    gii.prepare("select rubricID from Rubric where activityID = ?");
//    gii.addBindValue(actid);
//    gii.exec();
//    gii.next();

    //QString rid = gii.value(0).toString();
    qDebug() << "Rubric ID: " << rid;
   // QSqlQuery qry1,qry2,qry3;
    QSqlQuery qry1,qry2,qry3,qry4,qry5,qry6,gsid;
    qDebug() << "HERE I AM 1";
    qry1.prepare("Select itemID from Items where rubricID='"+rid+"'");
    qry1.exec();
    qry1.next();
    int itemid = qry1.value(0).toInt();
    qDebug() << "itemId: " << itemid;
    //qry1.prepare("UPDATE Items Set itemDescription='"+c1+"', maximumNumPoints='2' where rubricID='"+rID+"'");
    qry1.prepare("UPDATE Items Set itemDescription='"+c1+"', maximumNumPoints='"+p1+"' where itemID=?");
    qry1.addBindValue(itemid+0);
    //qry1.bindValue(":c1", c1);
   //qry1.bindValue(":p1", p1);
    qDebug() << "HERE I AM 2";
    //qry1.next();
    //qry2.prepare("UPDATE Items Set itemDescription='"+c2+"', maximumNumPoints='2' where rubricID='"+rID+"'");
    qry2.prepare("UPDATE Items Set itemDescription='"+c2+"', maximumNumPoints='"+p2+"' where itemID=?");
    qry2.addBindValue(itemid+1);
    //qry2.bindValue(":c2", c2);
    //qry2.bindValue(":p2", p2);
    //qry3.prepare("UPDATE Items Set itemDescription='"+c3+"', maximumNumPoints='2' where rubricID='"+rID+"'");
    qry3.prepare("UPDATE Items Set itemDescription='"+c3+"', maximumNumPoints='"+p3+"' where itemID=?");
    qry3.addBindValue(itemid+2);
    //qry3.bindValue(":c3", c3);
    //qry3.bindValue(":p3", p3);
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
//	gsid.prepare("SELECT studentID from CoursesToStudent where courseID = ?");
//    gsid.addBindValue(courseid);
//    gsid.exec();
    QSqlQuery mb;
    gsid.prepare("select * from CoursesToStudent where courseID = ?");
    gsid.addBindValue(courseid);
    gsid.exec();
    qDebug() << "COURSEID:" << courseid;
    while(gsid.next()){
        qDebug() << "test";
        // make rows for table ModifiedBy
//        mb.prepare("UPDATE ModifiedBy SET rubricID=?, studentID=?, courseID=?");
//        mb.addBindValue(rid);
//        mb.addBindValue(gsid.value(1).toInt());
//        mb.addBindValue(gsid.value(0).toInt());
        //mb.addBindValue(actid);
        //mb.exec();
        qry4.prepare("UPDATE ItemsToStudent SET itemID=?, studentID=?, courseID=?, rubricID=?, grade='0'");
        qry4.addBindValue(itemid+0);
        qry4.addBindValue(gsid.value(1).toInt());
        qry4.addBindValue(gsid.value(0).toInt());
        qry4.addBindValue(rid);
        qry4.exec();
        qry5.prepare("UPDATE ItemsToStudent SET itemID=?, studentID=?, courseID=?, rubricID=?, grade='0'");
        qry5.addBindValue(itemid+1);
        qry5.addBindValue(gsid.value(1).toInt());
        qry5.addBindValue(gsid.value(0).toInt());
        qry5.addBindValue(rid);
        qry5.exec();
        qry6.prepare("UPDATE ItemsToStudent SET itemID=?, studentID=?, courseID=?, rubricID=?, grade='0'");
        qry6.addBindValue(itemid+2);
        qry6.addBindValue(gsid.value(1).toInt());
        qry6.addBindValue(gsid.value(0).toInt());
        qry6.addBindValue(rid);
        qry6.exec();
    }
//    while(gsid.next()){
//        qDebug() << "test";
//        qry4.prepare("UPDATE ItemsToStudent SET (itemID, studentID, courseID) VALUES (:iid, :sid, :cid)");
//	qry4.bindValue(":iid", itemid);
//        qry4.bindValue(":sid", gsid.value(0).toInt());
//        qry4.bindValue(":cid", courseid);
//        qry5.prepare("INSERT into ItemsToStudent(itemID, studentID, courseID) VALUES (:iid, :sid, :cid)");
//	qry5.bindValue(":iid", itemid+1);
//        qry5.bindValue(":sid", gsid.value(0).toInt());
//        qry5.bindValue(":cid", courseid);
//        qry6.prepare("INSERT into ItemsToStudent(itemID, studentID, courseID) VALUES (:iid, :sid, :cid)");
//	qry6.bindValue(":iid", itemid+2);
//        qry6.bindValue(":sid", gsid.value(0).toInt());
//        qry6.bindValue(":cid", courseid);
//    }
//    if(qry1.exec() && qry2.exec() && qry3.exec() && qry4.exec() && qry5.exec() && qry6.exec()){
        QMessageBox::information(this,"Save","Saved");
        QSqlQuery qry;
        qry.prepare("UPDATE Rubric SET numberOfTests='1', directoryPath=:dirPath, description='description', activityID=(SELECT MAX(activityID) FROM Activity) where rubricID='"+rid+"'");
        qry.bindValue(":dirPath", ui->label_submissionPath->text());
        qry.exec();

        this->hide();
        ManageActivity m;
        m.setModal(true);
        m.exec();
//    }
//    else{
//        QMessageBox::critical(this,tr("error::"),qry1.lastError().text());
//    }

}

void editrubric::on_pushButton_path_clicked()
{

    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                   "/home",QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    qDebug() << "directoryPath: " << dir;
    ui->label_submissionPath->setText(dir);

}
