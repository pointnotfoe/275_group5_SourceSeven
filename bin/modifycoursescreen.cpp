//Release 1.0 By Simon Cheng

#include "modifycoursescreen.h"
#include "ui_modifycoursescreen.h"
#include "QMessageBox"

modifycoursescreen::modifycoursescreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modifycoursescreen)
{
    ui->setupUi(this);

    //Load Coursename ComboBox
    QSqlQueryModel * modal = new QSqlQueryModel();
    QSqlQuery qry;// = new QSqlQuery(conn.mydb);
    qry.prepare("select coursename from Courses");
    qry.exec();
    modal->setQuery(qry);
    ui->comboBox->setModel(modal);
    QSqlQueryModel * modal1 = new QSqlQueryModel();
    QSqlQuery qry1; // = new QSqlQuery(conn1.mydb);
    qry1.prepare("select name from Accounts where userType='Instructor'");
    qry1.exec();
    modal1->setQuery(qry1);
    ui->comboBox_Instructor->setModel(modal1);


    //Load TA Comboboxes
    QSqlQueryModel * modal2 = new QSqlQueryModel();

    QSqlQuery qry2;// = new QSqlQuery(conn2.mydb);
    qry2.prepare("select name from Accounts where userType='TA'");
    qry2.exec();
    modal2->setQuery(qry2);
    ui->comboBox_TA1->setModel(modal2);
    ui->comboBox_TA2->setModel(modal2);
    ui->comboBox_TA3->setModel(modal2);
    ui->comboBox_TA4->setModel(modal2);
    ui->comboBox_TA5->setModel(modal2);

    //Set empty
    ui->comboBox_TA1->setCurrentIndex(-1);
    ui->comboBox_TA2->setCurrentIndex(-1);
    ui->comboBox_TA3->setCurrentIndex(-1);
    ui->comboBox_TA4->setCurrentIndex(-1);
    ui->comboBox_TA5->setCurrentIndex(-1);

    QSqlQueryModel * modal3 = new QSqlQueryModel();

    QSqlQuery qry3;// = new QSqlQuery(conn2.mydb);

    qry3.prepare("select name from Accounts where userType='TM'");
    qry3.exec();
    modal3->setQuery(qry3);

    //Load TM ComboBoxes
    ui->comboBox_TM1->setModel(modal3);
    ui->comboBox_TM2->setModel(modal3);
    ui->comboBox_TM3->setModel(modal3);
    ui->comboBox_TM4->setModel(modal3);
    ui->comboBox_TM5->setModel(modal3);
    //Set empty
    ui->comboBox_TM1->setCurrentIndex(-1);
    ui->comboBox_TM2->setCurrentIndex(-1);
    ui->comboBox_TM3->setCurrentIndex(-1);
    ui->comboBox_TM4->setCurrentIndex(-1);
    ui->comboBox_TM5->setCurrentIndex(-1);

}

modifycoursescreen::~modifycoursescreen()
{
    delete ui;
}

void modifycoursescreen::on_pushButton_clicked()
{
    this->hide();
    AdminAssistMain adminassistant;
    adminassistant.setModal(true);
    adminassistant.exec();
}

void modifycoursescreen::checkString(QString &temp, QChar character)
{
    if(temp.count("\"")%2 == 0) {
        //if (temp.size() == 0 && character != ',') //problem with line endings
        //    return;
        if (temp.startsWith( QChar('\"')) && temp.endsWith( QChar('\"') ) ) {
             temp.remove( QRegExp("^\"") );
             temp.remove( QRegExp("\"$") );
        }
        //FIXME: will possibly fail if there are 4 or more reapeating double quotes
        temp.replace("\"\"", "\"");
        QStandardItem *item = new QStandardItem(temp);
        standardItemList.append(item);
        if (character != QChar(',')) {
            model->appendRow(standardItemList);
            standardItemList.clear();
        }
        temp.clear();
    } else {
        temp.append(character);
    }
}

