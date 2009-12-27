#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "mainwindow.h"
#include "encodingmanager.h"

class EncodingManager;
class MainWindow;

class Controller : public QObject
{
    Q_OBJECT

public:
    Controller();
    QString takeTopInputFile();
    bool hasInputFiles();

private slots:
    void startClicked();
    void inputFilesAdded();

private:
    MainWindow *m_ui;
    EncodingManager *m_encodingManager;


};

#endif // CONTROLLER_H
