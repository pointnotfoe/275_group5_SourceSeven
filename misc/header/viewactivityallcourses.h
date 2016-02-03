#ifndef VIEWACTIVITYALLCOURSES_H
#define VIEWACTIVITYALLCOURSES_H

#include <QDialog>
#include "login.h"
#include <QHeaderView>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include "administratorscreen.h"

namespace Ui {
class viewActivityAllCourses;
}

class viewActivityAllCourses : public QDialog
{
    Q_OBJECT

public:
    explicit viewActivityAllCourses(QWidget *parent = 0);
    ~viewActivityAllCourses();

private slots:
    void on_comboBox_currentIndexChanged();

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_export_clicked();

    void on_pushButton_Back_clicked();

private:
    Ui::viewActivityAllCourses *ui;
};

#endif // VIEWACTIVITYALLCOURSES_H
