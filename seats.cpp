#include "seats.h"
#include "ui_seats.h"

bool IsSeatsRefresh = false;



seats::seats(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::seats)
{
    ui->setupUi(this);
    getAllCategories();
    refreshHalls();
    //refreshSeats("");
}

seats::~seats()
{
    delete ui;
}

void seats::getAllCategories()
{
    QSqlQuery query;
    if (!query.exec("SELECT * from categories")) {
        qDebug() << "Ошибка при получении списка категорий!";
        return;
    };
    while (query.next())
    {
        ui->categoryBox->insertItem(0,query.value(1).toString(),query.value(0).toInt());
        Categories[query.value(0).toInt()] = query.value(1).toString();
    }
}

void seats::refreshHalls()
{
    IsHallsRefresh = true;
    QSqlQuery query;
    if (!query.exec("SELECT * from halls")) {
        qDebug() << "Ошибка при получении списка залов!";
        return;
    };
    while (query.next())
    {
        ui->hallsBox->insertItem(0,query.value(1).toString(),query.value(0).toInt());
    }
    ui->hallsBox->setCurrentIndex(-1);
    IsHallsRefresh = false;
}

void seats::refreshSeats(QString filter)
{
    IsSeatsRefresh = true;

    ui->tableWidget->clear();
    int j = ui->tableWidget->rowCount();
    for (int i = 0; i < j; i++) {
        qDebug() << ui->tableWidget->rowAt(0);
        ui->tableWidget->removeRow(0);
    }
    QSqlQuery query;
    if (!query.exec("select * from seats where id_hall = " + filter)) {
        qDebug() << "Ошибка вывода!";
        return;
    };

    ui->tableWidget->setColumnCount(5);
    QStringList labels;
    labels << "Зал" << "Ряд"<< "Номер"<< "Категория";
    ui->tableWidget->setHorizontalHeaderLabels(labels);

    int rowCount = 0;
    while (query.next())
    {
        ui->tableWidget->insertRow(rowCount);

        QTableWidgetItem *idhall = new QTableWidgetItem;
        QTableWidgetItem *idseat = new QTableWidgetItem;
        QTableWidgetItem *idcategory = new QTableWidgetItem;
        QTableWidgetItem *row = new QTableWidgetItem;
        QTableWidgetItem *number = new QTableWidgetItem;

        idhall->setText(query.value(4).toString());
        idseat->setText(query.value(0).toString());
        idcategory->setText(query.value(1).toString());
        row->setText(query.value(2).toString());
        number->setText(query.value(3).toString());

        ui->tableWidget->setItem(rowCount, 0, idhall);
        ui->tableWidget->setItem(rowCount, 1, row);
        ui->tableWidget->setItem(rowCount, 2, number);
        ui->tableWidget->setItem(rowCount, 3, idcategory);
        ui->tableWidget->setItem(rowCount, 4, idseat);
        rowCount++;
    }
    ui->tableWidget->setColumnHidden(4,true);
    ui->tableWidget->setColumnHidden(0,true);
    ui->tableWidget->setCurrentCell(0,0);
    IsSeatsRefresh = false;
}


void seats::on_addButton_clicked()
{

}

void seats::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    //QMessageBox::information(this, "Сообщение", "Произошло изменение");
}

void seats::on_deleteButton_clicked()
{
    int row = ui->tableWidget->currentRow();

    QString id = ui->tableWidget->item(row, 4)->text();
    QSqlQuery query;
    if (!query.exec("delete from seats where id_seat = " + id))
    {
        QMessageBox::information(this, "Сообщение", "Произошла ошибка при удалении: " + id);
        return;
    }
    else
        QMessageBox::information(this, "Сообщение", "Удалено сиденье id: " + id);
    QString id_hall = ui->tableWidget->item(row, 0)->text();
    refreshSeats(id_hall);
}

void seats::on_hallsBox_currentIndexChanged(int index)
{
    if(!IsHallsRefresh && index != -1)
    {
        QString id_hall = ui->hallsBox->itemData(index).toString();
        refreshSeats(id_hall);
//        QMessageBox::information(this, "Сообщение", "Выбран id: " + id_hall);
    }
}


int seats:: getLastSeatNumber(const int &id_hall, const int &row)
{
    QString row_number = QString::number(row);
    QString hall = QString::number(id_hall);


    QSqlQuery query;
    if (!query.exec("select max(number)"
                    " from seats"
                    " where id_hall = "+hall+" and row = "+ row_number+
                    " group by id_hall, row")) {
        QMessageBox::information(this, "Сообщение", "Ошибка getLastSeatNumber!");
        return 0;
    };
    if(query.first())
    {
        int result = query.value(0).toInt();

        return result;

    }
    else return 0;
}


void seats::on_pushButton_clicked()
{
    QString id_hall = ui->hallsBox->currentData().toString();
    QString row = ui->row_number->text();

    int crawler = getLastSeatNumber(ui->hallsBox->currentData().toInt() ,ui->row_number->text().toInt());
    crawler++;

    int seats_count = ui->seats_count->text().toInt();
    seats_count+= crawler;

    QString id_category = ui->categoryBox->currentData().toString();

    QSqlQuery query;
    for( ; crawler < seats_count; crawler++)
    {
        if (!query.exec(
                "insert into seats (number, row, id_hall, id_category)"
                "values (" + QString::number(crawler) +", " + row + ", "+ id_hall + ", " + id_category + ")"))
        {
            QMessageBox::information(this, "Сообщение", "Ошибка!");
            return;
        };
    }

    refreshSeats(id_hall);
}
