#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include "task_parameters.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    task_parameters parameters;

    // Fills comboboxes with dates;
    void init_comboboxes();

private slots:
    // Opens video file
    void open();

    // Starts file coding
    void start();

    void set_codec();

//    void set_size();

    // Common interface for similar methods
    void pattern_setter(unsigned int parameter, QComboBox *combobox);

    // Sets fields if ComboBox item selected
    void set_frame_rate();

    void set_audio_rate();

    void set_frame_density();

    void set_video_bitrate();

    void set_audio_bitrate();

};

#endif // MAINWINDOW_H