void modifycoursescreen::on_pushButton_Modify_clicked()
{
    QString coursename,coursenumber,instructor,startDate,endDate,courseid,TA1,TA2,TA3,TA4,TA5;
    QString TM1,TM2,TM3,TM4,TM5;
    QString name,studentid;

    coursename = ui->comboBox->currentText();
    coursenumber = ui->lineEdit_ModifyCourseNumber->text();
    instructor = ui->label_EID->text();
    startDate = ui->lineEdit_modifyStartDate->text();
    endDate = ui->lineEdit_modifyEndDate->text();

    TA1 = ui->label_TA1->text();
    TA2 = ui->label_TA2->text();
    TA3 = ui->label_TA3->text();
    TA4 = ui->label_TA4->text();
    TA5 = ui->label_TA5->text();

    TM1 = ui->label_TM1->text();
    TM2 = ui->label_TM2->text();
    TM3 = ui->label_TM3->text();
    TM4 = ui->label_TM4->text();
    TM5 = ui->label_TM5->text();

    //Update course info
    QSqlQuery qry;

    //Get username from employee ID query
    qry.prepare ("SELECT username from Accounts where empID='"+TA1+"'");
    qry.exec();
    while(qry.next()){
        TA1 = qry.value(0).toString();
    }
    qry.prepare ("SELECT username from Accounts where empID='"+TA2+"'");
    qry.exec();
    while(qry.next()){
        TA2 = qry.value(0).toString();
    }
    qry.prepare ("SELECT username from Accounts where empID='"+TA3+"'");
    qry.exec();
    while(qry.next()){
        TA3 = qry.value(0).toString();
    }
    qry.prepare ("SELECT username from Accounts where empID='"+TA4+"'");
    qry.exec();
    while(qry.next()){
        TA4 = qry.value(0).toString();
    }
    qry.prepare ("SELECT username from Accounts where empID='"+TA5+"'");
    qry.exec();
    while(qry.next()){
        TA5 = qry.value(0).toString();
    }
    qry.prepare ("SELECT username from Accounts where empID='"+TM1+"'");
    qry.exec();
    while(qry.next()){
        TM1 = qry.value(0).toString();
    }
    qry.prepare ("SELECT username from Accounts where empID='"+TM2+"'");
    qry.exec();
    while(qry.next()){
        TM2 = qry.value(0).toString();
    }
    qry.prepare ("SELECT username from Accounts where empID='"+TM3+"'");
    qry.exec();
    while(qry.next()){
        TM3 = qry.value(0).toString();
    }
    qry.prepare ("SELECT username from Accounts where empID='"+TM4+"'");
    qry.exec();
    while(qry.next()){
        TM4 = qry.value(0).toString();
    }
    qry.prepare ("SELECT username from Accounts where empID='"+TM5+"'");
    qry.exec();
    while(qry.next()){
        TM5 = qry.value(0).toString();
    }

    qry.prepare ("SELECT username from Accounts where empID='"+instructor+"'");
    qry.exec();
    while(qry.next()){
        instructor= qry.value(0).toString();
    }

    qry.prepare("update Courses set coursenumber='"+coursenumber+"',instructorusername='"+instructor+"',startdate='"+startDate+"',enddate='"+ endDate+"' where coursename='"+coursename+"' ");


    if(qry.exec( )){
        QMessageBox::critical(this,tr("Modify"), tr("Modified"));
        //conn.connClose();
        //this->hide();
        //AdminAssistMain adminassistant;
        //adminassistant.setModal(true);
        //adminassistant.exec();
    }
    else{
        QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }
    //Get courseID

    QSqlQuery qry1;
    qry1.prepare("select courseid from Courses where coursenumber='"+coursenumber+"' and coursename='"+coursename+"'");
    if(qry1.exec()){
        while(qry1.next())
         courseid = qry1.value(0).toString();
    }
    else{
        QMessageBox::critical(this,tr("Error::"),qry1.lastError().text());
    }
    //conn1.connClose();
    qDebug()<<"COURSEID:" << courseid;



    //Delete all TA and TM associated with courseID and insert
    qry1.prepare("delete from CoursesToTATM where courseID='"+courseid+"'");
    qry1.exec();

    //Insert only non-empty TA and TM
    if(TA1!=""){
        qry1.exec("insert into CoursesToTATM(courseid,tatmusername)values ('"+courseid+"','"+TA1+"')");
    }
    if(TA2!=""){
        qry1.exec("insert into CoursesToTATM(courseid,tatmusername)values ('"+courseid+"','"+TA2+"')");
    }
    if(TA3!=""){
        qry1.exec("insert into CoursesToTATM(courseid,tatmusername)values ('"+courseid+"','"+TA3+"')");
    }
    if(TA4!=""){
        qry1.exec("insert into CoursesToTATM(courseid,tatmusername)values ('"+courseid+"','"+TA4+"')");
    }
    if(TA5!=""){
        qry1.exec("insert into CoursesToTATM(courseid,tatmusername)values ('"+courseid+"','"+TA5+"')");
    }
    if(TM1!=""){
        qry1.exec("insert into CoursesToTM(courseid,tmusername)values ('"+courseid+"','"+TM1+"')");
    }
    if(TM2!=""){
        qry1.exec("insert into CoursesToTM(courseid,tmusername)values ('"+courseid+"','"+TM2+"')");
    }
    if(TM3!=""){
        qry1.exec("insert into CoursesToTM(courseid,tmusername)values ('"+courseid+"','"+TM3+"')");
    }
    if(TM4!=""){
        qry1.exec("insert into CoursesToTM(courseid,tmusername)values ('"+courseid+"','"+TM4+"')");
    }
    if(TM5!=""){
        qry1.exec("insert into CoursesToTM(courseid,tatmusername)values ('"+courseid+"','"+TM5+"')");
    }
    //conn1.connClose();

    //delete old students
    qry1.prepare("delete from CoursesToStudent where courseid='"+courseid+"'");
    qry1.exec();

    //insert students to CoursesToStudent
    for(int i=0;i<ui->tableView->model()->rowCount();i++){
        name = ui->tableView->model()->data(ui->tableView->model()->index(i,0)).toString();
        studentid = ui->tableView->model()->data(ui->tableView->model()->index(i,1)).toString();
        qry1.exec("insert into CoursesToStudent(courseid,studentid,studentName)values ('"+courseid+"','"+studentid+"','"+name+"')");
    }

    this->hide();
    AdminAssistMain adminassistant;
    adminassistant.setModal(true);
    adminassistant.exec();

}

