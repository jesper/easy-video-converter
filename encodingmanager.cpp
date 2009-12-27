#include <QDebug>

#include "encodingmanager.h"

EncodingManager::EncodingManager(MainWindow *ui)
{
    m_ui = ui;
}

void EncodingManager::dispatchEncoder()
{
    QString filename = m_ui->takeTopInputFile();
    emit convertingFile(filename);
    Encoder *encoder = new Encoder(filename);
    connect(encoder, SIGNAL(finishedEncoding(Encoder *)), this, SLOT(encoderFinished(Encoder *)));
    encoder->start();
}

void EncodingManager::encoderFinished(Encoder *encoder)
{
    QString filename = encoder->getFilename();
    int errorcode = encoder->getErrorcode();

    delete encoder;

    qDebug() << "Encodingmanager finished encoder with" << filename << "and " << errorcode;

    emit completedFile(filename);

    if (m_ui->hasInputFiles())
        dispatchEncoder();
    else
        return;
}

void EncodingManager::run()
{
    int threads = QThread::idealThreadCount();

    for (int i=0; i < threads; ++i)
        dispatchEncoder();
}
