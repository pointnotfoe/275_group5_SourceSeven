#ifndef CREATEACTIVITY_H
#define CREATEACTIVITY_H

#include <QDialog>
#include <QFile>
#include "login.h"
#include "login2.h"
#include "rubric.h"
#include <QFileDialog>

namespace Ui {
class CreateActivity;
}

class CreateActivity : public QDialog
{
    Q_OBJECT

public:
    explicit CreateActivity(QWidget *parent = 0);
    ~CreateActivity();
    //void on_pushButton_6_clicked();

private slots:



    void on_browseFile_clicked();

    void on_logout_clicked();

    void on_NextButton_clicked();

    void on_pushButton_clicked();

    //void on_pushButton_path_clicked();

    void on_pushButton_input_clicked();

    void on_pushButton_consoleinput_clicked();

    void on_pushButton_output_clicked();

    void on_pushButton_erroroutput_clicked();

    void on_pushButton_consoleoutput_clicked();

    void on_comboBoxType_currentIndexChanged();

private:
    Ui::CreateActivity *ui;
};

#endif // CREATEACTIVITY_H





