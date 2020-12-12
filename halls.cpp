#include "halls.h"
#include "ui_halls.h"

bool IsHallRefresh = false;

halls::halls(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::halls)
{
    ui->setupUi(this);
    refreshHalls();
}

halls::~halls()
{
    delete ui;
}



void halls::refreshHalls()
{
    IsHallRefresh = true;

    ui->tableWidget->clear();
    int j = ui->tableWidget->rowCount();
    for (int i = 0; i < j; i++) {
        qDebug() << ui->tableWidget->rowAt(0);
        ui->tableWidget->removeRow(0);
    }
    QSqlQuery query;
    if (!query.exec("SELECT * from halls ORDER BY name ASC")) {
        qDebug() << "Ошибка вывода!";
        return;
    };

    ui->tableWidget->setColumnCount(2);
    QStringList labels;
    labels << "Название";
    ui->tableWidget->setHorizontalHeaderLabels(labels);

    int rowCount = 0;
    while (query.next())
    {
        ui->tableWidget->insertRow(rowCount);

        QTableWidgetItem *name = new QTableWidgetItem;
        QTableWidgetItem *idhall = new QTableWidgetItem;

        name->setText(query.value(1).toString());
        idhall->setText(query.value(0).toString());

        ui->tableWidget->setItem(rowCount, 0, name);
        ui->tableWidget->setItem(rowCount, 1, idhall);
        rowCount++;
    }
    ui->tableWidget->setColumnHidden(1,true);
    ui->tableWidget->setCurrentCell(0,0);
    IsHallRefresh = false;
}


void halls::on_addButton_clicked()
{
    QSqlQuery query;

    query.exec("insert into halls (name) "
               "values ('new hall')");
    refreshHalls();
}

void halls::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    if(!IsHallRefresh)
    {
        QString id = ui->tableWidget->item(item->row(),1)->text();
        int y = item->row();
        QSqlQuery query;
        if (!query.exec("update halls set name = '"+
                        ui->tableWidget->item(y, 0)->text() +
                        "' where id_hall = " + id))
        {
            QMessageBox::information(this, "Сообщение", "Произошла ошибка при изменении: " + id);
            return;
        }
        else
            QMessageBox::information(this, "Сообщение", "Изменения применены!");


    }
}

void halls::on_deleteButton_clicked()
{
    int row = ui->tableWidget->currentRow();

    QString id = ui->tableWidget->item(row, 1)->text();
    QSqlQuery query;
    if (!query.exec("delete from halls where id_hall = " + id))
    {
        QMessageBox::information(this, "Сообщение", "Произошла ошибка при удалении: " + id);
        return;
    }
    else
        QMessageBox::information(this, "Сообщение", "Удален зал id: " + id);
    refreshHalls();

}
