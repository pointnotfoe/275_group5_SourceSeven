#include "comparison.h"
#include "ui_comparison.h"
#include <stdlib.h>
#include "globals.h"
#include <QString>
#include <QStringList>
#include "login.h"
#include "activityrubric.h"


comparison::comparison(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::comparison)
{
    ui->setupUi(this);

    QSqlQuery qry2;
    qry2.prepare("Select nameOfFile From Activity where activityID = ?");
    qry2.addBindValue(actid);
    qry2.exec();
    qry2.next();
    QString FileNameWE =  qry2.value(0).toString();

    QStringList pieces = FileNameWE.split(".");
    QString filename = pieces.at(0);
    QString extention = pieces.at(1);

    QSqlQuery qry;

    qry.prepare("Select inputFilePath,outputFilePath,consoleInputPath From TestFiles Where activityID = ?");
    qry.addBindValue(actid);
    qry.exec();
    qry.next();
    QString inputPath = qry.value(0).toString();
    QString pathConsolInputs=qry.value(2).toString();
    QString pathCorrectOutput=qry.value(1).toString();

    QSqlQuery gii;
    gii.prepare("select rubricID from Rubric where activityID = ?");
    gii.addBindValue(actid);
    gii.exec();
    gii.next();
    QString rubricID = gii.value(0).toString();

    qry.prepare("Select directoryPath From Rubric where rubricID = '"+rubricID+"'");
    qry.exec();
    qry.next();
    QString directoryPath = qry.value(0).toString() +"/"+studentid;

    QFile consolInputs(pathConsolInputs);
    QFile correctOutput(pathCorrectOutput);

    consolInputs.open(QIODevice::ReadOnly);
    correctOutput.open(QIODevice::ReadOnly);

    QString correctOutputS = correctOutput.readAll();
    QString consolInputsS = consolInputs.readAll();

    consolInputs.close();
    correctOutput.close();

    QString userOutput = compileC(directoryPath,inputPath,FileNameWE,filename,"output.txt");
    ui->UserOuptut->setPlainText (userOutput);
    ui->plainTextEdit->setPlainText (correctOutputS);
}

QString comparison:: compileC(QString directoryPath,QString inputPath, QString filenameWE, QString filename, QString ouptut_filename)
{
    QFile file;
    file.setFileName(filenameWE);

    QFile inputs;
    inputs.setFileName(inputPath);
    inputs.open(QIODevice::ReadOnly);
    QString args = inputs.readAll();
    inputs.close();

    QFile programmingFile;
    programmingFile.setFileName(""+directoryPath+filenameWE);
    programmingFile.copy(""+filenameWE);

    QString output;

    std::system(("g++ "+filenameWE.toStdString()+" -o "+filename.toStdString()).c_str());
    std::system((""+filename.toStdString()+" "+args.toStdString()+" >> "+ouptut_filename.toStdString()).c_str());

    file.open(QIODevice::ReadOnly);
    output =file.readAll();
    file.copy(""+directoryPath+ouptut_filename);
    file.close();

    QFile copyProgramming;
    copyProgramming.setFileName(""+filenameWE);
    copyProgramming.remove();

    QFile ProgramExe;
    ProgramExe.setFileName(""+filename+".exe");
    copyProgramming.remove();

    file.remove();
    return output;
}

void comparison::on_Rubric_clicked()
{
    this->hide();
    activityrubric ar;
    ar.setModal(true);
    ar.exec();
}

comparison::~comparison()
{
    delete ui;
}
