#ifndef IMPORTCSV_H
#define IMPORTCSV_H

#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QStandardItemModel>
#include <QString>
#include "login.h"


namespace Ui {
class ImportCSV;
}

class ImportCSV : public QDialog
{
    Q_OBJECT

public:
    explicit ImportCSV(QWidget *parent = 0);
    ~ImportCSV();

private slots:
    void on_pushButton_Import_clicked();
    void checkString(QString &temp, QChar character = 0);

    void on_pushButton_Done_clicked();

private:
    Ui::ImportCSV *ui;
    QList<QStringList> csv;
    QStandardItemModel *model;
    QList<QStandardItem*> standardItemList;
};

#endif // IMPORTCSV_H
