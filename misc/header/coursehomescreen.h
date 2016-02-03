#ifndef COURSEHOMESCREEN_H
#define COURSEHOMESCREEN_H

#include <QDialog>
#include "login2.h"

namespace Ui {
class Coursehomescreen;
}

class Coursehomescreen : public QDialog
{
    Q_OBJECT

public:
    explicit Coursehomescreen(QWidget *parent = 0);
    ~Coursehomescreen();

private slots:
    void on_markbutton_clicked();

    void on_activitiesbutton_clicked();

    void on_logoutbutton_clicked();

    void on_backbutton_clicked();

private:
    Ui::Coursehomescreen *ui;
};

#endif // COURSEHOMESCREEN_H
