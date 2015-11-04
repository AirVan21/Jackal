#include "worker_manager.h"
#include <QtAlgorithms>

worker_manager::worker_manager()
{

}

void worker_manager::add_new_worker(const QHostAddress &ip, quint16 port)
{
    workers_.push_back(worker_descriptor(ip, port, 0));
}

void worker_manager::update_worker_load_factor(const QHostAddress &ip, quint16 port, quint32 load_factor)
{
    for (auto it = workers_.begin(); it != workers_.end(); ++it)
    {

        if (it->get_ip() == ip && it->get_port() == port)
        {
            it->set_load_factor(load_factor);
        }
    }
}

QVector<QPair<QHostAddress, quint16> > worker_manager::get_workers()
{
    QVector<QPair<QHostAddress, quint16> > workers;
    qSort(workers_.begin(), workers_.end());
    /*
     * And if there are less than five workers?
     */
    for (quint32 i = 0; i < 5; ++i)
    {
        workers.push_back(QPair<QHostAddress, quint16>(workers_[i].get_ip(), workers_[i].get_port()));
    }
    return workers;
}
