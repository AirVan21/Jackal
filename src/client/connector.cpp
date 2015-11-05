#include "connector.h"
#include "ui_connector.h"
#include "mainwindow.h"

Connector::Connector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Connector)
{
    ui->setupUi(this);

    ui->ipComboBox->addItem("8080", QVariant(8080));
    ui->portComboBox->addItem("192.168.64.86", QVariant(QString("192.168.64.86")));

    connect(ui->ipComboBox,SIGNAL(clicked(bool)), this, SLOT(set_ip()));
    connect(ui->portComboBox,SIGNAL(clicked(bool)), this, SLOT(set_port()));
    connect(ui->connectPushButton,SIGNAL(clicked(bool)), this, SLOT(openMainWindow()));
}

Connector::~Connector()
{
    delete ui;
}

void Connector::set_ip()
{
    ip = ui->ipComboBox->itemData(ui->ipComboBox->currentIndex()).toString();
}

void Connector::set_port()
{
    port = ui->portComboBox->itemData(ui->portComboBox->currentIndex()).toInt();
}

void Connector::openMainWindow()
{
    setModal(false);
    MainWindow *w = new MainWindow(this);
    w->show();
    close();
}