void modifycoursescreen::on_pushButton_deleteCourse_clicked()
{

    QString coursename,coursenumber,instructor,startDate,endDate,courseid;
    coursename = ui->comboBox->currentText();
    coursenumber = ui->lineEdit_ModifyCourseNumber->text();
    instructor = ui->comboBox_Instructor->currentText();
    startDate = ui->lineEdit_modifyStartDate->text();
    endDate = ui->lineEdit_modifyEndDate->text();


    QSqlQuery qry;

    //find courseid
    qry.prepare("select courseID from Courses where courseNumber='"+coursenumber+"' and courseName='"+coursename+"' and startDate='"+startDate+"' and endDate='"+endDate+"'" );
    if(qry.exec()){
        while(qry.next())
         courseid = qry.value(0).toString();
    }

    //Count number of activities associated with course
    qry.exec("select count(activityID) from Activity where courseID='"+courseid+"'");
    qry.next();
    int activity = qry.value(0).toInt();
    qDebug() << "# of act:" << activity;
    if (activity == 0){

    //Delete TAs
    qry.exec("delete from CoursesToTATM where courseID='"+courseid+"'");

    //Delete TM
    qry.exec("delete from CoursesToTM where courseID='"+courseid+"'");
    //Delete students
    qry.exec("delete from CoursesToStudent where courseID='"+courseid+"'");

    //Delete course
    qry.prepare("Delete from Courses where courseID='"+courseid+"'");


        if(qry.exec( )){
            QMessageBox::critical(this,tr("Delete"), tr("Deleted course"));
            //conn.connClose();
            this->hide();
            AdminAssistMain adminassistant;
            adminassistant.setModal(true);
            adminassistant.exec();
        }
        else{
            QMessageBox::critical(this,tr("Error::"),qry.lastError().text());
        }
    }
    else {
        QMessageBox::critical(this,tr("Error::"),tr("Cannot delete a course which contains an activity"));
    }
}

