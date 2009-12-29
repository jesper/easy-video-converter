#include <QDebug>

#include "encodingmanager.h"

EncodingManager::EncodingManager(Controller *controller)
{
    m_controller = controller;
    m_runningThreads = 0;
}

void EncodingManager::dispatchEncoder()
{
    //No cores? Crap out...
    if (!isCoreAvailable() || !m_controller->hasInputFiles())
        return;

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

    dispatchEncoder();
}

bool EncodingManager::isRunning()
{
    return m_runningThreads != 0;
}

bool EncodingManager::isCoreAvailable()
{
    ConsumptionLevel level = m_controller->getConsumptionLevel();

    int availableCores = QThread::idealThreadCount();

    switch (level)
    {
            case Low:
                availableCores = 1;
                break;
            case Medium:
                availableCores = availableCores/2;
                break;
            case Max:
                break;
    }

    qDebug() << "Cores avail:" << availableCores;

    availableCores -= m_runningThreads;

    qDebug() << "Cores avail total:" << availableCores;

    return (availableCores > 0);
}

void EncodingManager::dispatch()
{
    while ((isCoreAvailable()) && (m_controller->hasInputFiles()))
        dispatchEncoder();
}

void EncodingManager::run()
{
    dispatch();
}
