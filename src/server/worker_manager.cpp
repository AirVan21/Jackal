#include "worker_manager.h"
#include <QtAlgorithms>

void worker_manager::add_new_worker(const QHostAddress &ip, quint16 port)
{
	workers_.push_back(worker_descriptor(ip, port, 0));
}

void worker_manager::update_worker_load_factor(const QHostAddress &ip, quint16 port, quint32 load_factor)
{
	for (auto & worker : workers_)
	{
		if (worker.get_ip() == ip && worker.get_port() == port)
		{
			worker.set_load_factor(load_factor);
		}
	}
}

QVector<QPair<QHostAddress, quint16> > worker_manager::get_workers()
{
	QVector<QPair<QHostAddress, quint16> > workers;
	qSort(workers_.begin(), workers_.end());
	quint32 count = 5 > workers_.size() ? workers_.size() : 5;
	for (quint32 i = 0; i < count; ++i)
	{
		workers.push_back(QPair<QHostAddress, quint16>(workers_[i].get_ip(), workers_[i].get_port()));
	}
	return workers;
}
