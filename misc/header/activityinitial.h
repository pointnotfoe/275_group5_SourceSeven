#ifndef ACTIVITYINITIAL_H
#define ACTIVITYINITIAL_H

#include <QDialog>

namespace Ui {
class activityinitial;
}

class activityinitial : public QDialog
{
    Q_OBJECT

public:
    explicit activityinitial(QWidget *parent = 0);
    ~activityinitial();

private slots:
    void on_studentList_doubleClicked(const QModelIndex &index);

private:
    Ui::activityinitial *ui;
};

#endif // ACTIVITYINITIAL_H
