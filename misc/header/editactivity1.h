#ifndef EDITACTIVITY1_H
#define EDITACTIVITY1_H

#include <QDialog>
#include "QSqlQuery"
#include "QSqlQueryModel"

namespace Ui {
class editActivity1;
}

class editActivity1 : public QDialog
{
    Q_OBJECT

public:
    explicit editActivity1(QWidget *parent = 0);
    ~editActivity1();

private slots:

    void on_activityList_activated(const QModelIndex &index);

    void on_pushButton_delete_clicked();

    void on_pushButton_select_clicked();

private:
    Ui::editActivity1 *ui;
};

#endif // EDITACTIVITY1_H
