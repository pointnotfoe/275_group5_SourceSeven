#include "importcsv.h"
#include "ui_importcsv.h"
#include "QMessageBox"

ImportCSV::ImportCSV(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImportCSV)
{
    ui->setupUi(this);
}

ImportCSV::~ImportCSV()
{
    delete ui;
}

void ImportCSV::on_pushButton_Import_clicked()
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

void ImportCSV::checkString(QString &temp, QChar character)
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



void ImportCSV::on_pushButton_Done_clicked()
{
    //login conn;
    QString name,studentid;

//    if(!conn.connOpen()){
//        qDebug()<<"Failed to open the database";
//        return;
//    }

    //conn.connOpen();


    QSqlQuery qry;


    for(int i=0;i<ui->tableView->model()->columnCount();i++){
        name = ui->tableView->model()->data(ui->tableView->model()->index(0,i)).toString();
        studentid = ui->tableView->model()->data(ui->tableView->model()->index(1,i)).toString();
         //qDebug()<<name;
        qry.exec("insert into students(studentid,studentname)values ('"+studentid+"','"+name+"')");

        //ui->label->setText(studentid);
    }

    //conn.connClose();
    this->hide();

}
