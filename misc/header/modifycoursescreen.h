#ifndef MODIFYCOURSESCREEN_H
#define MODIFYCOURSESCREEN_H

#include <QDialog>
#include "login.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QStandardItemModel>
#include <QString>

namespace Ui {
class modifycoursescreen;
}

class modifycoursescreen : public QDialog
{
    Q_OBJECT

public:
    explicit modifycoursescreen(QWidget *parent = 0);
    ~modifycoursescreen();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_Modify_clicked();

    void on_pushButton_deleteCourse_clicked();

    void on_comboBox_currentIndexChanged();

    void on_comboBox_Instructor_currentIndexChanged();

    void on_pushButton_ClearTA_clicked();

    void on_pushButton_ClearTM_clicked();

    void on_comboBox_TA1_currentIndexChanged();

    void on_comboBox_TA2_currentIndexChanged();

    void on_comboBox_TA3_currentIndexChanged();

    void on_comboBox_TA4_currentIndexChanged();

    void on_comboBox_TA5_currentIndexChanged();

    void on_comboBox_TM1_currentIndexChanged();

    void on_comboBox_TM2_currentIndexChanged();

    void on_comboBox_TM3_currentIndexChanged();

    void on_comboBox_TM4_currentIndexChanged();

    void on_comboBox_TM5_currentIndexChanged();

    void checkString(QString &temp, QChar character = 0);

    void on_pushButton_Import_clicked();

private:
    Ui::modifycoursescreen *ui;


    QList<QStringList> csv;
    QStandardItemModel *model;
    QList<QStandardItem*> standardItemList;
};

#endif // MODIFYCOURSESCREEN_H




