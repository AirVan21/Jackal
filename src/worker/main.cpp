#include <QCoreApplication>

#include <share/protocol/message_factory.hpp>

#include "worker.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	worker w(9090);
	w.connect_to_server(QHostAddress("127.0.0.1"), 8080);

	return a.exec();
}
