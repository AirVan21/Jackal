#ifndef WORKER_MANAGER_H
#define WORKER_MANAGER_H

#include <QVector>
#include <QHostAddress>

class worker_manager
{
public:
    worker_manager();
    void add_new_worker(QHostAddress const & ip, quint16 port);
    void update_worker_load_factor(QHostAddress const & ip, quint16 port, quint32 load_factor);
    QVector<QPair<QHostAddress, quint16> > get_workers();
private:
    QVector<worker_descriptor> workers_;
};

#endif // WORKER_MANAGER_H
