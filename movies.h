#ifndef MOVIES_H
#define MOVIES_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QDebug>

#include "addmovie.h"
#include <QTableWidget>
#include <QMessageBox>
namespace Ui {
class movies;
}

class movies : public QDialog
{
    Q_OBJECT


public:
    explicit movies(QWidget *parent = nullptr);
    ~movies();

    void refreshMovies();


private slots:

    void on_addButton_clicked();

    void on_tableWidget_itemChanged(QTableWidgetItem *item);

    void on_deleteButton_clicked();

private:
    Ui::movies *ui;
    addMovie *window1;
//    static inline movies *instance;
};

#endif // MOVIES_H
