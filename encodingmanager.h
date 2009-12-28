#ifndef ENCODINGMANAGER_H
#define ENCODINGMANAGER_H

#include <QThread>
#include <QListWidget>
#include <QLabel>

#include "controller.h"
#include "encoder.h"

class Controller;

class EncodingManager : public QThread
{
    Q_OBJECT

public:
    EncodingManager(Controller *controller);
    void run();
    bool isRunning();
    void dispatch();

signals:
    void convertingFile(QString file);
    void completedFile(QString file);

private slots:
    void encoderFinished(Encoder *encoder);

private:
    void dispatchEncoder();

    Controller *m_controller;
    int m_runningThreads;
};

#endif // ENCODINGMANAGER_H
