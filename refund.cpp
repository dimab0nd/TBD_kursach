#include "refund.h"
#include "ui_refund.h"

refund::refund(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::refund)
{
    ui->setupUi(this);
}

refund::~refund()
{
    delete ui;
}

void refund::on_acceptButton_clicked()
{

    QString hash = ui->lineEdit->text();
    int order_id = getOrderIdByHash(hash);

    QSqlQuery query;

    if(order_id)
    {
        query.prepare("insert into refunds (id_refunds, id_order) VALUES (default, :id_order)");
        query.bindValue(":id_order", order_id);
        if(!query.exec())
        {
            QMessageBox::information(this, "Сообщение", "Ошибка INSERT INTO!");
            return;
        }
        else
            QMessageBox::information(this, "Сообщение", "Успешно!");
        this->close();
    }
    else
        QMessageBox::information(this, "Сообщение", "Такого заказа не существует!");
    }


int refund::getOrderIdByHash(const QString &hash)
{
    QSqlQuery query;
    if (!query.exec("select id_order"
                    " from orders"
                    " where hash = '"+hash+"'")) {
        QMessageBox::information(this, "Сообщение", "Ошибка getSessionIdByHash!");
        return 0;
    };
    if(query.first())
    {
        int result = query.value(0).toInt();

        return result;

    }
    else return 0;
}
