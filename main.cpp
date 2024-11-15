#include "testedit.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    testEdit w;
    w.show();
    return a.exec();
}
