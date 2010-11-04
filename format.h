#ifndef FORMAT_H
#define FORMAT_H

#include <QString>

class Format
{
public:
    Format(QString name, QString args);
    QString getName();
    QString getArgs();

private:
    QString m_name;
    QString m_args;
};

#endif // FORMAT_H