void modifycoursescreen::on_comboBox_currentIndexChanged()
{
    //Clear TA combo boxes
    ui->comboBox_TA1->setCurrentIndex(-1);
    ui->comboBox_TA2->setCurrentIndex(-1);
    ui->comboBox_TA3->setCurrentIndex(-1);
    ui->comboBox_TA4->setCurrentIndex(-1);
    ui->comboBox_TA5->setCurrentIndex(-1);
    
    //Clear TM combo boxes
    ui->comboBox_TM1->setCurrentIndex(-1);
    ui->comboBox_TM2->setCurrentIndex(-1);
    ui->comboBox_TM3->setCurrentIndex(-1);
    ui->comboBox_TM4->setCurrentIndex(-1);
    ui->comboBox_TM5->setCurrentIndex(-1);


    QString coursename=ui->comboBox->currentText();

    int count = 0;
    int TA1index = 0 ;
    int TA2index = 0 ;
    int TA3index = 0 ;
    int TA4index = 0 ;
    int TA5index = 0 ;
    
    int count2 = 0;
    int TM1index = 0 ;
    int TM2index = 0 ;
    int TM3index = 0 ;
    int TM4index = 0 ;
    int TM5index = 0 ;
    QString inst,courseid;
    QString TA1temp,TA2temp,TA3temp,TA4temp,TA5temp;
    QString TM1temp,TM2temp,TM3temp,TM4temp,TM5temp;

    QSqlQuery qry;
    qry.prepare("select * from Courses where coursename='"+coursename+"'");


    if(qry.exec( )){
        while(qry.next()){
           //ui->lineEdit_CourseName->setText(qry.value(0).toString());
           //ui->lineEdit_modifyInstructor->setText(qry.value(1).toString());


           ui->lineEdit_ModifyCourseNumber->setText(qry.value(2).toString());
           ui->lineEdit_modifyStartDate->setText(qry.value(3).toString());
           ui->lineEdit_modifyEndDate->setText(qry.value(4).toString());
           courseid = qry.value(0).toString();
           inst = qry.value(5).toString();
           qDebug() << "instructor:" << inst;
        }

        //Set the index of the Instructor combobox
        //int tester= ui->comboBox_Instructor->findText(inst);
        //qDebug() << "index:" << tester ;
        //ui->comboBox_Instructor->setCurrentIndex(tester);

        //conn.connClose();
    }
    else{
        QMessageBox::critical(this,tr("Error::"),qry.lastError().text());
    }

    //get username of instructor
    qry.prepare("select name from Accounts where username='"+inst+"'");
    qry.exec();
    while(qry.next()){
        inst = qry.value(0).toString();
    }
    int tester= ui->comboBox_Instructor->findText(inst);
    ui->comboBox_Instructor->setCurrentIndex(tester);

    //Fill TA combo boxes

    QSqlQuery qry11;

    qry11.prepare("select tatmusername from CoursesToTATM where courseid='"+courseid+"'");

    //get the usernames of all ta
    if(qry11.exec( )){
           while( qry11.next()){
               qDebug() << "count:" << count ;
               count=count+1;
               if(count==1){
                   TA1temp = qry11.value(0).toString();
                   //TAindex= ui->comboBox_TA1->findText(TA);
                   //ui->comboBox_TA1->setCurrentIndex(TAindex);
               }
               else if (count==2){
                   TA2temp = qry11.value(0).toString();
                   //TAindex= ui->comboBox_TA2->findText(TA);
                   //ui->comboBox_TA2->setCurrentIndex(TAindex);
               }
               else if (count==3){
                   TA3temp = qry11.value(0).toString();
                   //TAindex= ui->comboBox_TA3->findText(TA);
                   //ui->comboBox_TA3->setCurrentIndex(TAindex);
               }
               else if (count==4){
                   TA4temp = qry11.value(0).toString();
                   //TAindex= ui->comboBox_TA4->findText(TA);
                   //ui->comboBox_TA4->setCurrentIndex(TAindex);
               }
               else if (count==5){
                   TA5temp = qry11.value(0).toString();
                   //TAindex= ui->comboBox_TA5->findText(TA);
                   //ui->comboBox_TA5->setCurrentIndex(TAindex);
               }
           }
    }
    else{
        QMessageBox::critical(this,tr("Error::"),qry11.lastError().text());
    }
    //conn11.connClose();

    qDebug() << "TA1:" << TA1temp << " TA2:" << TA2temp << " TA3:" <<TA3temp << " TA4:" <<TA4temp << " TA5:" <<TA5temp;


    QSqlQuery qry1;


    //convert the username to full name and set combo index
    if(TA1temp!=""){

        qry1.prepare("select name from Accounts where username='"+TA1temp+"'");
        qry1.exec();
        while(qry1.next()){
            TA1temp = qry1.value(0).toString();
        }
        TA1index= ui->comboBox_TA1->findText(TA1temp);
        ui->comboBox_TA1->setCurrentIndex(TA1index);
        //conn1.connClose();
    }

    QSqlQuery qry2;

    if(TA2temp!=""){

        qry2.prepare("select name from Accounts where username='"+TA2temp+"'");
        qry2.exec();
        while(qry2.next()){
            TA2temp = qry2.value(0).toString();
        }
        TA2index= ui->comboBox_TA2->findText(TA2temp);
        ui->comboBox_TA2->setCurrentIndex(TA2index);


    }

    QSqlQuery qry3;

    if(TA3temp!=""){

        qry3.prepare("select name from Accounts where username='"+TA3temp+"'");
        qry3.exec();
        while(qry3.next()){
            TA3temp = qry3.value(0).toString();
        }
        TA3index= ui->comboBox_TA3->findText(TA3temp);
        ui->comboBox_TA3->setCurrentIndex(TA3index);


    }

    QSqlQuery qry4;

    if(TA4temp!=""){

        qry4.prepare("select name from Accounts where username='"+TA4temp+"'");
        qry4.exec();
        while(qry4.next()){
            TA4temp = qry4.value(0).toString();
        }
        TA4index= ui->comboBox_TA4->findText(TA4temp);
        ui->comboBox_TA4->setCurrentIndex(TA4index);


    }

    QSqlQuery qry5;

    if(TA5temp!=""){

        qry5.prepare("select name from Accounts where username='"+TA5temp+"'");
        qry5.exec();
        while(qry5.next()){
            TA5temp = qry5.value(0).toString();
        }
        TA5index= ui->comboBox_TA5->findText(TA5temp);
        ui->comboBox_TA5->setCurrentIndex(TA5index);

    }
    //************************
    //TM
    //************************
    QSqlQuery qry112;

    qry112.prepare("select TMUsername from CoursesToTM where courseid='"+courseid+"'");

    //get the usernames of all tm
    if(qry112.exec( )){
           while( qry112.next()){
               qDebug() << "count2:" << count2 ;
               count2=count2+1;
               if(count2==1){
                   TM1temp = qry112.value(0).toString();
               }
               else if (count2==2){
                   TM2temp = qry112.value(0).toString();
               }
               else if (count2==3){
                   TM3temp = qry112.value(0).toString();

               }
               else if (count2==4){
                   TM4temp = qry112.value(0).toString();
               }
               else if (count2==5){
                   TM5temp = qry112.value(0).toString();
               }
           }
    }
    else{
        QMessageBox::critical(this,tr("Error::"),qry112.lastError().text());
    }
    //conn11.connClose();

    qDebug() << "TM1:" << TM1temp << " TM2:" << TM2temp << " TM3:" <<TM3temp << " TM4:" <<TM4temp << " TM5:" <<TM5temp;


    QSqlQuery qry1a;


    //convert the username to full name and set combo index
    if(TM1temp!=""){
        qry1a.prepare("select name from Accounts where username='"+TM1temp+"'");
        qry1a.exec();
        while(qry1a.next()){
            TM1temp = qry1a.value(0).toString();
        }
        TM1index= ui->comboBox_TM1->findText(TM1temp);
        ui->comboBox_TM1->setCurrentIndex(TM1index);

    }

    QSqlQuery qry2a;

    if(TM2temp!=""){

        qry2a.prepare("select name from Accounts where username='"+TM2temp+"'");
        qry2a.exec();
        while(qry2a.next()){
            TM2temp = qry2a.value(0).toString();
        }
        TM2index= ui->comboBox_TM2->findText(TM2temp);
        ui->comboBox_TM2->setCurrentIndex(TM2index);


    }

    QSqlQuery qry3a;

    if(TM3temp!=""){

        qry3a.prepare("select name from Accounts where username='"+TM3temp+"'");
        qry3a.exec();
        while(qry3a.next()){
            TM3temp = qry3a.value(0).toString();
        }
        TM3index= ui->comboBox_TM3->findText(TM3temp);
        ui->comboBox_TM3->setCurrentIndex(TM3index);


    }

    QSqlQuery qry4a;

    if(TM4temp!=""){

        qry4a.prepare("select name from Accounts where username='"+TM4temp+"'");
        qry4a.exec();
        while(qry4a.next()){
            TM4temp = qry4a.value(0).toString();
        }
        TM4index= ui->comboBox_TM4->findText(TM4temp);
        ui->comboBox_TM4->setCurrentIndex(TM4index);


    }

    QSqlQuery qry5a;

    if(TM5temp!=""){

        qry5a.prepare("select name from Accounts where username='"+TM5temp+"'");
        qry5a.exec();
        while(qry5a.next()){
            TM5temp = qry5a.value(0).toString();
        }
        TM5index= ui->comboBox_TM5->findText(TM5temp);
        ui->comboBox_TM5->setCurrentIndex(TM5index);

    }


    //Load student table
    QSqlQueryModel * modal = new QSqlQueryModel();
    QSqlQuery qry6;// = new QSqlQuery(conn6.mydb);
    qry6.prepare("select studentName,studentID from CoursesToStudent where courseid='"+courseid+"'");
    qry6.exec();
    modal->setQuery(qry6);
    ui->tableView->setModel(modal);
}

