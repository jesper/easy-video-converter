#ifndef ENCODINGMANAGER_H
#define ENCODINGMANAGER_H

#include <QThread>
#include <QListWidget>

class EncodingManager : public QThread
{
    Q_OBJECT

public:
    EncodingManager(QListWidget *fileList);
    void run();

private:
    QListWidget *m_files;
};

#endif // ENCODINGMANAGER_H
