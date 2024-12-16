#include "mainwindow.h"
#include "bignum.h"
#include <QApplication>

int main(int argc, char *argv[])
{   BigNum f("11.15");
    BigNum b(10);
    BigNum c = f/b;
    c.print();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