void modifycoursescreen::on_comboBox_Instructor_currentIndexChanged()
{
    QString name=ui->comboBox_Instructor->currentText();

    QString employeeid;

    //open connection
    QSqlQuery qry;
    qry.prepare("select empID from Accounts where name ='"+name+"'");


    if(qry.exec( )){
        while(qry.next()){
            employeeid = qry.value(0).toString();
     }
     ui->label_EID->setText(employeeid);

    }
    else{
        QMessageBox::critical(this,tr("Error::"),qry.lastError().text());
    }
}

void modifycoursescreen::on_pushButton_ClearTA_clicked()
{
    ui->comboBox_TA1->setCurrentIndex(-1);
    ui->comboBox_TA2->setCurrentIndex(-1);
    ui->comboBox_TA3->setCurrentIndex(-1);
    ui->comboBox_TA4->setCurrentIndex(-1);
    ui->comboBox_TA5->setCurrentIndex(-1);
}

void modifycoursescreen::on_pushButton_ClearTM_clicked()
{
    ui->comboBox_TM1->setCurrentIndex(-1);
    ui->comboBox_TM2->setCurrentIndex(-1);
    ui->comboBox_TM3->setCurrentIndex(-1);
    ui->comboBox_TM4->setCurrentIndex(-1);
    ui->comboBox_TM5->setCurrentIndex(-1);
}

