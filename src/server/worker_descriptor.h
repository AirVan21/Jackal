#ifndef WORKER_DESCRIPTOR_H
#define WORKER_DESCRIPTOR_H

#include <QHostAddress>

class worker_descriptor
{
public:
    worker_descriptor();
    worker_descriptor(QHostAddress const & ip, quint16 port, quint32 load_factor);
    QHostAddress get_ip() const;
    quint16 get_port() const;
    quint32 get_load_factor() const;
    void set_load_factor(quint32 const & value);
private:
    QHostAddress ip_;
    quint16 port_;
    quint32 load_factor_;
};

bool operator<(worker_descriptor const & lhs, worker_descriptor const & rhs);

#endif // WORKER_DESCRIPTOR_H
