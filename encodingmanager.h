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

signals:
    void convertingFile(QListWidgetItem *file);
    void completedFile(QListWidgetItem *file);

private:
    QListWidget *m_files;
};

#endif // ENCODINGMANAGER_H
