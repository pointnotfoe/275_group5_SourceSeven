#ifndef VIEWACTIVITY_H
#define VIEWACTIVITY_H

#include <QDialog>
//#include "manageactivityscreen.h"
#include "globals.h"

namespace Ui {
class viewactivity;
}

class viewactivity : public QDialog
{
    Q_OBJECT

public:
    explicit viewactivity(QWidget *parent = 0);
    ~viewactivity();

private slots:
    void on_activityList_doubleClicked(const QModelIndex &index);

private:
    Ui::viewactivity *ui;
};

#endif // VIEWACTIVITY_H
