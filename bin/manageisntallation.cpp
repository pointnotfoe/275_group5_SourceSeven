#include "manageisntallation.h"
#include "ui_manageisntallation.h"
#include "createaccount.h"
#include "manageaccounts.h"

ManageIsntallation::ManageIsntallation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageIsntallation)
{
    ui->setupUi(this);
}

ManageIsntallation::~ManageIsntallation()
{
    delete ui;
}

void ManageIsntallation::on_pushButton_3_clicked()
{
    createAccount create;
    create.setModal(true);
    create.exec();

}

void ManageIsntallation::on_pushButton_4_clicked()
{

    ManageAccounts manage;
    manage.setModal(true);
    manage.exec();
}
