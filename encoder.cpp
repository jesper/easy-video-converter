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
    m_errorcode = QProcess::execute("whoami");
    sleep(1);
    emit finishedEncoding(this);
}
