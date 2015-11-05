#include "worker_descriptor.h"

worker_descriptor::worker_descriptor(const QHostAddress &ip, quint16 port, quint32 load_factor) : ip_(ip), port_(port), load_factor_(load_factor)
{ }

QHostAddress worker_descriptor::get_ip() const
{
    return ip_;
}

quint16 worker_descriptor::get_port() const
{
    return port_;
}

quint32 worker_descriptor::get_load_factor() const
{
    return load_factor_;
}

void worker_descriptor::set_load_factor(quint32 const & value)
{
    load_factor_ = value;
}

bool operator<(const worker_descriptor &lhs, const worker_descriptor &rhs)
{
    return lhs.get_load_factor() < rhs.get_load_factor();

}
