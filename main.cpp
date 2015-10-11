#include "mazemainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MazeMainWindow w;
    w.show();

    return a.exec();
}
