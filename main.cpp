#include "wlist.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Wlist w;
    w.show();

    return a.exec();
}
