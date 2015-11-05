#pragma once

#include <QFile>
#include <QFileInfo>
#include <QString>

class mkvmerge_wrapper
{
public:

    mkvmerge_wrapper();
    ~mkvmerge_wrapper();

    QString split(const QString &file_name);
    void merge(QString &target_file_name, QDir &resource_dir);
    bool remove_dir(QDir &delete_dir);

private:

    static const QString mkvmerge_cmd_;
    static const QString mkvsplit_parameters_;
    static const QString mkvmerge_parameters_;
    static const QString mkvsplit_output_dir_suffix_;
    static const QString mkvmerge_mkv_suffix_;
    static const QString mkvmerge_split_;

    QString create_output_dir(const QFile &input_file);
};

