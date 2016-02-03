#ifndef VIEWACT_H
#define VIEWACT_H

#include <QDialog>
#include "globals.h"

namespace Ui {
class viewact;
}

class viewact : public QDialog
{
    Q_OBJECT

public:
    explicit viewact(QWidget *parent = 0);
    ~viewact();

private slots:
    void on_tableView_activated(const QModelIndex &index);

private:
    Ui::viewact *ui;
};

#endif // VIEWACT_H
