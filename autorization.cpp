#include "autorization.h"
#include "ui_autorization.h"
#include <QMessageBox>
#include <QtSql>

autorization::autorization(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::autorization)
{
    ui->setupUi(this);
}

autorization::~autorization()
{
    delete ui;
}

bool sklad(QString login1, QString password1) {
    auto db = QSqlDatabase::addDatabase("QPSQL");
    db.setPort(5432);
    db.setHostName("localhost");
    db.setDatabaseName("cinema");
    db.setUserName(login1);
    db.setPassword(password1);
    return db.open();
}

void autorization::on_pushButton_clicked()
{
    QString login = ui->login->text();
    QString login2 = ui->login->text();
    QString password = ui->pass->text();

    if (not sklad(login, password)) {
            QMessageBox::critical(nullptr, "Ошибка", "Ошибка подключения к БД! Проверьте логин или пароль!");
            return void();
        } else {
        mainwindow = new MainWindow;
        mainwindow->show();
        this->close();
    }
}
