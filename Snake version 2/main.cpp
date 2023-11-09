#include "mainwindow.h"
#include <QTime>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
     qsrand(QTime::currentTime().msec());
    MainWindow w;
    w.show();
    w.setFixedSize(w.width(), w.height());

    return a.exec();
}
