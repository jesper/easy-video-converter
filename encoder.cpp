#include <QProcess>
#include <QDebug>

#include "encoder.h"

Encoder::Encoder(QString filename, QString encoderArguments, QString outputDirectory)
{
    m_filename = filename;
    m_encoderArguments = encoderArguments;
    m_outputDirectory = outputDirectory;
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
    QString args = "-i " + m_filename.trimmed() + " " + m_encoderArguments + " \"" \
                   + m_outputDirectory +"/" + m_filename.trimmed() + ".avi\"";
    //m_errorCode = QProcess::execute("ffmpeg", args.split(" "));
    sleep(2);
    m_errorCode = 0;
    emit finishedEncoding(this);
}
