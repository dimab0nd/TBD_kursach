#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    void refreshSessions();
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
    IsSessionsRefresh = true;

    IsSessionsRefresh = false;
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
    window6->show();
}

