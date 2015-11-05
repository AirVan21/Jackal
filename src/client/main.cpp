#include "connector.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connector h;
    h.setModal(true);
    h.exec();

    return a.exec();
}
