#include "createactivity.h"
#include "ui_createactivity.h"
#include <QFileDialog>
#include <QMessageBox>

CreateActivity::CreateActivity(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateActivity)
{
    ui->setupUi(this);

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

CreateActivity::~CreateActivity()
{
    delete ui;
}

void CreateActivity::on_browseFile_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
                "All files (*.*);;Text File (*.txt);; PDF (*.pdf)"
                );
    QMessageBox::information(this,tr("File name"), filename);
    ui->label->setText(filename);
}

void CreateActivity::on_logout_clicked()
{
    this->hide();
    login2 log;
    log.setModal(true);
    log.exec();
}
void CreateActivity::on_NextButton_clicked()
{


    QString act_name, language, type, path, indGroup;


    act_name = ui->lineEdit_actName->text();
    language = ui->comboBoxLang->currentText();
    type = ui->comboBoxType->currentText();
    indGroup= ui->comboBoxIG->currentText();
    path = ui->label->text();

    actname = act_name;

    QString input,output,consoleinput,consoleoutput,consoleerror, fileNameProg,fileTypeProg;
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
        qry2.prepare("insert into TestFiles(activityID, inputFilePath,outputFilePath, consoleOutputPath, consoleInputPath,consoleErrorPath) VALUES ((SELECT MAX(activityID) FROM Activity),:input,:output,:consoleoutput,:consoleinput,:consoleerror)");
        qry2.bindValue(":input", input);
        qry2.bindValue(":output", output);
        qry2.bindValue(":consoleoutput", consoleoutput);
        qry2.bindValue(":consoleinput", consoleinput);
        qry2.bindValue(":consoleerror", consoleerror);
        qry2.exec();
        qry2.prepare("INSERT into Activity(numberOfFiles,nameOfFile,formatOfFile) VALUES (:numFile,:nameFile,:formatFile)");
        qry2.bindValue(":numFile", '1');
        qry2.bindValue(":nameFile",fileNameProg);
        qry2.bindValue(":formatFile",fileTypeProg);
        qry2.exec();

    }
    qDebug() << "type: " << type;
    int ig = 0;
    if(indGroup == "Group"){
         ig = 1;
    }

    QSqlQuery qry;
    QString fileType, nameFile;
    fileType = ui->comboBox_fileType->currentText();
    nameFile = ui->lineEdit_fileName->text()+fileType;
    qry.prepare("insert into Activity(activityName, TypeAssignment, courseID, ActivityLanguage, isgroup, numberOfFiles,nameOfFile,formatOfFile) VALUES (:act_name,:type,:cid,:language,:isGroup,:numFile,:nameFile,:formatFile)");
    qry.bindValue(":isGroup", ig);
    qry.bindValue(":cid", courseid);
    qry.bindValue(":act_name", act_name);
    qry.bindValue(":type", type);
    qry.bindValue(":language", language);
    qry.bindValue(":numFile", '1');
    qry.bindValue(":nameFile",nameFile);
    qry.bindValue(":formatFile",fileType);

    if(qry.exec()){
        //QMessageBox::Information(this,tr("Save"), tr("saved"));
        QMessageBox::information(this,"Save","Saved");

        qry.prepare("insert into ActivityToSolution(activityID,solutionPath) values ((SELECT MAX(activityID) FROM Activity),'"+path+"')");
        if(qry.exec()){
            QMessageBox::information(this,tr("Save"), tr("saved"));
            this->hide();
            rubric r;
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
        CreateActivity m;
        m.setModal(true);
        m.exec();
    }


}

void CreateActivity::on_pushButton_clicked()
{
    this->hide();
    ManageActivity m;
    m.setModal(true);
    m.exec();
}



void CreateActivity::on_pushButton_input_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open Input File"),
                "C://",
                "All files (*.*);;Text File (*.txt);; PDF (*.pdf)"
                );
    QMessageBox::information(this,tr("File name"), filename);
    ui->lineEdit_input->setText(filename);
}

void CreateActivity::on_pushButton_consoleinput_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open Console Input File"),
                "C://",
                "All files (*.*);;Text File (*.txt);; PDF (*.pdf)"
                );
    QMessageBox::information(this,tr("File name"), filename);
    ui->lineEdit_consoleinput->setText(filename);
}

void CreateActivity::on_pushButton_output_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open Output File"),
                "C://",
                "All files (*.*);;Text File (*.txt);; PDF (*.pdf)"
                );
    QMessageBox::information(this,tr("File name"), filename);
    ui->lineEdit_output->setText(filename);
}

void CreateActivity::on_pushButton_consoleoutput_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open Console Output File"),
                "C://",
                "All files (*.*);;Text File (*.txt);; PDF (*.pdf)"
                );
    QMessageBox::information(this,tr("File name"), filename);
    ui->lineEdit_consoleoutput->setText(filename);
}

void CreateActivity::on_pushButton_erroroutput_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open Console Error Output File"),
                "C://",
                "All files (*.*);;Text File (*.txt);; PDF (*.pdf)"
                );
    QMessageBox::information(this,tr("File name"), filename);
    ui->lineEdit_erroroutput->setText(filename);
}

void CreateActivity::on_comboBoxType_currentIndexChanged()
{
    //If type is programing show all buttons,labels etc
    QString current;
    current = ui->comboBoxType->currentText();
    if (current=="Programming"){
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
        ui->comboBox_fileType_prog->setVisible(false);
        ui->lineEdit_fileName_prog->setVisible(false);
    }
}

