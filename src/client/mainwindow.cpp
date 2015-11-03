#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked(bool)), this, SLOT(open()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open()
{
//    parameters.file_name.setFileName(QFileDialog::getOpenFileName(this));

//    QFileDialog::getOpenFileName(this, tr("Open File"), "");
//    QFile file(filen);
//    if (!file.open(QIODevice::ReadOnly)) {
//        return;
//    }
}

const QString task_parameters::input_file_    = "-i";
const QString task_parameters::codec_         = "-vcodec";
const QString task_parameters::frame_rate_    = "-r";
const QString task_parameters::audio_rate_    = "-ar";
const QString task_parameters::size_          = "-s";
const QString task_parameters::frame_density_ = "-g";
const QString task_parameters::video_bitrate_ = "-b";
const QString task_parameters::audio_bitrate_ = "-ab";
