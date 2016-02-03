#ifndef ACTIVITYRUBRIC_H
#define ACTIVITYRUBRIC_H

#include <QDialog>

namespace Ui {
class activityrubric;
}

class activityrubric : public QDialog
{
    Q_OBJECT

public:
    explicit activityrubric(QWidget *parent = 0);
    ~activityrubric();

private slots:
    //void on_submTable_doubleClicked();

    void on_saveButton_pressed();

    void on_closeButton_clicked();

    void on_subFiles_clicked();

private:
    Ui::activityrubric *ui;
};

#endif // ACTIVITYRUBRIC_H
