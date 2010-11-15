#include <QProcess>
#include <QDebug>

#include "encoder.h"

Encoder::Encoder(QString filename, QString encoderArguments)
{
    m_filename = filename;
    m_encoderArguments = encoderArguments;
}

QString Encoder::getFilename()
{
    return m_filename;
}

int Encoder::getErrorCode()
{
    return m_errorCode;
}

void Encoder::run()
{
    //TBD - Use real output directory
    QString args = "-i " + m_filename.trimmed() + " " + m_encoderArguments + " " + m_filename.trimmed() + ".avi";
    m_errorCode = QProcess::execute("ffmpeg", args.split(" "));
    emit finishedEncoding(this);
}
