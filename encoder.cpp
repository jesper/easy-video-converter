#include <QProcess>
#include <QDebug>

#include "encoder.h"

Encoder::Encoder(QFileInfo filename, QString encoderArguments, QString outputDirectory)
{
    m_filename = filename;
    m_encoderArguments = encoderArguments;
    m_outputDirectory = outputDirectory;
}

QFileInfo Encoder::getInputFilename()
{
    return m_filename;
}

QFileInfo Encoder::getOutputFilename()
{
    return QFileInfo(m_outputDirectory + "/" + m_filename.fileName());
}

int Encoder::getErrorCode()
{
    return m_errorCode;
}

void Encoder::run()
{
    QString args = "-i " + m_filename.absoluteFilePath().trimmed() + " " + m_encoderArguments + " \"" \
                   + m_outputDirectory +"/" + m_filename.fileName() + ".avi\"";
    //m_errorCode = QProcess::execute("ffmpeg", args.split(" "));
    sleep(2);
    m_errorCode = 0;
    emit finishedEncoding(this);
}
