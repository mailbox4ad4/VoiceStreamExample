#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _spetch = new Spetch(this);

    QAudioFormat format;
   // Set up the format, eg.
   format.setSampleRate(48000);
   format.setChannelCount(1);
   format.setSampleSize(8);
   format.setCodec("audio/pcm");
   format.setByteOrder(QAudioFormat::LittleEndian);
   format.setSampleType(QAudioFormat::UnSignedInt);

   foreach(const QAudioDeviceInfo &deviceInfo, QAudioDeviceInfo::availableDevices(QAudio::AudioOutput))
     qDebug() << "Device name: " << deviceInfo.deviceName();

   QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
   if (!info.isFormatSupported(format)) {
       qWarning() << "Raw audio format not supported by backend, cannot play audio.";
       return;
   }
   qDebug() << QAudioDeviceInfo::defaultOutputDevice().deviceName() << QAudioDeviceInfo::defaultOutputDevice().supportedSampleRates();

    _output = new QAudioOutput(format, this);
    _buffer = _output->start();

    connect(_spetch, &Spetch::ready, [this](const QByteArray &arr){
        ui->lineEdit->setText(arr.toHex());
        //qDebug() << arr;
        _buffer->reset();
        _buffer->seek(0);
        _buffer->write(arr);
        //_buffer->
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
