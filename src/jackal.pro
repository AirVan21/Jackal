TEMPLATE = subdirs
SUBDIRS = client \
	server \
	worker

client.depends = share
server.depends = share
worker.depends = share
