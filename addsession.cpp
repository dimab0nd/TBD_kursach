#include "addsession.h"
#include "ui_addsession.h"

addsession::addsession(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addsession)
{
    ui->setupUi(this);
    getFilms();
    getHalls();
    getMultipliers();

}


int addsession::getFilmDurationById(const int &film_id)
{
    QSqlQuery query;
    QString id_movie = QString::number(film_id);
    if (!query.exec("select duration from movie where id_movie = "+id_movie)) {
        QMessageBox::information(this, "Сообщение", "Ошибка getFilmDurationById!");
        return -1;
    };
    if(query.first())
    {
        return query.value(0).toInt();
    }
    else
        return -1;

}

void addsession::getFilms()
{
    FilmsRefresh = true;
    ui->filmsBox->clear();
    QSqlQuery query;
    if (!query.exec("SELECT id_movie, title, year from movie")) {
        qDebug() << "Ошибка при получении списка фильмов!";
        return;
    };
    while (query.next())
    {
        QString title = query.value(1).toString() + " (" +query.value(2).toString()+ ")";
        ui->filmsBox->insertItem(0,title,query.value(0).toInt());
        //Categories[query.value(0).toInt()] = query.value(1).toString();
    }
    FilmsRefresh = false;
}
void addsession::getHalls()
{
    QSqlQuery query;
    if (!query.exec("SELECT * from halls")) {
        qDebug() << "Ошибка при получении списка залов!";
        return;
    };
    while (query.next())
    {
        ui->hallsBox->insertItem(0,query.value(1).toString() ,query.value(0).toInt());
    }
}
void addsession::getMultipliers()
{
    QSqlQuery query;
    if (!query.exec("SELECT * from price_multiplier")) {
        qDebug() << "Ошибка при получении списка залов!";
        return;
    };
    while (query.next())
    {
        QString name = query.value(1).toString() + " x"+query.value(2).toString();
        ui->multiplierBox->insertItem(0, name ,query.value(0).toInt());
    }

}
addsession::~addsession()
{
    delete ui;
}
void addsession::addNewSession()
{
    QSqlQuery query;
    bool check = false;

    QString id_hall = ui->hallsBox->currentData().toString();
    QDateTime newDateTime = ui->dateTimeEdit->dateTime();
    int id_movie = ui->filmsBox->currentData().toInt();
    int secs_duration = getFilmDurationById(id_movie);
    int id_multiplier = ui->multiplierBox->currentData().toInt();

    if(secs_duration==-1)
    {
        QMessageBox::information(this, "Сообщение", "Ошибка!");
        return;
    }
    else
      secs_duration *= 60;

    QDateTime newDateTimeEnd = newDateTime.addSecs(secs_duration);

    if (!query.exec("select start_time, start_time + make_interval(mins => duration) as end_time"
                    " from session"
                    " inner join halls h on session.id_hall = h.id_hall"
                    " inner join movie m on m.id_movie = session.id_movie"
                    " where session.id_hall = "+id_hall+
                    " order by end_time ASC"))
    {
        QMessageBox::information(this, "Сообщение", "Ошибка!");
        return;
    };
    while (query.next())
    {
        QDateTime crawlerStart = query.value(0).toDateTime();
        QDateTime crawlerEnd = query.value(1).toDateTime();
        if((newDateTime>=crawlerStart && newDateTime<=crawlerEnd) || (newDateTimeEnd >= crawlerStart && newDateTimeEnd <=crawlerEnd))
        {
            check = true;
            QMessageBox::information(this, "Сообщение", "Время занято!");
            return;
        }
    }
    if(!check)
    {
        query.prepare("INSERT INTO session (id_session, id_movie, id_hall, start_time, id_multiplier) "
                      "VALUES (DEFAULT, :id_movie, :id_hall, :start_time, :id_multiplier)");
        query.bindValue(":id_movie", id_movie);
        query.bindValue(":id_hall", id_hall.toInt());
        query.bindValue(":id_multiplier", id_multiplier);
        query.bindValue(":start_time", newDateTime.toString("yyyy.MM.dd. hh:mm:ss"));
        if(!query.exec())
        {
            QMessageBox::information(this, "Сообщение", "Ошибка INSERT INTO!");
            return;
        }
        else
            QMessageBox::information(this, "Сообщение", "Успешно!");

    }



}
void addsession::on_addButton_clicked()
{
    //QMessageBox::information(this, "Сообщение", ui->dateTimeEdit->dateTime().toString("dd.MM.yyyy hh:mm"));
    //QMessageBox::information(this, "Сообщение",ui->filmsBox->currentText());
    addNewSession();
}

void addsession::on_filmsBox_editTextChanged(const QString &arg1)
{
}
