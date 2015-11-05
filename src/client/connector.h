#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QDialog>

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
    QString ip;
    int port;

private slots:
    void set_ip();

    void set_port();

    void openMainWindow();
};

#endif // CONNECTOR_H
