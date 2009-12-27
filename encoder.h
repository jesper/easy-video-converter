#ifndef ENCODER_H
#define ENCODER_H

#include <QThread>

class Encoder : public QThread
{
    Q_OBJECT

public:
    Encoder(QString filename);
    void run();
    QString getFilename();
    int getErrorcode();

signals:
    void finishedEncoding(Encoder *encoder);

private:
    QString m_filename;
    int m_errorcode;
};

#endif // ENCODER_H
