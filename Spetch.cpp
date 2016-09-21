#include "Spetch.h"
#include <QDebug>

Spetch::Spetch(QObject *parent) : QObject(parent)
{
    QAudioFormat format;
    format.setSampleRate(48000);
    format.setChannelCount(1);
    format.setSampleSize(8);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

    foreach(const QAudioDeviceInfo &deviceInfo, QAudioDeviceInfo::availableDevices(QAudio::AudioInput))
      qDebug() << "Device name: " << deviceInfo.deviceName();

    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
    if (!info.isFormatSupported(format)) {
        qDebug() << "Not suported format!";
    }
    _audioInput = new QAudioInput(format, this);
    _buffer = new QBuffer(this);
    _buffer->open(QBuffer::ReadWrite);

    connect(_buffer, &QBuffer::readyRead, [this](){
        emit ready(_buffer->buffer());
        _buffer->reset();
    });

    _audioInput->start(_buffer);

}

Spetch::~Spetch()
{
    _audioInput->stop();
    _audioInput->deleteLater();
}
