#include "mkvmerge_wrapper.h"

#include <iostream>
#include <QDir>
#include <QDebug>

const QString mkvmerge_wrapper::mkvmerge_cmd_               = "mkvmerge";
const QString mkvmerge_wrapper::mkvsplit_parameters_        = " -o -q %1 --split %2 %3";
const QString mkvmerge_wrapper::mkvmerge_parameters_        = " -o -q ";
const QString mkvmerge_wrapper::mkvsplit_output_dir_suffix_ = "_output";
const QString mkvmerge_wrapper::mkvmerge_mkv_suffix_        = ".mkv";

const QString mkvmerge_wrapper::mkvmerge_split_             = "2s";

mkvmerge_wrapper::mkvmerge_wrapper()
{
}

mkvmerge_wrapper::~mkvmerge_wrapper()
{
}

/*
 * Splits input_file on segments && put segments into directory
 *
 * @return Absolute path to directory, where segments are located
 */
QString mkvmerge_wrapper::split(const QString &file_name)
{
    QFile input_file(file_name);

    if (input_file.exists())
    {
        QFileInfo file_info(input_file.fileName());
        QString output_dir_name = create_output_dir(input_file);

        QString output_file = output_dir_name + QDir().separator() + file_info.baseName()
                + mkvsplit_output_dir_suffix_ + mkvmerge_mkv_suffix_;
        // Assemble split command
        QString cmd = mkvmerge_cmd_ + mkvsplit_parameters_.arg(output_file, mkvmerge_split_, file_info.absoluteFilePath());
        // Run splitting
        system(cmd.toStdString().c_str());

        return output_dir_name;
    }

    return "";
}

void mkvmerge_wrapper::merge(QString &target_file_name, QDir &resource_dir)
{
    QFile target_file(target_file_name);
    QFileInfo target_file_info(target_file);
    resource_dir.setFilter(QDir::Files | QDir::NoSymLinks);

    QFileInfoList list_of_files = resource_dir.entryInfoList();

    // Assemble merge command
    QString first_segment_name = list_of_files.at(0).absoluteFilePath();
    QString cmd = mkvmerge_cmd_+ mkvmerge_parameters_ + target_file_info.absoluteFilePath() +
            " " + first_segment_name;
    for (int i = 1; i < list_of_files.size(); ++i)
    {
        cmd += " +" + list_of_files.at(i).absoluteFilePath();
    }
    // Run splitting
    system(cmd.toStdString().c_str());
    // Removes folder
    remove_dir(resource_dir);
}

QString mkvmerge_wrapper::create_output_dir(const QFile &input_file)
{
    QFileInfo file_info(input_file.fileName());
    QDir file_dir = file_info.absoluteDir();
    QString file_base_name = file_info.baseName();

    QString output_dir_name = file_dir.absolutePath() + QDir().separator() + file_base_name + "_output";
    if (!QDir(output_dir_name).exists())
    {
        QDir().mkdir(output_dir_name);
    }

    return output_dir_name;
}

/*
 * @return true  if successful
 *         false not (directory must be empty )
 */
bool mkvmerge_wrapper::remove_dir(QDir &delete_dir)
{
    QFileInfoList list_of_files = delete_dir.entryInfoList();
    for (QFileInfo &file_in_dir : list_of_files)
    {
        QDir().remove(file_in_dir.absoluteFilePath());
    }

    return QDir().rmdir(delete_dir.absolutePath());
}
