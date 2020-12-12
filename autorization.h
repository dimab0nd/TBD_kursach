#ifndef AUTORIZATION_H
#define AUTORIZATION_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class autorization;
}

extern QString login2;

class autorization : public QDialog
{
    Q_OBJECT

public:
    explicit autorization(QWidget *parent = nullptr);
    ~autorization();

private slots:
    void on_pushButton_clicked();

private:
    Ui::autorization *ui;
    MainWindow *mainwindow;
};

#endif // AUTORIZATION_H
