#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit->setMinimumDate(QDate::currentDate());
    refreshSessions();
    timerId = startTimer(1000);

}

MainWindow::~MainWindow()
{
    delete ui;
    killTimer(timerId);

}

void MainWindow::timerEvent(QTimerEvent *evt)
{
    if (evt->timerId() == timerId)
    {
        QDateTime currTime = QDateTime::currentDateTime();
        ui->timeLabel->setText(currTime.toString("dd.MM.yy hh:mm:ss"));
    }
}


void MainWindow::refreshSessions()
{
    //IsSessionsRefresh = true;

    QDateTime sessionTime;
    if (ui->dateEdit->date() == QDate::currentDate()) {
        sessionTime = QDateTime::currentDateTime();
    } else {
        sessionTime.setDate(ui->dateEdit->date());
    }

    ui->tableWidget->clear();
    int j = ui->tableWidget->rowCount();
    for (int i = 0; i < j; i++) {
        qDebug() << ui->tableWidget->rowAt(0);
        ui->tableWidget->removeRow(0);
    }
    QSqlQuery query;
    if (!query.exec("SELECT movie.title, session.start_time, halls.name, (q2.s - COALESCE(q1.c, 0)) m FROM session "
                    "INNER JOIN halls ON session.id_hall = halls.id_hall "
                    "INNER JOIN movie ON session.id_movie = movie.id_movie "
                    "LEFT JOIN ( "
                    "    SELECT id_session, COUNT(*) c "
                    "    FROM orders GROUP BY id_session "
                    ") q1 ON session.id_session = q1.id_session "
                    "INNER JOIN ( "
                    "    SELECT id_hall, COUNT(*) s "
                    "    FROM seats GROUP BY id_hall "
                    ") q2 ON session.id_hall = q2.id_hall "
                    "WHERE session.start_time >= '" + sessionTime.toString("yyyy.MM.dd hh:mm:ss") + "' "
                    "AND (q2.s - COALESCE(q1.c, 0)) != 0 "
                    "ORDER BY session.start_time ASC ")) {
        qDebug() << "Ошибка вывода сеансов!";
        qDebug() << "SQL error:" << query.lastError().text() << ", SQL error code:" << query.lastError().number();
        return;
    };

    ui->tableWidget->setColumnCount(4);
    QStringList labels;
    labels << "Фильм" << "Начало" << "Зал" << "Осталось мест";
    ui->tableWidget->setHorizontalHeaderLabels(labels);

    int rowCount = 0;
    while (query.next())
    {
        ui->tableWidget->insertRow(rowCount);

        QTableWidgetItem *title = new QTableWidgetItem;
        QTableWidgetItem *start_time = new QTableWidgetItem;
        QTableWidgetItem *session = new QTableWidgetItem;
        QTableWidgetItem *free_seats = new QTableWidgetItem;

        title->setText(query.value(0).toString());
        start_time->setText(query.value(1).toString());
        session->setText(query.value(2).toString());
        free_seats->setText(query.value(3).toString());

        ui->tableWidget->setItem(rowCount, 0, title);
        ui->tableWidget->setItem(rowCount, 1, start_time);
        ui->tableWidget->setItem(rowCount, 2, session);
        ui->tableWidget->setItem(rowCount, 3, free_seats);
        rowCount++;
    }

    //IsSessionsRefresh = false;
}

void MainWindow::on_buyButton_clicked()
{

}

void MainWindow::on_refundButton_clicked()
{

}


void MainWindow::on_movieButton_clicked()
{
    window1 = new movies;
    window1->show();
}

void MainWindow::on_hallsButton_clicked()
{
    window2 = new halls;
    window2->show();
}

void MainWindow::on_categoriesButton_clicked()
{
    window3 = new catigories;
    window3->show();
}

void MainWindow::on_priceButton_clicked()
{
    window4 = new multiplier;
    window4->show();
}

void MainWindow::on_seatsButton_clicked()
{
    window5 = new seats;
    window5->show();
}

void MainWindow::on_addButton_clicked()
{
    window6 = new addsession;
    window6->exec();
    refreshSessions();
}


void MainWindow::on_dateEdit_dateChanged(const QDate &date)
{
    refreshSessions();
}
