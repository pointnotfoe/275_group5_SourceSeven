#ifndef COMPARISON_H
#define COMPARISON_H

#include <QDialog>

namespace Ui {
class comparison;
}

class comparison : public QDialog
{
    Q_OBJECT

public:
    explicit comparison(QWidget *parent = 0);
    static QString compileC(QString directoryPath,QString inputPath, QString filenameWE, QString filename, QString ouptut_filename);
    ~comparison();

private slots:
    void on_Rubric_clicked();

private:
    Ui::comparison *ui;
};

#endif // COMPARISON_H
