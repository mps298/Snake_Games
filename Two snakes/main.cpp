#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    translator.load("snakes_ru.qm", ".");
    a.installTranslator(&translator);
    MainWindow w;
    w.show();

    return a.exec();
}
