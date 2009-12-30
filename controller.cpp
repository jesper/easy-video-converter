#include <QDebug>

#include "controller.h"

Controller::Controller()
{
    m_encodingManager = new EncodingManager(this);

    m_ui = new MainWindow();
    m_ui->show();    

    connect(m_encodingManager, SIGNAL(convertingFile(QString)), m_ui, SLOT(addConvertingFile(QString)));
    connect(m_encodingManager, SIGNAL(completedFile(QString)), m_ui, SLOT(moveFromConvertingToCompleted(QString)));

    connect(m_ui, SIGNAL(startClicked()), this, SLOT(startClicked()));
    connect(m_ui, SIGNAL(newInputFilesAdded(QStringList)), this, SLOT(newInputFilesAdded(QStringList)));
    connect(m_ui, SIGNAL(consumptionLevelChanged()), this, SLOT(consumptionLevelChanged()));
}

void Controller::consumptionLevelChanged()
{
    if (m_encodingManager->isRunning())
        m_encodingManager->dispatch();
}

ConsumptionLevel Controller::getConsumptionLevel()
{
    return m_ui->getConsumptionLevel();
}

void Controller::newInputFilesAdded(QStringList filenames)
{
    //TBD - Check for valid files
    m_ui->addInputFiles(filenames);

    if (m_encodingManager->isRunning())
        m_encodingManager->dispatch();
}

void Controller::startClicked()
{
    m_encodingManager->start();
}

QString Controller::takeTopInputFile()
{
    return m_ui->takeTopInputFile();
}

bool Controller::hasInputFiles()
{
    return m_ui->hasInputFiles();
}
