#ifndef COPYCOURSE_H
#define COPYCOURSE_H

#include <QDialog>
#include "login.h"

namespace Ui {
class copycourse;
}

class copycourse : public QDialog
{
    Q_OBJECT

public:
    explicit copycourse(QWidget *parent = 0);
    ~copycourse();

private slots:
    void on_pushButton_back_clicked();

    void on_comboBox_existingCourse_currentIndexChanged();

    void on_pushButton_clicked();



private:
    Ui::copycourse *ui;
};

#endif // COPYCOURSE_H



