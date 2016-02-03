#include "editactivity.h"
#include "ui_editactivity.h"
#include "editrubric.h"

//QString value;

QString actID;
editactivity::editactivity(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editactivity)
{
    ui->setupUi(this);




    qDebug() << "val: " << value;
    ui->lineEdit_actName->setText(value);
    QSqlQuery qry;
    qry.prepare("SELECT TypeAssignment, ActivityLanguage, isGroup from Activity where activityName='"+value+"' and courseID='"+courseid+"'");
    qDebug() << "courseId: " << courseid;
    qry.exec();
    qry.next();
    //SolutionPath
    QString type, lang, isgroup;
    QString input,output,consoleinput,consoleoutput,consoleerror;

    type = qry.value(0).toString();

    //If programming, show programming boxes
    if (type == "Programming"){
        //labels
        ui->programmingtitle->setVisible(true);
        ui->label_inputfile->setVisible(true);
        ui->label_consoleinput->setVisible(true);
        ui->label_output->setVisible(true);
        ui->label_consoleoutput->setVisible(true);
        ui->label_erroroutput->setVisible(true);
       //buttons
        ui->pushButton_input->setVisible(true);
        ui->pushButton_consoleinput->setVisible(true);
        ui->pushButton_output->setVisible(true);
        ui->pushButton_consoleoutput->setVisible(true);
        ui->pushButton_erroroutput->setVisible(true);
        //lineedit
        ui->lineEdit_input->setVisible(true);
        ui->lineEdit_consoleinput->setVisible(true);
        ui->lineEdit_output->setVisible(true);
        ui->lineEdit_consoleoutput->setVisible(true);
        ui->lineEdit_erroroutput->setVisible(true);
        ui->comboBox_fileType_prog->setVisible(true);
        ui->lineEdit_fileName_prog->setVisible(true);
    }
    else{
        //Hide programming stuff
        ui->programmingtitle->setVisible(false);
        ui->label_inputfile->setVisible(false);
        ui->label_consoleinput->setVisible(false);
        ui->label_output->setVisible(false);
        ui->label_consoleoutput->setVisible(false);
        ui->label_erroroutput->setVisible(false);
       //buttons
        ui->pushButton_input->setVisible(false);
        ui->pushButton_consoleinput->setVisible(false);
        ui->pushButton_output->setVisible(false);
        ui->pushButton_consoleoutput->setVisible(false);
        ui->pushButton_erroroutput->setVisible(false);
        //lineedit
        ui->lineEdit_input->setVisible(false);
        ui->lineEdit_consoleinput->setVisible(false);
        ui->lineEdit_output->setVisible(false);
        ui->lineEdit_consoleoutput->setVisible(false);
        ui->lineEdit_erroroutput->setVisible(false);
        ui->comboBoxType->setCurrentIndex(1);
        ui->comboBox_fileType_prog->setVisible(false);
        ui->lineEdit_fileName_prog->setVisible(false);
    }
    int index =  ui->comboBoxType->findText(type);//use default exact match
    if(index >= 0)
         ui->comboBoxType->setCurrentIndex(index);
    qDebug() << "type: " << type;
    lang = qry.value(1).toString();
    index = ui->comboBoxLang->findText(lang); //use default exact match
    if(index >= 0)
         ui->comboBoxLang->setCurrentIndex(index);
    //ui->comboBoxType->currentText(lang);
    qDebug() << "lang: " << lang;
    isgroup = qry.value(2).toString();
    index = ui->comboBoxIG->findText(isgroup); //use default exact match
    if(index >= 0)
         ui->comboBoxIG->setCurrentIndex(index);
    //ui->comboBoxType->currentText(isgroup);
    qDebug() << "isGroup: " << isgroup;
    qry.prepare("select activityID from Activity where activityName='"+value+"'and courseID='"+courseid+"'");
    qry.exec();
    qry.next();
    QString actID = qry.value(0).toString();
    qry.prepare("SELECT solutionPath from ActivityToSolution where activityID='"+actID+"'");
    qry.exec();
    qry.next();
    QString path = qry.value(0).toString();
    ui->label->setText(path);

    if(type == "Programming"){
    qry.prepare("SELECT * from TestFiles where activityID='"+actID+"'");
    input = qry.value(1).toString();
    ui->lineEdit_input->setText(input);
    output= qry.value(2).toString();
    ui->lineEdit_output->setText(output);
    consoleinput= qry.value(4).toString();
    ui->lineEdit_consoleinput->setText(consoleinput);
    consoleoutput= qry.value(3).toString();
    ui->lineEdit_consoleoutput->setText(consoleoutput);
    consoleerror= qry.value(5).toString();
    ui->lineEdit_erroroutput->setText(consoleerror);
    }
}

