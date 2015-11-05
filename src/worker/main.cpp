#include <QCoreApplication>

#include "worker.h"

void usage()
{
	static QString usage_message =
		"Usage: ./worker <server-ip> <server-port> <local-port>\n\n"
		"Example: ./worker 127.0.0.1 8080 9090\n"
		"This will start worker on local port 9090 connected to server which is running on 127.0.0.1:8080.\n"
		"Note: only IPv4 is allowed to use as server-ip.";
	qDebug() << usage_message;
}

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	if (4 != argc)
	{
		usage();
		return 1;
	}
	else
	{
		QString const server_ip_str(argv[1]);
		QString const server_port_str(argv[2]);
		QString const local_port_str(argv[3]);

		QHostAddress const server_ip(server_ip_str);
		quint16 const server_port = server_port_str.toShort();
		quint16 const local_port = local_port_str.toShort();

		worker w(local_port);
		if (!w.connect_to_server(server_ip, quint16(server_port)))
			return 1;

		return a.exec();
	}
}
