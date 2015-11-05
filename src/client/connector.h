#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QDialog>
#include <QHostAddress>
#include <memory>

namespace Ui {
class Connector;
}

class Connector : public QDialog
{
    Q_OBJECT

public:
    explicit Connector(QWidget *parent = 0);
    ~Connector();

private:
    Ui::Connector *ui;
    QString server_ip_string_;
    std::unique_ptr<QHostAddress> server_ip_;
    quint16 port_;

private slots:
    void set_ip();

    void set_port();

    void openMainWindow();
};

#endif // CONNECTOR_H
