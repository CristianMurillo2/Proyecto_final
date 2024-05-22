#include "ventanas.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ventanas w;
    w.show();
    return a.exec();
}
