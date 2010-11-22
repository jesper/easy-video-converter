#ifndef ENCODER_H
#define ENCODER_H

#include <QFileInfo>
#include <QThread>

class Encoder : public QThread
{
    Q_OBJECT

public:
    Encoder(QFileInfo filename, QString encoderArguments, QString outputDirectory);
    void run();
    QFileInfo getInputFilename();
    QFileInfo getOutputFilename();
    int getErrorCode();

signals:
    void finishedEncoding(Encoder *encoder);

private:
    QFileInfo m_filename;
    QString m_encoderArguments;
    QString m_outputDirectory;
    int m_errorCode;
};

#endif // ENCODER_H
