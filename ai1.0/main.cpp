#include "othello.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    othello w;
    w.show();

    return a.exec();
}
