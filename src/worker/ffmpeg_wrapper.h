#pragma once

#include <client/task_parameters.h>


class ffmpeg_wrapper
{
public:

    ffmpeg_wrapper();
    ~ffmpeg_wrapper();

    QByteArray& encode(QByteArray &data);

private:

    //task_parameters encode_task_;

    static const QString ffmpeg_tempfile_name_;
    static const QString ffmpeg_cmd_;
    static const QString ffmpeg_output_filename_;
    static const QString ffmpeg_params_;

};