void modifycoursescreen::on_comboBox_TA1_currentIndexChanged()
{
    QString name=ui->comboBox_TA1->currentText();

    QString employeeid;

    QSqlQuery qry;
    qry.prepare("select empID from Accounts where name ='"+name+"'");

    if(qry.exec( )){
        while(qry.next()){
            employeeid = qry.value(0).toString();
     }
     ui->label_TA1->setText(employeeid);
    }
    else{
        QMessageBox::critical(this,tr("Error::"),qry.lastError().text());
    }
}

void modifycoursescreen::on_comboBox_TA2_currentIndexChanged()
{
    QString name=ui->comboBox_TA2->currentText();


    QString employeeid;
    QSqlQuery qry;
    qry.prepare("select empID from Accounts where name ='"+name+"'");

    if(qry.exec( )){
        while(qry.next()){
            employeeid = qry.value(0).toString();
     }
     ui->label_TA2->setText(employeeid);
    }
    else{
        QMessageBox::critical(this,tr("Error::"),qry.lastError().text());
    }
}

void modifycoursescreen::on_comboBox_TA3_currentIndexChanged()
{
    QString name=ui->comboBox_TA3->currentText();

    QString employeeid;
    QSqlQuery qry;
    qry.prepare("select empID from Accounts where name ='"+name+"'");

    if(qry.exec( )){
        while(qry.next()){
            employeeid = qry.value(0).toString();
     }
     ui->label_TA3->setText(employeeid);
    }
    else{
        QMessageBox::critical(this,tr("Error::"),qry.lastError().text());
    }
}

void modifycoursescreen::on_comboBox_TA4_currentIndexChanged()
{
    QString name=ui->comboBox_TA4->currentText();


    QString employeeid;

    QSqlQuery qry;
    qry.prepare("select empID from Accounts where name ='"+name+"'");

    if(qry.exec( )){
        while(qry.next()){
            employeeid = qry.value(0).toString();
     }
     ui->label_TA4->setText(employeeid);

    }
    else{
        QMessageBox::critical(this,tr("Error::"),qry.lastError().text());
    }
}

