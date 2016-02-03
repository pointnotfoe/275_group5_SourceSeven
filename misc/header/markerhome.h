#ifndef MARKERHOME_H
#define MARKERHOME_H

#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
class markerhome;
}

class markerhome : public QDialog
{
    Q_OBJECT

public:
    explicit markerhome(QWidget *parent = 0);
    ~markerhome();

private slots:
    void on_logoutButton_clicked();

    void on_courseList_itemDoubleClicked();

private:
    Ui::markerhome *ui;
};

#endif // MARKERHOME_H
