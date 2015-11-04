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
    ui->frameRateComboBox->addItem("25", QVariant(25));
    ui->frameRateComboBox->addItem("30", QVariant(30));
    ui->frameRateComboBox->addItem("50", QVariant(50));

    ui->sizeComboBox->addItem("1080x720", QVariant(QSize(1080, 720)));
    ui->sizeComboBox->addItem("1020x1000", QVariant(QSize(1020, 1000)));
    ui->sizeComboBox->addItem("720x480", QVariant(QSize(720, 480)));
    
    ui->audioRateComboBox->addItem("44100", QVariant(44100));
    ui->audioRateComboBox->addItem("47250", QVariant(47250));
    ui->audioRateComboBox->addItem("80000", QVariant(80000));
    
    ui->codecComboBox->addItem("h264", QVariant(QString("h264")));
    ui->codecComboBox->addItem("x264", QVariant(QString("x264")));
    
    ui->videoBitrateComboBox->addItem("800k", QVariant(800));
    ui->videoBitrateComboBox->addItem("1150k", QVariant(1150));
    ui->videoBitrateComboBox->addItem("2500k", QVariant(2500));

    ui->audioBitrateComboBox->addItem("256k", QVariant(256));
    ui->audioBitrateComboBox->addItem("400k", QVariant(400));
    ui->audioBitrateComboBox->addItem("1440k", QVariant(1440));
}

// проверка инициализации
bool MainWindow::checkFileName()
{
    if (parameters.file_name.fileName().isEmpty())
    {
        cout << "file is not choosen" << endl;
        return false;
    }
    else
    {
        QFileInfo checkFile(ui->pathLine->text());
        if (!(checkFile.exists() && checkFile.isFile()))
        {
            cout << "no file is found" << endl;
            return false;
        }
        else
        {
            QString ext = checkFile.suffix();
            // TODO use enum to siplify?
            if (!(ext == "mp4"   ||
                  ext == "mkv"   ||
                  ext == "mov"   ||
                  ext == "mpeg"  ||
                  ext == "mpeg4" ||
                  ext == "wmv"))
            {
                cout << "not valid file extension" << endl;
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
                                                                     "*.mpeg *.mpeg4 *.wmv)")));

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
    cout << "    audio rate: " << parameters.audio_rate << endl;
    cout << " video bitrate: " << parameters.video_bitrate << endl;
    cout << " audio bitrate: " << parameters.audio_bitrate << "k" << endl;
    cout << " frame density: " << parameters.frame_density << "k" << endl;

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
