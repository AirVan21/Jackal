#pragma once
#include "mkvmerge_wrapper.h"

#include <QString>

class client_logic
{

public:
    client_logic(QString &filename);
    ~client_logic();

    void run();
    void encodeOn(QString &filename);

private:
    quint32 get_file_size(QString &filepath) const;

    // + Network Manager
    QString input_filename_;

};

