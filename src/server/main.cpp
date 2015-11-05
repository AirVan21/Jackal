#include <QCoreApplication>
#include <QHostAddress>
#include <QDebug>
#include "server.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

    if (argc != 2)
    {
        qDebug() << "Incorrect number of server arguments";
        qDebug() << "Usage: ./server server_port_num";
        return 1;
    }
    else
    {
        QString port_num_string(argv[1]);
        quint16 port_num = port_num_string.toShort();

        server s(port_num);
        return a.exec();
    }


}
