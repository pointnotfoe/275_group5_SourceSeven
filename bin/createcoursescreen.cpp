//Release 1.0 By Simon Cheng

#include "createcoursescreen.h"
#include "ui_createcoursescreen.h"
#include "QMessageBox"

CreateCourseScreen::CreateCourseScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateCourseScreen)
{
    ui->setupUi(this);

    //Load TA Comboboxes
    QSqlQueryModel * modal1 = new QSqlQueryModel();

    QSqlQuery qry1;// = new QSqlQuery(conn1.mydb);
    qry1.prepare("select name from Accounts where userType='TA'");
    qry1.exec();
    modal1->setQuery(qry1);
    ui->comboBox_TA1->setModel(modal1);
    ui->comboBox_TA2->setModel(modal1);
    ui->comboBox_TA3->setModel(modal1);
    ui->comboBox_TA4->setModel(modal1);
    ui->comboBox_TA5->setModel(modal1);
    //Set empty
    ui->comboBox_TA1->setCurrentIndex(-1);
    ui->comboBox_TA2->setCurrentIndex(-1);
    ui->comboBox_TA3->setCurrentIndex(-1);
    ui->comboBox_TA4->setCurrentIndex(-1);
    ui->comboBox_TA5->setCurrentIndex(-1);

    QSqlQueryModel * modal2 = new QSqlQueryModel();

    QSqlQuery qry2;// = new QSqlQuery(conn1.mydb);

    qry2.prepare("select name from Accounts where userType='TM'");
    qry2.exec();
    modal2->setQuery(qry2);

    //Load TM ComboBoxes
    ui->comboBox_TM1->setModel(modal2);
    ui->comboBox_TM2->setModel(modal2);
    ui->comboBox_TM3->setModel(modal2);
    ui->comboBox_TM4->setModel(modal2);
    ui->comboBox_TM5->setModel(modal2);
    //Set empty
    ui->comboBox_TM1->setCurrentIndex(-1);
    ui->comboBox_TM2->setCurrentIndex(-1);
    ui->comboBox_TM3->setCurrentIndex(-1);
    ui->comboBox_TM4->setCurrentIndex(-1);
    ui->comboBox_TM5->setCurrentIndex(-1);

    //Load Instructor ComboBox and set to empty
    QSqlQueryModel * modal3 = new QSqlQueryModel();
    QSqlQuery qry3;// = new QSqlQuery(conn2.mydb);
    qry3.prepare("select name from accounts where userType='Instructor'");
    qry3.exec();
    modal3->setQuery(qry3);
    ui->comboBox_Instructor->setModel(modal3);
    ui->comboBox_Instructor->setCurrentIndex(-1);
    //conn2.connClose();


}

CreateCourseScreen::~CreateCourseScreen()
{
    delete ui;
}

