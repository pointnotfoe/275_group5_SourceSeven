#ifndef INSTRUCTORSELECTCOURSESCREEN_H
#define INSTRUCTORSELECTCOURSESCREEN_H

#include <QDialog>
#include "login.h"
#include "login2.h"

namespace Ui {
class instructorSelectCourseScreen;
}

class instructorSelectCourseScreen : public QDialog
{
    Q_OBJECT

public:
    explicit instructorSelectCourseScreen(QWidget *parent = 0);
    void on_listView_activated();
    ~instructorSelectCourseScreen();

private slots:
    //void on_comboBox_Course_activated(const QString &arg1);

    //void on_listWidget_activated(const QModelIndex &index);






    void on_courseList_doubleClicked(const QModelIndex &index);


    //void on_courseList_activated(const QModelIndex &index);

    void on_logoutButton_clicked();
    void on_pushButton_changePassword_clicked();

    //void on_pushButton_6_clicked();

   // void on_pushButton_6_clicked();

private:
    Ui::instructorSelectCourseScreen *ui;
};

#endif // INSTRUCTORSELECTCOURSESCREEN_H




