#ifndef EDITACTIVITY_H
#define EDITACTIVITY_H

#include <QDialog>
#include "globals.h"
#include "editrubric.h"
#include "editactivity1.h"

namespace Ui {
class editactivity;
}

class editactivity : public QDialog
{
    Q_OBJECT

public:
    explicit editactivity(QWidget *parent = 0);
    ~editactivity();

private slots:
    void on_NextButton_clicked();

    void on_pushButton_path_clicked();

private:
    Ui::editactivity *ui;
};

#endif // EDITACTIVITY_H
