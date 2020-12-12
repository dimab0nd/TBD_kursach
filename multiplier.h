#ifndef MULTIPLIER_H
#define MULTIPLIER_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QDebug>
#include <QTableWidget>
#include <QMessageBox>
namespace Ui {
class multiplier;
}

class multiplier : public QDialog
{
    Q_OBJECT

public:
    explicit multiplier(QWidget *parent = nullptr);
    ~multiplier();
    void refreshMultiplier();

private slots:

    void on_addButton_clicked();

    void on_tableWidget_itemChanged(QTableWidgetItem *item);

    void on_deleteButton_clicked();
private:
    Ui::multiplier *ui;
};

#endif // MULTIPLIER_H
