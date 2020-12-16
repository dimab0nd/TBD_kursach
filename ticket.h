#ifndef TICKET_H
#define TICKET_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class Ticket;
}

class Ticket : public QDialog
{
    Q_OBJECT

public:
    explicit Ticket(QWidget *parent = nullptr, int id_session = 1);
    ~Ticket();
    void getAllSeatsBySessionId(const int &id_session);

private:
    Ui::Ticket *ui;
    int id_session;
};

#endif // TICKET_H
