#include "mainwindow.h"
#include <QApplication>
#include "board.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Board *board = new Board(20, 10);
    MainWindow w(board);
    w.show();

    return a.exec();
}
