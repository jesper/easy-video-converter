#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "mainwindow.h"
#include "encodingmanager.h"
#include "misc.h"
#include "format.h"

class EncodingManager;
class MainWindow;

class Controller : public QObject
{
    Q_OBJECT

public:
    Controller();
    QString takeTopInputFile();
    QString getEncoderArguments();
    bool hasInputFiles();
    ConsumptionLevel getConsumptionLevel();

private slots:
    void startClicked();
    void newInputFilesAdded(QStringList filenames);
    void consumptionLevelChanged();

private:
    void populateFormats();

    MainWindow *m_ui;
    EncodingManager *m_encodingManager;


};

#endif // CONTROLLER_H
