#include "catigories.h"
#include "ui_catigories.h"

bool IsCategoryRefresh = false;

catigories::catigories(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::catigories)
{
    ui->setupUi(this);
    refreshCategories();
}

catigories::~catigories()
{
    delete ui;
}


void catigories::refreshCategories()
{
    IsCategoryRefresh = true;

    ui->tableWidget->clear();
    int j = ui->tableWidget->rowCount();
    for (int i = 0; i < j; i++) {
        qDebug() << ui->tableWidget->rowAt(0);
        ui->tableWidget->removeRow(0);
    }
    QSqlQuery query;
    if (!query.exec("SELECT * from categories ORDER BY name ASC")) {
        qDebug() << "Ошибка вывода!";
        return;
    };

    ui->tableWidget->setColumnCount(3);
    QStringList labels;
    labels << "Название" << "Стандартная цена";
    ui->tableWidget->setHorizontalHeaderLabels(labels);

    int rowCount = 0;
    while (query.next())
    {
        ui->tableWidget->insertRow(rowCount);

        QTableWidgetItem *name = new QTableWidgetItem;
        QTableWidgetItem *idcategory = new QTableWidgetItem;
        QTableWidgetItem *price = new QTableWidgetItem;


        name->setText(query.value(1).toString());
        idcategory->setText(query.value(0).toString());
        price->setText(query.value(2).toString());


        ui->tableWidget->setItem(rowCount, 0, name);
        ui->tableWidget->setItem(rowCount, 1, price);
        ui->tableWidget->setItem(rowCount, 2, idcategory);
        rowCount++;
    }
    ui->tableWidget->setColumnHidden(2,true);
    ui->tableWidget->setCurrentCell(0,0);
    IsCategoryRefresh = false;
}


void catigories::on_addButton_clicked()
{
    QSqlQuery query;

    query.exec("insert into categories (name, price) "
               "values ('temp', 0)");
    refreshCategories();
}

void catigories::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    if(!IsCategoryRefresh)
    {
        QString id = ui->tableWidget->item(item->row(),2)->text();
        int y = item->row();
        QSqlQuery query;
        if (!query.exec("update categories set name = '" + ui->tableWidget->item(y, 0)->text() +
                        "' , price = "+ ui->tableWidget->item(y, 1)->text() +
                        " where id_category = " + id))
        {
            QMessageBox::information(this, "Сообщение", "Произошла ошибка при изменении: " + id);
            return;
        }
    }
}

void catigories::on_deleteButton_clicked()
{
    int row = ui->tableWidget->currentRow();

    QString id = ui->tableWidget->item(row, 2)->text();
    QSqlQuery query;
    if (!query.exec("delete from categories where id_category = " + id))
    {
        QMessageBox::information(this, "Сообщение", "Произошла ошибка при удалении: " + id);
        return;
    }
    else
        QMessageBox::information(this, "Сообщение", "Удалена категория id: " + id);
    refreshCategories();

}
