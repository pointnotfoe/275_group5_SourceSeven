#ifndef EDITRUBRIC_H
#define EDITRUBRIC_H
#include <QDialog>
#include "QSqlQuery"
#include "QSqlQueryModel"
#include "login2.h"
#include "globals.h"


namespace Ui {
class editrubric;
}

class editrubric : public QDialog
{
    Q_OBJECT

public:
    explicit editrubric(QWidget *parent = 0);
    ~editrubric();

private slots:
    void on_pushButton_6_clicked();
    void on_pushButton_showTotal_clicked();
    void on_pushButton_finish_clicked();

    void on_pushButton_path_clicked();

private:
    Ui::editrubric *ui;
};
#endif // EDITRUBRIC_H