void CreateCourseScreen::on_pushButton_Create_clicked()
{

    QString lastIDs,coursenumber2,emptyCheck, studentid, name;
    int valid = 0;

    //Get values from the boxes
    QString coursename,coursenumber,instructor,startDate,endDate,TA1,TA2,TA3,TA4,TA5,TM1,TM2,TM3,TM4,TM5,courseid;
    coursename = ui->lineEdit_CourseName->text();
    coursenumber = ui->lineEdit_CourseNumber->text();
    //instructor = ui->comboBox_Instructor->currentText();
    instructor = ui->label_EID->text();
    startDate = ui->lineEdit_StartDate->text();
    endDate = ui->lineEdit_endDate->text();

    //Get employee ID
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


    QSqlQuery qry;

    //Get username from employee ID query
    qry.prepare ("SELECT username from accounts where empID='"+TA1+"'");
    qry.exec();
    while(qry.next()){
        TA1 = qry.value(0).toString();
    }
    qry.prepare ("SELECT username from accounts where empID='"+TA2+"'");
    qry.exec();
    while(qry.next()){
        TA2 = qry.value(0).toString();
    }
    qry.prepare ("SELECT username from accounts where empID='"+TA3+"'");
    qry.exec();
    while(qry.next()){
        TA3 = qry.value(0).toString();
    }
    qry.prepare ("SELECT username from accounts where empID='"+TA4+"'");
    qry.exec();
    while(qry.next()){
        TA4 = qry.value(0).toString();
    }
    qry.prepare ("SELECT username from accounts where empID='"+TA5+"'");
    qry.exec();
    while(qry.next()){
        TA5 = qry.value(0).toString();
    }
    qry.prepare ("SELECT username from accounts where empID='"+TM1+"'");
    qry.exec();
    while(qry.next()){
        TM1 = qry.value(0).toString();
    }
    qry.prepare ("SELECT username from accounts where empID='"+TM2+"'");
    qry.exec();
    while(qry.next()){
        TM2 = qry.value(0).toString();
    }
    qry.prepare ("SELECT username from accounts where empID='"+TM3+"'");
    qry.exec();
    while(qry.next()){
        TM3 = qry.value(0).toString();
    }
    qry.prepare ("SELECT username from accounts where empID='"+TM4+"'");
    qry.exec();
    while(qry.next()){
        TM4 = qry.value(0).toString();
    }
    qry.prepare ("SELECT username from accounts where empID='"+TM5+"'");
    qry.exec();
    while(qry.next()){
        TM5 = qry.value(0).toString();
    }

    qry.prepare ("SELECT username from accounts where empID='"+instructor+"'");
    qry.exec();
    while(qry.next()){
        instructor= qry.value(0).toString();
    }

    qry.prepare("insert into courses(coursename,coursenumber,startdate,enddate,instructorusername)values ('"+coursename+"','"+coursenumber+"','"+startDate+"','"+endDate+"','"+instructor+"')");


    if(qry.exec( )){
        QMessageBox::critical(this,tr("Save"), tr("saved"));
        valid = 1;
    }
    else{
        QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }

    //find courseid
    qry.prepare("select courseid from courses where coursenumber='"+coursenumber+"' and coursename='"+coursename+"' and startdate='"+startDate+"' and enddate='"+endDate+"'" );
    if(qry.exec()){
        while(qry.next())
         courseid = qry.value(0).toString();
    }

    if(valid == 1){
    //Insert only non-empty TA and TM
        if(TA1!=""){
            qry.exec("insert into CoursesToTATM(courseid,tatmusername)values ('"+courseid+"','"+TA1+"')");
        }
        if(TA2!=""){
            qry.exec("insert into CoursesToTATM(courseid,tatmusername)values ('"+courseid+"','"+TA2+"')");
        }
        if(TA3!=""){
            qry.exec("insert into CoursesToTATM(courseid,tatmusername)values ('"+courseid+"','"+TA3+"')");
        }
        if(TA4!=""){
            qry.exec("insert into CoursesToTATM(courseid,tatmusername)values ('"+courseid+"','"+TA4+"')");
        }
        if(TA5!=""){
            qry.exec("insert into CoursesToTATM(courseid,tatmusername)values ('"+courseid+"','"+TA5+"')");
        }
        if(TM1!=""){
            qry.exec("insert into CoursesToTM(courseid,tmusername)values ('"+courseid+"','"+TM1+"')");
        }
        if(TM2!=""){
            qry.exec("insert into CoursesToTM(courseid,tmusername)values ('"+courseid+"','"+TM2+"')");
        }
        if(TM3!=""){
            qry.exec("insert into CoursesToTM(courseid,tmusername)values ('"+courseid+"','"+TM3+"')");
        }
        if(TM4!=""){
            qry.exec("insert into CoursesToTM(courseid,tmusername)values ('"+courseid+"','"+TM4+"')");
        }
        if(TM5!=""){
            qry.exec("insert into CoursesToTM(courseid,tmusername)values ('"+courseid+"','"+TM5+"')");
        }

        //insert students to Students table and CoursesToStudent
        for(int i=0;i<ui->tableView->model()->rowCount();i++){
            name = ui->tableView->model()->data(ui->tableView->model()->index(i,0)).toString();
            studentid = ui->tableView->model()->data(ui->tableView->model()->index(i,1)).toString();
            qry.exec("insert into CoursesToStudent(courseid,studentid,studentName)values ('"+courseid+"','"+studentid+"','"+name+"')");
        }


        this->hide();
        AdminAssistMain adminassistant;
        adminassistant.setModal(true);
        adminassistant.exec();
    }


  }

void CreateCourseScreen::on_pushButton_Load_clicked()
{

}

void CreateCourseScreen::on_comboBox_currentIndexChanged()
{

}

void CreateCourseScreen::on_pushButton_Back_clicked()
{
    this->hide();
    AdminAssistMain adminassistant;
    adminassistant.setModal(true);
    adminassistant.exec();
}

void CreateCourseScreen::on_pushButton_Import_clicked()
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

void CreateCourseScreen::checkString(QString &temp, QChar character)
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

