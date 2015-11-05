#include "worker_manager.h"
#include <QtAlgorithms>

quint32 worker_manager::add_new_worker(const QHostAddress &ip, quint16 port)
{
	workers_[worker_id_] = {ip, port, 0};
	qDebug() << "Worker manager: add worker." << workers_.size() << "in queue.";
	return worker_id_++;
}

void worker_manager::remove_worker(quint32 id)
{
	workers_.remove(id);
	qDebug() << "Worker manager: removed worker." << workers_.size() << "in queue.";
}

void worker_manager::update_worker_load_factor(quint32 id, quint32 load_factor)
{
	auto it = workers_.find(id);
	if (workers_.end() != it)
		it->set_load_factor(load_factor);
	else
		qDebug() << "Trying to update load factor to unknown worker. Do nothing.";
}

QVector<QPair<QHostAddress, quint16> > worker_manager::get_workers()
{
	// Always return first 5 workers.
	// TODO: implement more clever choosing algorithm.
	QVector<QPair<QHostAddress, quint16> > workers;
	quint32 count = 5 > workers_.size() ? workers_.size() : 5;
	for (auto const & wd : workers_)
	{
		workers.push_back({wd.get_ip(), wd.get_port()});
		if (0 == --count)
			break;
	}
	return workers;
}
