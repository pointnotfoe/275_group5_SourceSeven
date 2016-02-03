#ifndef ACTIVITYHOME_H
#define ACTIVITYHOME_H

#include <QDialog>

namespace Ui {
class activityhome;
}

class activityhome : public QDialog
{
    Q_OBJECT

public:
    explicit activityhome(QWidget *parent = 0);
    ~activityhome();

private slots:
    void on_pushButton_clicked();

    void on_logoutButton_clicked();

    void on_studentList_clicked(const QModelIndex &index);

private:
    Ui::activityhome *ui;
};

#endif // ACTIVITYHOME_H
