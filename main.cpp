#include "mainwindow.h"
#include "bignum.h"
#include <QApplication>

int main(int argc, char *argv[])
{   BigNum f("-11.25");
    BigNum x(-10.2);
    BigNum y = f*x;
    y.print();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
