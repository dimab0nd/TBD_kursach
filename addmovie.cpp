#include "addmovie.h"
#include "ui_addmovie.h"
#include <QtSql>
#include <QMessageBox>

addMovie::addMovie(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addMovie)
{
    ui->setupUi(this);
}

addMovie::~addMovie()
{
    delete ui;
}

//void addMovie::setCallback(std::function<void ()> callback)
//{
//    this->callback = callback;
//}

void addMovie::on_pushButton_clicked()
{
    QString title = ui->movieName->text();
    QString genre = ui->movieGenre->text();
    QString year = ui->movieYear->text();
    QString duration = ui->movieDuration->text();
    QString director = ui->movieDirector->text();

    QSqlQuery query;

    query.exec("insert into movie (title, genre, year, duration, director) "
               "values ('" + title + "', '" + genre + "', " + year + ", " + duration + ", '" + director + "')");
    qDebug() << query.lastError().text();
    QMessageBox::information(this, "Сообщение", "Информация успешно добавлена");
//    callback();
    this->close();
}
