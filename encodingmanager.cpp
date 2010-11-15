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

    Encoder *encoder = new Encoder(filename,  m_controller->getEncoderArguments());
    connect(encoder, SIGNAL(finishedEncoding(Encoder *)), this, SLOT(encoderFinished(Encoder *)));
    encoder->start();
}

void EncodingManager::encoderFinished(Encoder *encoder)
{
    --m_runningThreads;
    QString filename = encoder->getFilename();
    int errorCode = encoder->getErrorCode();

    //TBD - Use the error code for something
    Q_ASSERT_X(errorCode == 0, "encoderFinished", "A ffmpeg instancer returned a non-zero error code");

    delete encoder;

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

    availableCores -= m_runningThreads;

    return (availableCores > 0);
}

void EncodingManager::dispatch()
{
    while (isCoreAvailable() && m_controller->hasInputFiles())
        dispatchEncoder();
}

void EncodingManager::run()
{
    dispatch();
}
