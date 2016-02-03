#ifndef ADMINASSISTMAIN_H
#define ADMINASSISTMAIN_H

#include <QDialog>
#include "createcoursescreen.h"
#include "modifycoursescreen.h"
#include "copycourse.h"
#include "login.h"
#include "login2.h"

namespace Ui {
class AdminAssistMain;
}

class AdminAssistMain : public QDialog
{
    Q_OBJECT

public:
    explicit AdminAssistMain(QWidget *parent = 0);
    ~AdminAssistMain();

private slots:
    void on_pushButton_CreateCourse_clicked();

    void on_pushButton_ModifyCourse_clicked();

    void on_pushButton_LogOff_clicked();

    void on_pushButton_clicked();

    void on_pushButton_CopyCourse_clicked();

private:
    Ui::AdminAssistMain *ui;
};

#endif // ADMINASSISTMAIN_H
