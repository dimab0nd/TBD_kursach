#ifndef ADDMOVIE_H
#define ADDMOVIE_H

#include <QDialog>
#include <functional>

namespace Ui {
class addMovie;
}

class addMovie : public QDialog
{
    Q_OBJECT

public:
    explicit addMovie(QWidget *parent = nullptr);
    ~addMovie();
private slots:
    void on_pushButton_clicked();

private:
    Ui::addMovie *ui;
};

#endif // ADDMOVIE_H
