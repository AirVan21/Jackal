#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QTextStream>

QTextStream cout(stdout);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init_comboboxes();

    connect(ui->selectButton,SIGNAL(clicked(bool)), this, SLOT(open()));
    connect(ui->startButton,SIGNAL(clicked(bool)), this, SLOT(start()));

    connect(ui->pathLine, SIGNAL(textChanged(QString)), this, SLOT(put_path()));

    connect(ui->codecComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(set_codec()));
    connect(ui->sizeComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(set_size()));
    connect(ui->frameRateComboBox,SIGNAL(currentIndexChanged(int)), this, SLOT(set_frame_rate()));
    connect(ui->audioRateComboBox ,SIGNAL(currentIndexChanged(int)), this, SLOT(set_audio_rate()));
    connect(ui->frameDensitySpinBox,SIGNAL(valueChanged(int)), this, SLOT(set_frame_density()));
    connect(ui->videoBitrateComboBox,SIGNAL(currentIndexChanged(int)), this, SLOT(set_video_bitrate()));
    connect(ui->audioBitrateComboBox,SIGNAL(currentIndexChanged(int)), this, SLOT(set_audio_bitrate()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_comboboxes()
{
    ui->frameRateComboBox->addItem("25p", QVariant(25));
    ui->frameRateComboBox->addItem("30p", QVariant(30));
    ui->frameRateComboBox->addItem("48p", QVariant(48));
    ui->frameRateComboBox->addItem("50i", QVariant(50));
    ui->frameRateComboBox->addItem("60i", QVariant(60));
    ui->frameRateComboBox->addItem("72p", QVariant(60));
    ui->frameRateComboBox->addItem("90p", QVariant(90));
    ui->frameRateComboBox->addItem("100p", QVariant(100));
    ui->frameRateComboBox->addItem("120p", QVariant(120));
    ui->frameRateComboBox->addItem("144 fps", QVariant(144));
    ui->frameRateComboBox->addItem("300 fps", QVariant(300));


    ui->sizeComboBox->addItem("320x240", QVariant(QSize(320, 240)));
    ui->sizeComboBox->addItem("480x576", QVariant(QSize(480, 576)));
    ui->sizeComboBox->addItem("640x480", QVariant(QSize(640, 480)));
    ui->sizeComboBox->addItem("720x576 ", QVariant(QSize(720, 576)));
    ui->sizeComboBox->addItem("1024x768", QVariant(QSize(1024, 768)));
    ui->sizeComboBox->addItem("1280x800", QVariant(QSize(1280, 800)));
    ui->sizeComboBox->addItem("1366x768", QVariant(QSize(1366, 768)));
    ui->sizeComboBox->addItem("1280x1024", QVariant(QSize(1280, 1024)));
    ui->sizeComboBox->addItem("1440x900", QVariant(QSize(1440, 900)));
    ui->sizeComboBox->addItem("1920x1080", QVariant(QSize(1920, 1080)));
    ui->sizeComboBox->addItem("1152x864", QVariant(QSize(1152, 864)));
    ui->sizeComboBox->addItem("1360x768", QVariant(QSize(1360, 768)));
    
    ui->audioRateComboBox->addItem("44100 Hz", QVariant(44100));
    ui->audioRateComboBox->addItem("48000 Hz", QVariant(48000));
    ui->audioRateComboBox->addItem("96000 Hz", QVariant(96000));
    ui->audioRateComboBox->addItem("192000 Hz", QVariant(192000));
    ui->audioRateComboBox->addItem("2822400 Hz", QVariant(2822400));
    ui->audioRateComboBox->addItem("5644800 Hz", QVariant(5644800));
    
    ui->codecComboBox->addItem("mpeg4", QVariant(QString("mpeg4")));
    ui->codecComboBox->addItem("aac", QVariant(QString("aac")));
    ui->codecComboBox->addItem("h264", QVariant(QString("h264")));
    ui->codecComboBox->addItem("vp6", QVariant(QString("vp6")));
    
    ui->videoBitrateComboBox->addItem("576 kb/s", QVariant(576));
    ui->videoBitrateComboBox->addItem("896 kb/s", QVariant(896));
    ui->videoBitrateComboBox->addItem("1088 kb/s", QVariant(1088));
    ui->videoBitrateComboBox->addItem("1216 kb/s", QVariant(1216));
    ui->videoBitrateComboBox->addItem("1536 kb/s", QVariant(1536));
    ui->videoBitrateComboBox->addItem("1856 kb/s", QVariant(1856));
    ui->videoBitrateComboBox->addItem("2176 kb/s", QVariant(2176));
    ui->videoBitrateComboBox->addItem("2496 kb/s", QVariant(2496));
    ui->videoBitrateComboBox->addItem("3072 kb/s", QVariant(3072));
    ui->videoBitrateComboBox->addItem("4992 kb/s", QVariant(4992));
    ui->videoBitrateComboBox->addItem("7552 kb/s", QVariant(7552));
    ui->videoBitrateComboBox->addItem("20000 kb/s", QVariant(20000));

    ui->audioBitrateComboBox->addItem("32 kb/s", QVariant(32));
    ui->audioBitrateComboBox->addItem("64 kb/s", QVariant(64));
    ui->audioBitrateComboBox->addItem("128 kb/s", QVariant(128));
    ui->audioBitrateComboBox->addItem("192 kb/s", QVariant(192));
    ui->audioBitrateComboBox->addItem("256 kb/s", QVariant(256));
    ui->audioBitrateComboBox->addItem("320 kb/s", QVariant(320));

}

bool MainWindow::checkFileName()
{
    if (parameters.file_name.fileName().isEmpty())
    {
        ui->statusBar->showMessage("Choose File.", 3000);
        return false;
    }
    else
    {
        QFileInfo checkFile(ui->pathLine->text());
        if (!(checkFile.exists() && checkFile.isFile()))
        {
            ui->statusBar->showMessage("Error: Incorrect File!", 3000);
            return false;
        }
        else
        {
            QString ext = checkFile.suffix();
            // TODO use enum to siplify?
            if (!(ext == "mp4"   ||
                  ext == "avi"   ||
                  ext == "mkv"   ||
                  ext == "mov"   ||
                  ext == "mpeg"  ||
                  ext == "mpeg4" ||
                  ext == "wmv"   ||
                  ext == "flv"))
            {
                ui->statusBar->showMessage("Error: Invalid File Extension!", 3000);
                return false;
            }
        }
    }
    return true;
}

void MainWindow::open()
{
    parameters.file_name.setFileName(QFileDialog::getOpenFileName(this, tr("Open File"), "/",
                                                                  tr("Video File (*.mp4 *.avi *.mkv *.mov "
                                                                     "*.mpeg *.mpeg4 *.wmv *.flv )")));

    QFileInfo file_info(parameters.file_name.fileName());
    QString path(file_info.filePath());

    ui->pathLine->setText(path);
}

void MainWindow::put_path()
{
    if (QFile::exists(ui->pathLine->text()))
    {
        parameters.file_name.setFileName(ui->pathLine->text());
    }
}

void MainWindow::start()
{       
    if (!checkFileName())
        return;

    if (parameters.size.isEmpty())
    {
        set_size();
    }
    if (parameters.codec.isEmpty())
    {
        set_codec();
    }
    if (!parameters.frame_rate)
    {
        set_frame_rate();
    }
    if (!parameters.audio_rate)
    {
        set_audio_rate();
    }
    if (!parameters.video_bitrate)
    {
        set_video_bitrate();
    }
    if (!parameters.audio_bitrate)
    {
        set_audio_bitrate();
    }
    if (!parameters.frame_density)
    {
        set_frame_density();
    }

    cout << "\n     file name: " << parameters.file_name.fileName() << endl;
    cout << "          size: " << parameters.size.width() << "x" << parameters.size.height() << endl;
    cout << "         codec: " << parameters.codec << endl;
    cout << "    frame rate: " << parameters.frame_rate << endl;
    cout << "    audio rate: " << parameters.audio_rate << " Hz"<< endl;
    cout << " video bitrate: " << parameters.video_bitrate << " kb/s" << endl;
    cout << " audio bitrate: " << parameters.audio_bitrate << " kb/s" << endl;
    cout << " frame density: " << parameters.frame_density << endl;

    // Call method to send video file and parameters

}

void MainWindow::set_size()
{
    parameters.size = ui->sizeComboBox->itemData(ui->sizeComboBox->currentIndex()).toSize();
}

void MainWindow::set_codec()
{
    parameters.codec = ui->codecComboBox->itemData(ui->codecComboBox->currentIndex()).toString();
}

void MainWindow::pattern_setter(unsigned int &parameter, QComboBox *combobox)
{
    parameter = combobox->itemData(combobox->currentIndex()).toInt();
}

void MainWindow::set_frame_rate()
{
    pattern_setter(parameters.frame_rate, ui->frameRateComboBox);
}

void MainWindow::set_audio_rate()
{
    pattern_setter(parameters.audio_rate, ui->audioRateComboBox);
}

void MainWindow::set_video_bitrate()
{
    pattern_setter(parameters.video_bitrate, ui->videoBitrateComboBox);
}

void MainWindow::set_audio_bitrate()
{
    pattern_setter(parameters.audio_bitrate, ui->audioBitrateComboBox);
}

void MainWindow::set_frame_density()
{
    parameters.frame_density = ui->frameDensitySpinBox->value();
}
