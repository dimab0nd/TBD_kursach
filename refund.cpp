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
    QSqlQuery query;

}
