#include "format.h"

Format::Format(QString name, QString args) :
        m_name(name), m_args(args)
{
}

QString Format::getName()
{
    return m_name;
}

QString Format::getArgs()
{
    return m_args;
}
