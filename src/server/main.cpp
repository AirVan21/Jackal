#include <QCoreApplication>
#include <QHostAddress>
#include <QDebug>

#include "server.h"

void usage()
{
	static QString usage_message =
		"Usage: ./server <local-port>\n\n"
		"Example: ./server 8080\n"
		"This will start server on local port 8080.";
	qDebug() << usage_message;
}

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	if (2 != argc)
	{
		usage();
		return 1;
	}
	else
	{
		QString const port_str(argv[1]);
		quint16 const port = port_str.toShort();

		server s(port);
		return a.exec();
	}
}
