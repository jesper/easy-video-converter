#include <QDebug>

#include "encodingmanager.h"

EncodingManager::EncodingManager(MainWindow *ui)
{
    m_ui = ui;
}

void EncodingManager::run()
{

    while (m_ui->hasInputFiles())
    {
        const QString filename = m_ui->takeTopInputFile();
        qDebug() << "Handling" << filename;
        emit convertingFile(filename);
        sleep(2);
        emit completedFile(filename);
    }
}
