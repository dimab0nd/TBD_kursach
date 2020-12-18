#ifndef REFUND_H
#define REFUND_H

#include <QDialog>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class refund;
}

class refund : public QDialog
{
    Q_OBJECT

public:
    explicit refund(QWidget *parent = nullptr);
    ~refund();

    int getOrderIdByHash(const QString &hash);


private slots:
    void on_acceptButton_clicked();

private:
    Ui::refund *ui;
};

#endif // REFUND_H
