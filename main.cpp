#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qsrand(QTime::currentTime().msec());
    MainWindow w;
    w.show();
    w.setFixedSize(w.width(), w.height());

    return a.exec();
}
