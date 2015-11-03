#pragma once

#include <string>

#include <QString>
#include <QFile>
#include <QSize>

class task_parameters
{

public:

    QFile file_name;
    QString codec;
    QSize size;
    unsigned int frame_rate;
    unsigned int audio_rate;
    unsigned int frame_density;
    unsigned int video_bitrate;
    unsigned int audio_bitrate;

private:

    static const QString input_file_;        //
    static const QString codec_;             // h264
    static const QString size_;              // widthxheight
    static const QString frame_rate_;        // 25
    static const QString audio_rate_;        // 44100
    static const QString frame_density_;     // 50 (default = frame_rate)
    static const QString video_bitrate_;     // 800k
    static const QString audio_bitrate_;     // 32k

};

const QString task_parameters::input_file_    = "-i";
const QString task_parameters::codec_         = "-vcodec";
const QString task_parameters::frame_rate_    = "-r";
const QString task_parameters::audio_rate_    = "-ar";
const QString task_parameters::size_          = "-s";
const QString task_parameters::frame_density_ = "-g";
const QString task_parameters::video_bitrate_ = "-b";
const QString task_parameters::audio_bitrate_ = "-ab";
