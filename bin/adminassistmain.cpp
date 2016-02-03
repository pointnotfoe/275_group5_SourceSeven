#include "adminassistmain.h"
#include "ui_adminassistmain.h"

AdminAssistMain::AdminAssistMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminAssistMain)
{
    ui->setupUi(this);
    //qDebug() << "from login:" <<test ;
}

AdminAssistMain::~AdminAssistMain()
{
    delete ui;
}

void AdminAssistMain::on_pushButton_CreateCourse_clicked()
{
    this->hide();
    CreateCourseScreen createcourse;
    createcourse.setModal(true);
    createcourse.exec();
}

void AdminAssistMain::on_pushButton_ModifyCourse_clicked()
{
    this->hide();
    modifycoursescreen modifycourse;
    modifycourse.setModal(true);
    modifycourse.exec();
}

void AdminAssistMain::on_pushButton_LogOff_clicked()
{
    this->hide();
    login2 log;
    log.setModal(true);
    log.exec();
}

void AdminAssistMain::on_pushButton_clicked()
{
    QApplication::quit() ;
}

void AdminAssistMain::on_pushButton_CopyCourse_clicked()
{
    this->hide();
    copycourse copy;
    copy.setModal(true);
    copy.exec();
}
