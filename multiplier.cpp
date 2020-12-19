#include "multiplier.h"
#include "ui_multiplier.h"

bool IsMultiplierRefresh = false;


multiplier::multiplier(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::multiplier)
{
    ui->setupUi(this);
    refreshMultiplier();

}

multiplier::~multiplier()
{
    delete ui;
}


void multiplier::refreshMultiplier()
{
    IsMultiplierRefresh = true;

    ui->tableWidget->clear();
    int j = ui->tableWidget->rowCount();
    for (int i = 0; i < j; i++) {
        qDebug() << ui->tableWidget->rowAt(0);
        ui->tableWidget->removeRow(0);
    }
    QSqlQuery query;
    if (!query.exec("SELECT * from price_multiplier ORDER BY name ASC")) {
        qDebug() << "Ошибка вывода!";
        return;
    };

    ui->tableWidget->setColumnCount(3);
    QStringList labels;
    labels << "Название типовой расценки" << "Множитель стандартной цены";
    ui->tableWidget->setHorizontalHeaderLabels(labels);

    int rowCount = 0;
    while (query.next())
    {
        ui->tableWidget->insertRow(rowCount);

        QTableWidgetItem *name = new QTableWidgetItem;
        QTableWidgetItem *id = new QTableWidgetItem;
        QTableWidgetItem *multiplier = new QTableWidgetItem;



        name->setText(query.value(1).toString());
        id->setText(query.value(0).toString());
        multiplier->setText(query.value(2).toString());


        ui->tableWidget->setItem(rowCount, 0, name);
        ui->tableWidget->setItem(rowCount, 1, multiplier);
        ui->tableWidget->setItem(rowCount, 2, id);
        rowCount++;
    }
    ui->tableWidget->setColumnHidden(2,true);
    ui->tableWidget->setCurrentCell(0,0);
    IsMultiplierRefresh = false;
}


void multiplier::on_addButton_clicked()
{
    QSqlQuery query;

    query.exec("insert into price_multiplier (name, multiplier) "
               "values ('new type', 1)");
    refreshMultiplier();
}

void multiplier::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    if(!IsMultiplierRefresh)
    {
        QString id = ui->tableWidget->item(item->row(),2)->text();
        int y = item->row();
        QSqlQuery query;
        if (!query.exec("update price_multiplier set name = '"+ ui->tableWidget->item(y, 0)->text() +
                        "', multiplier = " + ui->tableWidget->item(y, 1)->text() +
                        " where id_multiplier = " + id))
        {
            QMessageBox::information(this, "Сообщение", "Произошла ошибка при изменении: " + id);
            return;
        }
        else
            QMessageBox::information(this, "Сообщение", "Изменения применены!");

    }
}

void multiplier::on_deleteButton_clicked()
{
    int row = ui->tableWidget->currentRow();

    QString id = ui->tableWidget->item(row, 2)->text();
    QSqlQuery query;
    if (!query.exec("delete from price_multiplier where id_multiplier = " + id))
    {
        QMessageBox::information(this, "Сообщение", "Произошла ошибка при удалении: " + id);
        return;
    }
    else
        QMessageBox::information(this, "Сообщение", "Вы удалили id: " + id);

    refreshMultiplier();

}

