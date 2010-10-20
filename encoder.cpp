#include <QProcess>
#include <QDebug>

#include "encoder.h"

Encoder::Encoder(QString filename)
{
    m_filename = filename;
}

QString Encoder::getFilename()
{
    return m_filename;
}

int Encoder::getErrorcode()
{
    return m_errorcode;
}

void Encoder::run()
{
    QString argstring = "-i " + m_filename.trimmed() + " -vcodec libxvid -b 18000k -acodec libmp3lame -ac 2 -ab 256k -deinterlace -s 1920x1080 " + m_filename.trimmed() + ".avi";

    //m_errorcode = QProcess::execute("ffmpeg", argstring.split(" "));
    m_errorcode = 0;
    sleep(2);
    emit finishedEncoding(this);
}
