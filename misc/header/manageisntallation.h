#ifndef MANAGEISNTALLATION_H
#define MANAGEISNTALLATION_H

#include <QDialog>

namespace Ui {
class ManageIsntallation;
}

class ManageIsntallation : public QDialog
{
    Q_OBJECT

public:
    explicit ManageIsntallation(QWidget *parent = 0);
    ~ManageIsntallation();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::ManageIsntallation *ui;
};

#endif // MANAGEISNTALLATION_H
