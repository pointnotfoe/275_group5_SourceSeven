#ifndef LOGIN2_H
#define LOGIN2_H

#include <QMainWindow>
#include <QtSql>
#include <QDialog>
#include <QDebug>
#include <QFileInfo>
#include "adminassistmain.h"
#include "instructorselectcoursescreen.h"
#include "markerhome.h"

namespace Ui {
class login2;
}

class login2 : public QDialog
{
    Q_OBJECT

public:
    explicit login2(QWidget *parent = 0);
    ~login2();


private slots:
    void on_pushButton_clicked();

private:
    Ui::login2 *ui;


};

#endif // LOGIN2_H
