#ifndef TICKET_H
#define TICKET_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QCryptographicHash>

namespace Ui {
class ticket;
}

class ticket : public QDialog
{
    Q_OBJECT

public:
     ticket(QWidget *parent = nullptr, int id_session=0);
    ~ticket();
    void getAllSeatsByRow(const int &row_number);
    void getAllRowsBySessionId(const int &id_session);

    void getAllInfoBySessionId(const int &id_session);
    void getCategoryBySeatId(const int &id_seat);

    int calculateSumm(const int &id_seat);
    void updatesum(const int &sum);

private slots:
    void on_rowsBox_currentIndexChanged(int index);

    void on_seatsBox_currentIndexChanged(int index);

    void on_acceptButton_clicked();

private:
    Ui::ticket *ui;
    int id_session;
    bool isRefresh = false;
};

#endif // TICKET_H