editactivity::~editactivity()
{
    delete ui;
}



void editactivity::on_NextButton_clicked()
{
    QSqlQuery qry;
    QString act_name, language,type, path,indGroup, fileType,nameFile;
    act_name = ui->lineEdit_actName->text();
    language = ui->comboBoxLang->currentText();
    type = ui->comboBoxType->currentText();
    indGroup= ui->comboBoxIG->currentText();
    path = ui->label->text();
    fileType = ui->comboBox_fileType->currentText();
    nameFile = ui->lineEdit_fileName->text()+fileType;
    qDebug() << "type: " << type;


    int ig = 0;
    if(indGroup == "Group"){
         ig = 1;
    }
    qry.prepare("select activityID from Activity where activityName='"+act_name+"'and courseID='"+courseid+"'");
    qry.exec();
    qry.next();
    QString actID = qry.value(0).toString();
    qDebug() << "ACTIVITY NAME: " << act_name;
    qry.prepare("UPDATE Activity SET numberOfFiles=:numFile,nameOfFile=:nameFile, formatOfFile=:formatFile, activityName=:act_name, TypeAssignment=:type, ActivityLanguage=:language, isgroup=:isGroup where activityID='"+actID+"' and courseID='"+courseid+"';");
    qry.bindValue(":isGroup", ig);
    //qry.bindValue(":courseID", "SELECT courseID from Courses where courseNumber='"+courseid+"')");
    qry.bindValue(":activityName", act_name);
    //ERROR RUBRICID
    //qry.bindValue(":rubricID", "SELECT activityID from Activity where activityName='"+act_name+"')");
    qry.bindValue(":type", type);
    qry.bindValue(":language", language);
    qry.bindValue(":numFile", '1');
    qry.bindValue(":nameFile",nameFile);
    qry.bindValue(":formatFile",fileType);
    //qry.exec();

    if(qry.exec()){
        //QMessageBox::Information(this,tr("Save"), tr("saved"));
        QMessageBox::information(this,"Save","Saved");

        qry.prepare("UPDATE ActivityToSolution SET solutionPath='"+path+"' where activityID='"+actID+"'");
        if(qry.exec()){
            QMessageBox::information(this,tr("Save"), tr("saved"));

            this->hide();
            editrubric r;
            r.setModal(true);
            r.exec();
        }
        else{
            QMessageBox::critical(this,tr("error::"),qry.lastError().text());
        }
    }
    else{
        QMessageBox::critical(this,tr("error::"),qry.lastError().text());
        this->hide();
        editactivity m;
        m.setModal(true);
        m.exec();
    }


    QString input,output,consoleinput,consoleoutput,consoleerror, fileTypeProg, fileNameProg;
    QString current;
    QSqlQuery qry2;

    current = ui->comboBoxType->currentText();
    if (current=="Programming"){
        input = ui->lineEdit_input->text();
        output = ui->lineEdit_output->text();
        consoleinput = ui->lineEdit_consoleinput->text();
        consoleoutput = ui->lineEdit_consoleoutput->text();
        consoleerror= ui->lineEdit_erroroutput->text();
        fileTypeProg = ui->comboBox_fileType_prog->currentText();
        fileNameProg = ui->lineEdit_fileName_prog->text() + fileTypeProg;
         qry2.prepare("UPDATE TestFile SET inputFilePath=:intput,outputFilePath=:output, consoleOutputPath=:consoleoutput,consoleInputPath=:consoleinput,consoleErrorPath=:consoleerror numberOfFiles=:numFile,formatOfFile=:formatFile,nameOfFile=:nameFile where activityID='"+actID+"'");
         qry2.bindValue(":input", input);
         qry2.bindValue(":output", output);
         qry2.bindValue(":consoleoutput", consoleoutput);
         qry2.bindValue(":consoleinput", consoleinput);
         qry2.bindValue(":consoleerror", consoleerror);
         qry.bindValue(":numFile", '1');
         qry.bindValue(":nameFile",fileNameProg);
         qry.bindValue(":formatFile",fileType);
         qry2.exec();
    }
}

void editactivity::on_pushButton_path_clicked()
{

}
