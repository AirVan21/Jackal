#include <QCoreApplication>

#include <share/protocol/message_factory.hpp>

#include "worker.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	worker w(9090);
	if (!w.connect_to_server(QHostAddress("192.168.0.46"), 8080))
		return 1;

	return a.exec();
}
