#ifndef MANAGEACCOUNTS_H
#define MANAGEACCOUNTS_H

#include <QDialog>
#include "login.h"
#include "createaccount.h"


namespace Ui {
class ManageAccounts;
}

class ManageAccounts : public QDialog
{
    Q_OBJECT

public:
    explicit ManageAccounts(QWidget *parent = 0);
    ~ManageAccounts();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_radioButton_systemAdmin_clicked();

    void on_radioButton_administrator_clicked();

    void on_radioButton_adminAssistant_clicked();

    void on_radioButton_instructor_clicked();

    void on_radioButton_TA_clicked();

    void on_radioButton_showAll_clicked();

    void on_pushButton_go_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_confirm_clicked();

private:
    Ui::ManageAccounts *ui;
};

#endif // MANAGEACCOUNTS_H
