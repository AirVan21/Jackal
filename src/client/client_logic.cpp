#include "client_logic.h"

#include <QDir>
#include <QDebug>

//#include <QHostAddress>

client_logic::client_logic(QString &filename)
    : input_filename_(filename)
{
}

//QByteArray - chunk
//quint32_t

void client_logic::run()
{
    //quint32 file_size = get_file_size(input_filename_);
    //QVector<QPair<quint16, QHostAddress>> workes_address;
    mkvmerge_wrapper task_splitter;
    QString segment_dir_name = task_splitter.split(input_filename_);
    QDir segment_dir(segment_dir_name);
    segment_dir.setFilter(QDir::Files | QDir::NoSymLinks);

    QFileInfoList list_of_files = segment_dir.entryInfoList();

    for (QFileInfo &file_info : list_of_files)
    {
        QString coding_file = file_info.absoluteFilePath();
        encodeOn(coding_file);
    }
    QFile fileOut(this->input_filename_);
    QFileInfo file_info_out(fileOut);
    QString outputname = file_info_out.absolutePath() + QDir().separator() + file_info_out.baseName() + "o" + ".mkv";
    task_splitter.merge(outputname, segment_dir);

}

quint32 client_logic::get_file_size(QString &filepath) const
{
    QFile file(filepath);
    if (file.exists())
    {
        return file.size();
    } else
    {
        return 0;
    }
}

client_logic::~client_logic()
{
}

void client_logic::encodeOn(QString &filename)
{
    const QString ffmpeg_cmd_              = "ffmpeg";
    const QString ffmpeg_params_           = " -i %1 -vcodec h264 -r 25 -g 50 -b 500k -acodec mp3 -ar 44100 -ab 32k -s 1080x720 -y %2";

     QFile temp_file(filename);
     if (temp_file.open(QIODevice::ReadWrite))
     {
         QFile file(filename);
         QFileInfo file_info(file);
         QString cmd = ffmpeg_cmd_ + ffmpeg_params_.arg(filename, file_info.absolutePath() + QDir().separator() + file_info.baseName() + "o" + ".mkv");
         system(cmd.toStdString().c_str());
         qDebug() << cmd;
         QDir().remove(filename);
     }
}
