#ifndef RUBRIC_H
#define RUBRIC_H

#include <QDialog>
#include "login2.h"
#include "QMessageBox"

namespace Ui {
class rubric;
}

class rubric : public QDialog
{
    Q_OBJECT

public:
    explicit rubric(QWidget *parent = 0);
    ~rubric();

private slots:
    void on_pushButton_6_clicked(); //logout

    void on_pushButton_showTotal_clicked();
    void on_pushButton_path_clicked();
    void on_pushButton_finish_clicked();

private:
    Ui::rubric *ui;
};

#endif // RUBRIC_H
