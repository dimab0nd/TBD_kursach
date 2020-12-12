#include "autorization.h"
#include <iostream>
#include <QApplication>

#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    autorization w;
    w.show();

    return a.exec();
}
