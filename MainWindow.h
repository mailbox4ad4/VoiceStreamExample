#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Spetch.h"
#include <QAudioOutput>
#include <QBuffer>

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


    QAudioOutput *_output;
    QIODevice *_buffer;

    Spetch *_spetch;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
