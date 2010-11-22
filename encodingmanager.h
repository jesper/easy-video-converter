#ifndef ENCODINGMANAGER_H
#define ENCODINGMANAGER_H

#include <QThread>
#include <QListWidget>
#include <QLabel>

#include "controller.h"
#include "encoder.h"
#include "misc.h"

class Controller;

class EncodingManager : public QThread
{
    Q_OBJECT

public:
    EncodingManager(Controller *controller);
    void run();
    bool isRunning();
    void dispatch();
    void setConsumptionLevel(ConsumptionLevel level);

signals:
    void convertingFile(QFileInfo file);
    void completedFile(QFileInfo file);

private slots:
    void encoderFinished(Encoder *encoder);

private:
    void dispatchEncoder();
    bool isCoreAvailable();

    Controller *m_controller;
    int m_runningThreads;
};

#endif // ENCODINGMANAGER_H
