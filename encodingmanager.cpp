#include <QDebug>

#include "encodingmanager.h"

EncodingManager::EncodingManager(QListWidget *filelist)
{
    m_files = filelist;
}

void EncodingManager::run()
{
    while (m_files->count() != 0)
    {
        qDebug() << "Handling" << m_files->item(0)->text();
        QListWidgetItem *file = m_files->takeItem(0);
        emit convertingFile(file);
        sleep(2);
        emit completedFile(file);
    }
}
