#include "mainwindow.h"
#include "minestormgame.h"
#include <QSize>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MinestormGame game(QSize(1000,600));
    MainWindow w(&game);
    return a.exec();
}
