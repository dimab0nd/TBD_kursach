#ifndef ADDSESSION_H
#define ADDSESSION_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include "map"
namespace Ui {
class addsession;
}

class addsession : public QDialog
{
    Q_OBJECT

public:
    explicit addsession(QWidget *parent = nullptr);
    ~addsession();
    void getHalls();
    void getFilms();
    void getMultipliers();
    void addNewSession();
    int getFilmDurationById(const int &film_id);

private slots:
    void on_addButton_clicked();

    void on_filmsBox_editTextChanged(const QString &arg1);

private:
    Ui::addsession *ui;
    bool FilmsRefresh = false;
};

#endif // ADDSESSION_H
