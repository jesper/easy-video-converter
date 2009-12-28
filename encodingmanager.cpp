#include <QDebug>

#include "encodingmanager.h"

EncodingManager::EncodingManager(Controller *controller)
{
    m_controller = controller;
    m_runningThreads = 0;
}

void EncodingManager::dispatchEncoder()
{
    ++m_runningThreads;

    QString filename = m_controller->takeTopInputFile();

    emit convertingFile(filename);

    Encoder *encoder = new Encoder(filename);
    connect(encoder, SIGNAL(finishedEncoding(Encoder *)), this, SLOT(encoderFinished(Encoder *)));
    encoder->start();
}

void EncodingManager::encoderFinished(Encoder *encoder)
{
    --m_runningThreads;
    QString filename = encoder->getFilename();
    int errorcode = encoder->getErrorcode();

    delete encoder;

    qDebug() << "Encodingmanager finished encoder with" << filename << "and " << errorcode;

    emit completedFile(filename);

    if (m_controller->hasInputFiles())
        dispatchEncoder();
    else
        return; // All done!
}

bool EncodingManager::isRunning()
{
    return m_runningThreads != 0;
}

void EncodingManager::run()
{
    int threads = QThread::idealThreadCount();

    for (int i=0; (i < threads) && (m_controller->hasInputFiles()); ++i)
        dispatchEncoder();
}
