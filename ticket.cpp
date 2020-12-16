#include "ticket.h"
#include "ui_ticket.h"

Ticket::Ticket(QWidget *parent, int id_session) :
    QDialog(parent),
    ui(new Ui::Ticket),
    id_session(id_session)
{
    ui->setupUi(this);
    getAllInfo();

}

Ticket::~Ticket()
{
    delete ui;
}
