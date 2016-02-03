#ifndef COURSEINITIALSCREEN_H
#define COURSEINITIALSCREEN_H

#include <QDialog>
#include "login.h"

namespace Ui {
class CourseScreen;
}

class CourseScreen : public QDialog
{
    Q_OBJECT

public:
    explicit CourseScreen(QWidget *parent = 0);
    ~CourseScreen();
    Ui::CourseScreen *ui;

private slots:

    void on_activityButton_clicked();

    void on_markButton_clicked();

    void on_logoutButton_clicked();

private:

};


#endif // COURSEINITIALSCREEN_H
