#ifndef CHANGEINFO_H
#define CHANGEINFO_H

#include <QDialog>

namespace Ui {
class changeinfo;
}

class changeinfo : public QDialog
{
    Q_OBJECT

public:
    explicit changeinfo(QWidget *parent = 0);
    ~changeinfo();

private slots:
    void on_pushButton_confirm_clicked();

private:
    Ui::changeinfo *ui;
};

#endif // CHANGEINFO_H
