/*
Copyright (c) 2013, Ronie P. Martinez <ronmarti18@gmail.com>
All rights reserved.

Permission to use, copy, modify, and/or distribute this software for any purpose
with or without fee is hereby granted, provided that the above copyright notice
and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT,
OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA
OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#include "csvreader.h"
#include "ui_csvreader.h"
#include "QMessageBox"

CsvReader::CsvReader(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CsvReader)
{
    ui->setupUi(this);
}

CsvReader::~CsvReader()
{
    delete ui;
}

void CsvReader::on_action_Open_triggered()
{
    model = new QStandardItemModel(this);
    ui->tableView->setModel(model);
    QString fileName = QFileDialog::getOpenFileName (this, "Open CSV file",
                                                     QDir::currentPath(), "CSV (*.csv)");
    QFile file (fileName);
    if (file.open(QIODevice::ReadOnly)) {
        QString data = file.readAll();
        data.remove( QRegExp("\r") ); //remove all ocurrences of CR (Carriage Return)
        QString temp;
        QChar character;
        QTextStream textStream(&data);
        while (!textStream.atEnd()) {
            textStream >> character;
            if (character == ',') {
                checkString(temp, character);
            } else if (character == '\n') {
                checkString(temp, character);
            } else if (textStream.atEnd()) {
                temp.append(character);
                checkString(temp);
            } else {
                temp.append(character);
            }
        }
    }
}

void CsvReader::checkString(QString &temp, QChar character)
{
    if(temp.count("\"")%2 == 0) {
        //if (temp.size() == 0 && character != ',') //problem with line endings
        //    return;
        if (temp.startsWith( QChar('\"')) && temp.endsWith( QChar('\"') ) ) {
             temp.remove( QRegExp("^\"") );
             temp.remove( QRegExp("\"$") );
        }
        //FIXME: will possibly fail if there are 4 or more reapeating double quotes
        temp.replace("\"\"", "\"");
        QStandardItem *item = new QStandardItem(temp);
        standardItemList.append(item);
        if (character != QChar(',')) {
            model->appendRow(standardItemList);
            standardItemList.clear();
        }
        temp.clear();
    } else {
        temp.append(character);
    }
}



void CsvReader::on_tableView_clicked(const QModelIndex &index)
{
    //QString testing;
    //testing = ui->tableView->model()->data(ui->tableView->model()->index(0,1)).toString();
    //ui->label->setText(testing);
}


void CsvReader::on_tableView_activated(const QModelIndex &index)
{

}

void CsvReader::on_pushButton_clicked()
{

    //testing = ui->tableView->model()->data(ui->tableView->model()->index(i,1)).toString();
    //ui->label->setText(testing);

    login conn;
    QString name,studentid;

    if(!conn.connOpen()){
        qDebug()<<"Failed to open the database";
        return;
    }

    //open connection
    /*
    conn.connOpen();
    QSqlQuery qry;
    name = "comeon";
    studentid = "heh";
    qry.prepare("insert into students(name,studentid)values ('"+name+"','"+studentid+"')");
    qry.exec();
    */

    QSqlQuery qry;


    for(int i=0;i<ui->tableView->model()->columnCount();i++){
        name = ui->tableView->model()->data(ui->tableView->model()->index(0,i)).toString();
        studentid = ui->tableView->model()->data(ui->tableView->model()->index(1,i)).toString();
         //qDebug()<<name;
        qry.exec("insert into students(name,studentid)values ('"+name+"','"+studentid+"')");

        //ui->label->setText(studentid);
    }






}
