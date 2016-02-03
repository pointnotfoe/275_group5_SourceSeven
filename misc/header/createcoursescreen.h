#ifndef CREATECOURSESCREEN_H
#define CREATECOURSESCREEN_H

#include <QDialog>
#include "login.h"
#include "importcsv.h"

namespace Ui {
class CreateCourseScreen;
}

class CreateCourseScreen : public QDialog
{
    Q_OBJECT

public:
    explicit CreateCourseScreen(QWidget *parent = 0);
    ~CreateCourseScreen();

private slots:
    void checkString(QString &temp, QChar character = 0);
    void on_pushButton_Create_clicked();

    void on_pushButton_Load_clicked();

    void on_comboBox_currentIndexChanged();

    void on_pushButton_Back_clicked();

    void on_pushButton_Import_clicked();

    void on_comboBox_Instructor_currentIndexChanged();

   // void on_comboBox_Instructor_activated(const QString &arg1);

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

private:
    Ui::CreateCourseScreen *ui;
    QList<QStringList> csv;
    QStandardItemModel *model;
    QList<QStandardItem*> standardItemList;
};

#endif // CREATECOURSESCREEN_H
