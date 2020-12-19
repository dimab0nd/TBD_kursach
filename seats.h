#ifndef SEATS_H
#define SEATS_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QDebug>
#include <QTableWidget>
#include <QMessageBox>
#include "map"

namespace Ui {
class seats;
}

class seats : public QDialog
{
    Q_OBJECT

public:
    explicit seats(QWidget *parent = nullptr);
    ~seats();

    void refreshSeats(QString filter);
    void refreshHalls();
    void getAllCategories();

private slots:

    void on_addButton_clicked();

    void on_tableWidget_itemChanged(QTableWidgetItem *item);

    void on_deleteButton_clicked();



    void on_hallsBox_currentIndexChanged(int index);

    void on_pushButton_clicked();
    int getLastSeatNumber(const int &id_hall, const int &row);

private:
    Ui::seats *ui;
    bool IsHallsRefresh = false;
    std::map<int,QString> Categories;

};

#endif // SEATS_H
