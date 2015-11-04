#include "client_logic.h"
#include "mkvmerge_wrapper.h"
#include <share/protocol/message_factory.hpp>
#include <share/protocol/message.h>
#include <share/net/socket.h>
#include <QIODevice>
#include <QDir>
#include <QHash>

using namespace share::net;

client_logic::client_logic(QString filename)
    : manager_(this)
    , filename_(filename)
    , chunk_amount_(0)
{

}

void client_logic::recieve_workers(QVector<QPair<QHostAddress, quint16> > ip_ports)
{
    if (ip_ports.empty())
    {
        return;
    }
    mkvmerge_wrapper splitter;
    QString segments_dir_name = splitter.split(filename_);
    QDir segments_dir(segments_dir_name);
    segments_dir.setFilter(QDir::Files | QDir::NoSymLinks);

    quint32 next_worker = 0;
    quint32 task_id = 0; //think about hash

    for (QFileInfo & file_info : segments_dir.entryInfoList())
    {
        QString task_path = file_info.absoluteFilePath();
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
            ++task_id;
            ++chunk_amount_;
        }

        next_worker = (next_worker + 1) % ip_ports.size();
    }
}


void client_logic::recieve_chunk(const QHostAddress & /*ip*/, quint16 /*port*/, quint32 chunk_id, QByteArray chunk)
{
    QFile file(filename_);
    QFileInfo file_info(file);

    QString target_dirname = file_info.absolutePath() + QDir::separator() + "target";
    QDir target_dir(target_dirname);

    if (!target_dir.exists())
    {
        target_dir.mkdir(target_dirname);
    }

    QString chunk_name = map_[chunk_id];
    QFile chunk_file_dummy(chunk_name);
    QFileInfo chunk_file_info(chunk_file_dummy);

    chunk_name = target_dirname + QDir::separator() + chunk_file_info.baseName();
    QFile chunk_file(chunk_name);
    if (chunk_file.open(QIODevice::WriteOnly))
    {
        chunk_file.write(chunk);
        chunk_file.close();
    }
}


