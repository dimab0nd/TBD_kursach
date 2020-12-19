#include "ticket.h"
#include "ui_ticket.h"

ticket::ticket(QWidget *parent, int id_session) :
    QDialog(parent),
    ui(new Ui::ticket),
    id_session(id_session)
{
    ui->setupUi(this);
    getAllInfoBySessionId(id_session);
    getAllRowsBySessionId(id_session);
    //QMessageBox::information(this, "Сообщение", "session id = " + QString::number(id_session));
    //QMessageBox::information(this, "Сообщение", "session id 2 = " + QString::number(this->id_session));

}

ticket::~ticket()
{
    delete ui;
}

void ticket::getAllInfoBySessionId(const int &id_session)
{
    QString session = QString::number(id_session);
    QSqlQuery query;
    if (!query.exec("select m.title, m.year, h.name, start_time, start_time + make_interval(mins => duration) as end_time, pm.name, pm.multiplier"
                    " from session"
                    " inner join movie m on m.id_movie = session.id_movie"
                    " inner join halls h on h.id_hall = session.id_hall"
                    " inner join price_multiplier pm on pm.id_multiplier = session.id_multiplier"
                     " where session.id_session = "+session)) {
        QMessageBox::information(this, "Сообщение", "Ошибка getAllInfoBySessionId!");
        return;
    };

    if(query.first())
    {
        QString title = ui->sessionlabel->text() + query.value(0).toString() + " (" + query.value(1).toString() +")";
        ui->sessionlabel->setText(title);

        QString hall = ui->halllabel->text() + query.value(2).toString();
        ui->halllabel->setText(hall);

        QString multiplier = ui->multiplierlabel->text() + query.value(5).toString() + " (x" + query.value(6).toString() +")";
        ui->multiplierlabel->setText(multiplier);

        QDateTime tmp = QDateTime::fromString(query.value(3).toString(), Qt::ISODateWithMs);
        QString start_time = tmp.time().toString("HH:mm:ss");
        tmp = QDateTime::fromString(query.value(4).toString(), Qt::ISODateWithMs);
        QString end_time = tmp.time().toString("HH:mm:ss");

        QString time = ui->timelabel->text() + start_time + " - " + end_time;
        ui->timelabel->setText(time);
    }
    else
        QMessageBox::information(this, "Сообщение", "Ошибка getAllInfoBySessionId query.first()!");
}


void ticket::getAllRowsBySessionId(const int &id_session)
{
    isRefresh = true;
    QString session = QString::number(id_session);
    QSqlQuery query;
    if (!query.exec("select seats.row"
                    " from seats"
                    " inner join halls h on h.id_hall = seats.id_hall"
                    " inner join session s on h.id_hall = s.id_hall"
                    " where id_session = "+session+
                    " group by seats.row")) {
        QMessageBox::information(this, "Сообщение", "Ошибка getAllRowsBySessionId!");
        return;
    };

    while (query.next())
    {
        ui->rowsBox->insertItem(0,query.value(0).toString(), query.value(0).toInt());
    }
    ui->rowsBox->setCurrentIndex(-1);
    isRefresh = false;
}


void ticket:: getAllSeatsByRow(const int &row_number)
{
    isRefresh = true;
    QString session = QString::number(this->id_session);
    QString row = QString::number(row_number);
    ui->seatsBox->clear();
    QSqlQuery query;
    if (!query.exec("select id_seat, number"
                    " from seats t1"
                    " inner join halls h on h.id_hall = t1.id_hall"
                    " inner join session s on h.id_hall = s.id_hall"
                    " where s.id_session = "+session+
                    " and t1.row = "+row+
                    " and not exists "
                    " ("
                            " select o.id_order"
                            " from orders o"
                            " left join refunds r on o.id_order = r.id_order"
                            " where id_session = s.id_session and id_seat = t1.id_seat"
                            " and id_refunds is null"
                    " )")) {
        QMessageBox::information(this, "Сообщение", "Ошибка getAllSeatsByRow!");
        //qDebug() << "SQL error:" << query.lastError().text() << ", SQL error code:" << query.lastError().number();
        return;
    };

    while (query.next())
    {
        ui->seatsBox->insertItem(0,query.value(1).toString(), query.value(0).toInt());
    }
    ui->seatsBox->setCurrentIndex(-1);
    isRefresh = false;
}


void ticket::getCategoryBySeatId(const int &id_seat)
{

    QString seat = QString::number(id_seat);
    QSqlQuery query;
    if (!query.exec("select c.name, c.price"
                    " from seats"
                    " inner join categories c on c.id_category = seats.id_category"
                    " where id_seat = "+seat)) {
        QMessageBox::information(this, "Сообщение", "Ошибка getCategoryBySeatId!");
        return;
    };

    if(query.first())
    {
        QString category = "Тип места: "+query.value(0).toString()+"("+ query.value(1).toString()+"руб. )";
        ui->categorylabel->setText(category);
    }
    else
        QMessageBox::information(this, "Сообщение", "Ошибка getCategoryBySeatId query.first()!");

}


int ticket::calculateSumm(const int &id_seat)
{
    QString session = QString::number(this->id_session);
    QString seat = QString::number(id_seat);
    QSqlQuery query;
    if (!query.exec("select price*multiplier as summa"
                    " from session"
                    " inner join price_multiplier pm on pm.id_multiplier = session.id_multiplier"
                    " inner join seats s on session.id_hall = s.id_hall"
                    " inner join categories c on c.id_category = s.id_category"
                    " where id_session = "+session+
                    " and id_seat = "+seat)) {
        QMessageBox::information(this, "Сообщение", "Ошибка calculateSumm!");
        return -1;
    };
    if(query.first())
    {
        int result = query.value(0).toInt();

        return result;

    }
    else return -1;
}


void ticket:: updatesum(const int &sum)
{
    QString summa = "Итого: "+QString::number(sum);
    ui->summlabel->setText(summa);
}


void ticket::on_rowsBox_currentIndexChanged(int index)
{
    if(!isRefresh)
    {

        int row_number = ui->rowsBox->itemData(index).toInt();
        getAllSeatsByRow(row_number);
        //QMessageBox::information(this, "Сообщение", "Выбран ряд: " + QString::number(row_number));
    }

}


void ticket::on_seatsBox_currentIndexChanged(int index)
{
    if(!isRefresh)
    {
    int id_seat = ui->seatsBox->itemData(index).toInt();
    getCategoryBySeatId(id_seat);
    updatesum(calculateSumm(id_seat));
    }

}


void ticket::on_acceptButton_clicked()
{
    QSqlQuery query;

    query.prepare("insert into public.orders (id_order, id_session, sum, id_seat, hash)"
                  " VALUES (DEFAULT, :id_session, :sum, :id_seat, :hash)");

    int session = this->id_session;
    int id_seat = ui->seatsBox->currentData().toInt();
    int sum = calculateSumm(id_seat);
    //QString tmp = QString::number(session)+QString::number(id_seat);
    std::string tmp = std::to_string(session)+std::to_string(id_seat);

    QString hash = QString(QCryptographicHash::hash((QByteArray::fromStdString(tmp)),QCryptographicHash::Md5).toHex());


    query.bindValue(":id_session", session);
    query.bindValue(":sum", sum);
    query.bindValue(":id_seat", id_seat);
    query.bindValue(":hash", hash);
    if(!query.exec())
    {
        QMessageBox::information(this, "Сообщение", "Ошибка INSERT INTO!");
        return;
    }
    else
        QMessageBox::information(this, "Сообщение", "Успешно!");
    this->close();
}
