#include "ffmpeg_wrapper.h"

#include <QDebug>
#include <QFileInfo>

const QString ffmpeg_wrapper::ffmpeg_tempfile_name_    = "temp.mkv";
const QString ffmpeg_wrapper::ffmpeg_cmd_              = "ffmpeg";
const QString ffmpeg_wrapper::ffmpeg_output_filename_  = "output.mkv";
const QString ffmpeg_wrapper::ffmpeg_params_           = " -i %1 -vcodec h264 -r 30 -g 35 -b 4M -s 1920x1080 -y %2";

//ffmpeg -i input.avi -vcodec h264 -threads 0 -r 30 -g 35 -b 3M -bt 1M -acodec mp3 -ar 44100 -ab 32k out.mp4

QByteArray& ffmpeg_wrapper::encode(QByteArray &data)
{
	QFile temp_file(ffmpeg_tempfile_name_);
	if (temp_file.open(QIODevice::WriteOnly))
	{
		temp_file.write(data);
		temp_file.close();
		QString cmd = ffmpeg_cmd_ + ffmpeg_params_.arg(ffmpeg_tempfile_name_, ffmpeg_output_filename_);
		system(cmd.toStdString().c_str());
		QFile output_file(ffmpeg_output_filename_);
		if (output_file.open(QIODevice::ReadOnly))
		{
			data = output_file.readAll();
		}
	}

	return data;
}
