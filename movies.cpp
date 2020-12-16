#include "movies.h"
#include "ui_movies.h"

bool IsRefresh = false;

movies::movies(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::movies)
{
    ui->setupUi(this);
    refreshMovies();
}

movies::~movies()
{
    delete ui;
}

void movies::refreshMovies()
{
    IsRefresh = true;

    ui->tableWidget->clear();
    int j = ui->tableWidget->rowCount();
    for (int i = 0; i < j; i++) {
        qDebug() << ui->tableWidget->rowAt(0);
        ui->tableWidget->removeRow(0);
    }
    QSqlQuery query;
    if (!query.exec("SELECT * from movie "
                    "WHERE title ILIKE '" + ui->lineEdit->text() + "%' "
                    "ORDER BY title ASC")) {
        qDebug() << "Ошибка вывода фильмов!";
        return;
    };

    ui->tableWidget->setColumnCount(6);
    QStringList labels;
    labels << "Название" << "Жанр" << "Год" << "Продолжительность (мин.)" << "Режисёр";
    ui->tableWidget->setHorizontalHeaderLabels(labels);

    int rowCount = 0;
    while (query.next())
    {
        ui->tableWidget->insertRow(rowCount);

        QTableWidgetItem *title = new QTableWidgetItem;
        QTableWidgetItem *genre = new QTableWidgetItem;
        QTableWidgetItem *year = new QTableWidgetItem;
        QTableWidgetItem *duration = new QTableWidgetItem;
        QTableWidgetItem *director = new QTableWidgetItem;
        QTableWidgetItem *idmovie = new QTableWidgetItem;

        title->setText(query.value(4).toString());
        genre->setText(query.value(1).toString());
        year->setText(query.value(5).toString());
        duration->setText(query.value(2).toString());
        director->setText(query.value(3).toString());
        idmovie->setText(query.value(0).toString());

        ui->tableWidget->setItem(rowCount, 0, title);
        ui->tableWidget->setItem(rowCount, 1, genre);
        ui->tableWidget->setItem(rowCount, 2, year);
        ui->tableWidget->setItem(rowCount, 3, duration);
        ui->tableWidget->setItem(rowCount, 4, director);
        ui->tableWidget->setItem(rowCount, 5, idmovie);
        rowCount++;
    }
    ui->tableWidget->setColumnHidden(5,true);
    ui->tableWidget->setCurrentCell(0,0);
    IsRefresh = false;
}

void movies::on_addButton_clicked()
{
    window1 = new addMovie;
    window1->exec();
    refreshMovies();
}

void movies::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    if(!IsRefresh)
    {
        QString id = ui->tableWidget->item(item->row(),5)->text();
        int y = item->row();
        QSqlQuery query;
        if (!query.exec("update movie set title = '"+
                        ui->tableWidget->item(y, 0)->text() +
                        "', genre = '" + ui->tableWidget->item(y, 1)->text() +
                        "', year = " + ui->tableWidget->item(y, 2)->text() +
                        ", duration = " + ui->tableWidget->item(y, 3)->text() +
                        ", director = '" + ui->tableWidget->item(y, 4)->text() +
                        "' where id_movie = " + id))
        {
            QMessageBox::information(this, "Сообщение", "Произошла ошибка при изменении: " + id);
            return;
        }


    }
}

void movies::on_deleteButton_clicked()
{
    int row = ui->tableWidget->currentRow();

    QString id_movie = ui->tableWidget->item(row, 5)->text();
    QSqlQuery query;
    if (!query.exec("delete from movie where id_movie = " + id_movie))
    {
        QMessageBox::information(this, "Сообщение", "Произошла ошибка при удалении: " + id_movie);
        return;
    }
    else
    QMessageBox::information(this, "Сообщение", "Удален фильм id: " + id_movie);
    refreshMovies();

}

void movies::on_lineEdit_textChanged(const QString &arg1)
{
    refreshMovies();
}
