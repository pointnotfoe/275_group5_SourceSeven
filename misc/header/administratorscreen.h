#ifndef ADMINISTRATORSCREEN_H
#define ADMINISTRATORSCREEN_H

#include <QDialog>
#include"login.h"
#include "login2.h"
#include "viewactivityallcourses.h"

namespace Ui {
class administratorScreen;
}

class administratorScreen : public QDialog
{
    Q_OBJECT

public:
    explicit administratorScreen(QWidget *parent = 0);
    ~administratorScreen();

private slots:

    void on_logoutButton_clicked();

    void on_changepasswordButton_clicked();

    void on_listofcourses_doubleClicked(const QModelIndex &index);





private:
    Ui::administratorScreen *ui;
};

#endif // ADMINISTRATORSCREEN_H