void CreateCourseScreen::on_comboBox_Instructor_currentIndexChanged()
{
    QString name=ui->comboBox_Instructor->currentText();


    QString employeeid;



    QSqlQuery qry;
    qry.prepare("select empID from accounts where name ='"+name+"'");


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



void CreateCourseScreen::on_pushButton_ClearTA_clicked()
{
    //Set TA related labels and combo boxes to blank
    ui->comboBox_TA1->setCurrentIndex(-1);
    ui->comboBox_TA2->setCurrentIndex(-1);
    ui->comboBox_TA3->setCurrentIndex(-1);
    ui->comboBox_TA4->setCurrentIndex(-1);
    ui->comboBox_TA5->setCurrentIndex(-1);
    ui->label_TA1->setText("");
    ui->label_TA2->setText("");
    ui->label_TA3->setText("");
    ui->label_TA4->setText("");
    ui->label_TA5->setText("");
}

void CreateCourseScreen::on_pushButton_ClearTM_clicked()
{
    //Set TM related labels and combo boxes to blank
    ui->comboBox_TM1->setCurrentIndex(-1);
    ui->comboBox_TM2->setCurrentIndex(-1);
    ui->comboBox_TM3->setCurrentIndex(-1);
    ui->comboBox_TM4->setCurrentIndex(-1);
    ui->comboBox_TM5->setCurrentIndex(-1);
    ui->label_TM1->setText("");
    ui->label_TM2->setText("");
    ui->label_TM3->setText("");
    ui->label_TM4->setText("");
    ui->label_TM5->setText("");
}

//Display EMPLOYEE ID for TA1 etc
void CreateCourseScreen::on_comboBox_TA1_currentIndexChanged()
{
    QString name=ui->comboBox_TA1->currentText();

    QString employeeid;

    QSqlQuery qry;
    qry.prepare("select empID from accounts where name ='"+name+"'");

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

void CreateCourseScreen::on_comboBox_TA2_currentIndexChanged()
{
    QString name=ui->comboBox_TA2->currentText();


    QString employeeid;
    QSqlQuery qry;
    qry.prepare("select empID from accounts where name ='"+name+"'");

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

void CreateCourseScreen::on_comboBox_TA3_currentIndexChanged()
{
    QString name=ui->comboBox_TA3->currentText();
    QString employeeid;
    QSqlQuery qry;
    qry.prepare("select empID from accounts where name ='"+name+"'");

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

void CreateCourseScreen::on_comboBox_TA4_currentIndexChanged()
{
    QString name=ui->comboBox_TA4->currentText();

    QString employeeid;
    QSqlQuery qry;
    qry.prepare("select empID from accounts where name ='"+name+"'");

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

void CreateCourseScreen::on_comboBox_TA5_currentIndexChanged()
{
    QString name=ui->comboBox_TA5->currentText();

    QString employeeid;
    QSqlQuery qry;
    qry.prepare("select empID from accounts where name ='"+name+"'");

    if(qry.exec()){
        while(qry.next()){
            employeeid = qry.value(0).toString();
     }
     ui->label_TA5->setText(employeeid);
    }
    else{
        QMessageBox::critical(this,tr("Error::"),qry.lastError().text());
    }
}

void CreateCourseScreen::on_comboBox_TM1_currentIndexChanged()
{
    QString name=ui->comboBox_TM1->currentText();

    QString employeeid;
    QSqlQuery qry;
    qry.prepare("select empID from accounts where name ='"+name+"'");

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

void CreateCourseScreen::on_comboBox_TM2_currentIndexChanged()
{
    QString name=ui->comboBox_TM2->currentText();

    QString employeeid;
    QSqlQuery qry;
    qry.prepare("select empID from accounts where name ='"+name+"'");

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

void CreateCourseScreen::on_comboBox_TM3_currentIndexChanged()
{
    QString name=ui->comboBox_TM3->currentText();

    QString employeeid;
    QSqlQuery qry;
    qry.prepare("select empID from accounts where name ='"+name+"'");

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

void CreateCourseScreen::on_comboBox_TM4_currentIndexChanged()
{
    QString name=ui->comboBox_TM4->currentText();

    QString employeeid;
    QSqlQuery qry;
    qry.prepare("select empID from accounts where name ='"+name+"'");

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

void CreateCourseScreen::on_comboBox_TM5_currentIndexChanged()
{
    QString name=ui->comboBox_TM5->currentText();

    QString employeeid;
    QSqlQuery qry;
    qry.prepare("select empID from accounts where name ='"+name+"'");

    if(qry.exec()){
        while(qry.next()){
            employeeid = qry.value(0).toString();
     }
     ui->label_TM5->setText(employeeid);
    }
    else{
        QMessageBox::critical(this,tr("Error::"),qry.lastError().text());
    }
}
