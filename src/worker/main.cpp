#include <QCoreApplication>

#include <share/protocol/message_factory.hpp>

#include "worker.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

    if (argc != 3)
    {
        qDebug() << "Incorrect number of server arguments";
        qDebug() << "Usage: ./server ip_address port_num";
        return 1;
    }
    else
    {
        QString ip_string(argv[1]);
        QString port_string(argv[2]);

        QHostAddress ip_address(ip_string);
        quint16 port_num = port_string.toShort();

        worker w(9090);
        if (!w.connect_to_server(ip_address, (quint16)port_num))
            return 1;

        return a.exec();
    }
}
