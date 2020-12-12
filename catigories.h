#ifndef CATIGORIES_H
#define CATIGORIES_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QDebug>
#include <QTableWidget>
#include <QMessageBox>
namespace Ui {
class catigories;
}

class catigories : public QDialog
{
    Q_OBJECT

public:
    explicit catigories(QWidget *parent = nullptr);
    ~catigories();
    void refreshCategories();

private slots:

    void on_addButton_clicked();

    void on_tableWidget_itemChanged(QTableWidgetItem *item);

    void on_deleteButton_clicked();

private:
    Ui::catigories *ui;
};

#endif // CATIGORIES_H