void modifycoursescreen::on_comboBox_TA5_currentIndexChanged()
{
    QString name=ui->comboBox_TA5->currentText();


    QString employeeid;

    QSqlQuery qry;
    qry.prepare("select empID from Accounts where name ='"+name+"'");

    if(qry.exec( )){
        while(qry.next()){
            employeeid = qry.value(0).toString();
     }
     ui->label_TA5->setText(employeeid);

    }
    else{
        QMessageBox::critical(this,tr("Error::"),qry.lastError().text());
    }
}

void modifycoursescreen::on_comboBox_TM1_currentIndexChanged()
{
    QString name=ui->comboBox_TM1->currentText();


    QString employeeid;

    QSqlQuery qry;
    qry.prepare("select empID from Accounts where name ='"+name+"'");

    if(qry.exec( )){
        while(qry.next()){
            employeeid = qry.value(0).toString();
     }
     ui->label_TM1->setText(employeeid);

    }
    else{
        QMessageBox::critical(this,tr("Error::"),qry.lastError().text());
    }
}

void modifycoursescreen::on_comboBox_TM2_currentIndexChanged()
{
    QString name=ui->comboBox_TM2->currentText();


    QString employeeid;

    QSqlQuery qry;
    qry.prepare("select empID from Accounts where name ='"+name+"'");

    if(qry.exec( )){
        while(qry.next()){
            employeeid = qry.value(0).toString();
     }
     ui->label_TM2->setText(employeeid);

    }
    else{
        QMessageBox::critical(this,tr("Error::"),qry.lastError().text());
    }
}

void modifycoursescreen::on_comboBox_TM3_currentIndexChanged()
{
    QString name=ui->comboBox_TM3->currentText();

    QString employeeid;

    QSqlQuery qry;
    qry.prepare("select empID from Accounts where name ='"+name+"'");

    if(qry.exec( )){
        while(qry.next()){
            employeeid = qry.value(0).toString();
     }
     ui->label_TM3->setText(employeeid);

    }
    else{
        QMessageBox::critical(this,tr("Error::"),qry.lastError().text());
    }
}

void modifycoursescreen::on_comboBox_TM4_currentIndexChanged()
{
    QString name=ui->comboBox_TM4->currentText();


    QString employeeid;

    QSqlQuery qry;
    qry.prepare("select empID from Accounts where name ='"+name+"'");

    if(qry.exec( )){
        while(qry.next()){
            employeeid = qry.value(0).toString();
     }
     ui->label_TM4->setText(employeeid);

    }
    else{
        QMessageBox::critical(this,tr("Error::"),qry.lastError().text());
    }
}

void modifycoursescreen::on_comboBox_TM5_currentIndexChanged()
{
    QString name=ui->comboBox_TM5->currentText();

    QString employeeid;

    QSqlQuery qry;
    qry.prepare("select empID from Accounts where name ='"+name+"'");

    if(qry.exec( )){
        while(qry.next()){
            employeeid = qry.value(0).toString();
     }
     ui->label_TM5->setText(employeeid);

    }
    else{
        QMessageBox::critical(this,tr("Error::"),qry.lastError().text());
    }
}

void modifycoursescreen::on_pushButton_Import_clicked()
{
    model = new QStandardItemModel(this);
    ui->tableView->setModel(model);
    QString fileName = QFileDialog::getOpenFileName (this, "Open CSV file",
                                                     QDir::currentPath(), "CSV (*.csv)");
    QFile file (fileName);
    if (file.open(QIODevice::ReadOnly)) {
        QString data = file.readAll();
        data.remove( QRegExp("\r") ); //remove all ocurrences of CR (Carriage Return)
        QString temp;
        QChar character;
        QTextStream textStream(&data);
        while (!textStream.atEnd()) {
            textStream >> character;
            if (character == ',') {
                checkString(temp, character);
            } else if (character == '\n') {
                checkString(temp, character);
            } else if (textStream.atEnd()) {
                temp.append(character);
                checkString(temp);
            } else {
                temp.append(character);
            }
        }
    }
}
