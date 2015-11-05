#ifndef WORKER_MANAGER_H
#define WORKER_MANAGER_H

#include <QVector>
#include <QHostAddress>

#include "worker_descriptor.h"

class worker_manager
{
public:
	quint32 add_new_worker(QHostAddress const & ip, quint16 port);
	void remove_worker(quint32 id);
	void update_worker_load_factor(quint32 id, quint32 load_factor);
	QVector<QPair<QHostAddress, quint16> > get_workers();

private:
	QMap<quint32, worker_descriptor> workers_;
	quint32 worker_id_;
};

#endif // WORKER_MANAGER_H
