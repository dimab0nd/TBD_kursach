#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "movies.h"
#include "halls.h"
#include "catigories.h"
#include "multiplier.h"
#include "seats.h"
#include "addsession.h"
#include "QDateTime"
#include "QLabel"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void refreshSessions();

private slots:
    void on_buyButton_clicked();

    void on_refundButton_clicked();

    void on_movieButton_clicked();

    void on_hallsButton_clicked();

    void on_categoriesButton_clicked();

    void on_priceButton_clicked();

    void on_seatsButton_clicked();

    void on_addButton_clicked();

    void timerEvent(QTimerEvent *evt);

    void on_dateEdit_dateChanged(const QDate &date);

private:
    Ui::MainWindow *ui;
    movies *window1;
    halls *window2;
    catigories *window3;
    multiplier *window4;
    seats *window5;
    addsession *window6;

    //bool IsSessionsRefresh = false;
    int timerId;

};
#endif // MAINWINDOW_H
