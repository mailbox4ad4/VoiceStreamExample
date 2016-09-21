#ifndef SPETCH_H
#define SPETCH_H

#include <QObject>
#include <QAudioInput>
#include <QBuffer>

class Spetch : public QObject
{
    Q_OBJECT
public:
    explicit Spetch(QObject *parent = 0);
    ~Spetch();

private:

    QAudioInput *_audioInput;
    QBuffer *_buffer;


signals:
    void ready(const QByteArray &arr);

public slots:
};

#endif // SPETCH_H
