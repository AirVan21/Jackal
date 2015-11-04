#include "client_logic.h"
#include "mkvmerge_wrapper.h"
#include <share/protocol/message_factory.hpp>
#include <share/protocol/message.h>
#include <share/net/socket.h>
#include <QIODevice>
#include <QDir>
#include <QHash>

using namespace share::net;

client_logic::client_logic(QString filename) : filename_(filename)
{ }

void client_logic::recieve_workers(QVector<QPair<QHostAddress, quint16> > ip_ports)
{
    mkvmerge_wrapper splitter;
    QString segments_dir_name = splitter.split(filename_);
    QDir segments_dir(segments_dir_name);
    segments_dir.setFilter(QDir::Files | QDir::NoSymLinks);

    quint32 next_worker = 0;

    for (QFileInfo & file_info : segments_dir.entryInfoList())
    {
        QString task_path = file_info.absoluteFilePath();
        quint32 task_id = qHash(task_path);
        map_[task_id] = task_path;

        QPair<QHostAddress, quint16> ip_port = ip_ports[next_worker];
        QHostAddress ip = ip_port.first;
        quint16 port = ip_port.second;
        socket task_socket(ip, port);

        QFile file(task_path);
        if (file.open(QIODevice::ReadOnly))
        {
            QByteArray data = file.readAll();
            auto msg = create_message<chunk_message>(client_worker_request, task_id, data.constData(), data.size());
            task_socket.send(*msg);
        }

        next_worker = (next_worker + 1) % ip_ports.size();
    }
}


void client_logic::recieve_chunk(const QHostAddress & /*ip*/, quint16 /*port*/, quint32 /*chunk_id*/, QByteArray /*chunk*/)
{

}


