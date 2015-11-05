#include "connector.h"
#include "ui_connector.h"
#include "mainwindow.h"

Connector::Connector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Connector)
{
    ui->setupUi(this);

    connect(ui->ipLineEdit, SIGNAL(textChanged(QString)), this, SLOT(set_ip()));
    connect(ui->portLineEdit, SIGNAL(textChanged(QString)), this, SLOT(set_port()));
    connect(ui->connectPushButton,SIGNAL(clicked(bool)), this, SLOT(openMainWindow()));
}

Connector::~Connector()
{
    delete ui;
}

void Connector::set_ip()
{
    server_ip_string_ = ui->ipLineEdit->text();
    server_ip_ = std::make_unique<QHostAddress>(server_ip_string_);
}

void Connector::set_port()
{
    port_ = ui->portLineEdit->text().toShort();
}

void Connector::openMainWindow()
{
    if (ui->ipLineEdit->text().isEmpty() || ui->portLineEdit->text().isEmpty())
    {
        return;
    }
    else
    {
        setModal(false);
        MainWindow *w = new MainWindow(this);
        w->connect_to_server(*server_ip_, port_);
        w->show();
        close();
    }
}
