#include "controller.h"

Controller::Controller()
{
    m_encodingManager = new EncodingManager(this);

    m_ui = new MainWindow();
    m_ui->show();    


    connect(m_encodingManager, SIGNAL(convertingFile(QString)), m_ui, SLOT(addConvertingFile(QString)));
    connect(m_encodingManager, SIGNAL(completedFile(QString)), m_ui, SLOT(addCompletedFile(QString)));
    connect(m_ui, SIGNAL(startClicked()), this, SLOT(startClicked()));
    connect(m_ui, SIGNAL(inputFilesAdded()), this, SLOT(inputFilesAdded()));
}

void Controller::inputFilesAdded()
{
    if (!m_encodingManager->isRunning())
        m_ui->setStartButtonEnabled(true);
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
