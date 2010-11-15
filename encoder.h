#ifndef ENCODER_H
#define ENCODER_H

#include <QThread>

class Encoder : public QThread
{
    Q_OBJECT

public:
    Encoder(QString filename, QString encoderArguments);
    void run();
    QString getFilename();
    int getErrorCode();

signals:
    void finishedEncoding(Encoder *encoder);

private:
    QString m_filename;
    QString m_encoderArguments;
    int m_errorCode;
};

#endif // ENCODER_H
