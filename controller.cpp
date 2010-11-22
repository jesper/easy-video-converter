#include <QDebug>

#include "controller.h"

Controller::Controller()
{
    m_encodingManager = new EncodingManager(this);

    m_ui = new MainWindow();

    populateFormats();

    m_ui->show();    

    qRegisterMetaType<QFileInfo>("QFileInfo");

    connect(m_encodingManager, SIGNAL(convertingFile(QFileInfo)), m_ui, SLOT(addConvertingFile(QFileInfo)));
    connect(m_encodingManager, SIGNAL(completedFile(QFileInfo)), m_ui, SLOT(moveFromConvertingToCompleted(QFileInfo)));

    connect(m_ui, SIGNAL(startClicked()), this, SLOT(startClicked()));
    connect(m_ui, SIGNAL(newInputFilesAdded(QStringList)), this, SLOT(newInputFilesAdded(QStringList)));
    connect(m_ui, SIGNAL(consumptionLevelChanged()), this, SLOT(consumptionLevelChanged()));
}

void Controller::populateFormats()
{
    // TBD - UNTESTED! Dunno how accurate these are - or if they even work
    m_ui->addFormat(Format("N900", "-vcodec libx264 -vpre hq -vpre ipod640 -b 800k -s #{osize[0]}x#{osize[1]} -acodec libmp3lame -ab 128k -ac 2"));
    m_ui->addFormat(Format("1080 HD Video", "-vcodec libxvid -b 18000k -acodec libmp3lame -ac 2 -ab 256k -deinterlace -s 1920x1080"));
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

QString Controller::getEncoderArguments()
{
    return m_ui->getEncoderArguments();
}

QString Controller::getOutputDirectory()
{
    return m_ui->getOutputDirectory();
}

QFileInfo Controller::takeTopInputFile()
{
    return m_ui->takeTopInputFile();
}

bool Controller::hasInputFiles()
{
    return m_ui->hasInputFiles();
}
