#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    m_encodingManager = new EncodingManager(this);

    connect(m_encodingManager, SIGNAL(finished()), this, SLOT(encoderFinished()));
    connect(m_encodingManager, SIGNAL(convertingFile(QString)), this, SLOT(addConvertingFile(QString)));
    connect(m_encodingManager, SIGNAL(completedFile(QString)), this, SLOT(addCompletedFile(QString)));

    connect(m_ui->pb_addFiles, SIGNAL(clicked()), this, SLOT(addFilesClicked()));
    connect(m_ui->pb_directory, SIGNAL(clicked()), this, SLOT(selectDirectoryClicked()));

    //TBD: Disable "start" button untill files are added and output dir/format are selected.
    connect(m_ui->pb_start, SIGNAL(clicked()), this, SLOT(startClicked()));
}

const QString MainWindow::takeTopInputFile()
{
    return m_ui->lw_files->takeItem(0)->text();
}

bool MainWindow::hasInputFiles()
{
    return m_ui->lw_files->count() != 0;
}

void MainWindow::addConvertingFile(QString file)
{
    m_ui->lw_converting->addItem(file);
}

void MainWindow::addCompletedFile(QString filename)
{
    //Find the item in the Converting list widget
    QList<QListWidgetItem *> items = m_ui->lw_converting->findItems(filename, Qt::MatchExactly);

    //Remove the item from the Converting list widget
    m_ui->lw_converting->takeItem(m_ui->lw_converting->row(items.first()));

    m_ui->lw_completed->addItem(filename);
}

void MainWindow::encoderFinished()
{
    m_ui->pb_start->setEnabled(true);
}

void MainWindow::startClicked()
{
    m_ui->pb_start->setEnabled(false);

    m_encodingManager->start();
}

void MainWindow::selectDirectoryClicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, QLatin1String("Select output directory"));

    //No Dir selected, no need to continue
    if (dir.isEmpty())
        return;

     m_ui->l_directory->setStyleSheet("");

     //TBD: Check that the directory is writable/etc
     m_ui->l_directory->setText(dir);
}

void MainWindow::addFilesClicked()
{
    QStringList filenames = QFileDialog::getOpenFileNames(this, QLatin1String("Select video files to convert"));

    //No files selected? Return
    if (filenames.length() == 0)
        return;

    //If there's files, then clear the list of the red dummy text
    if (m_ui->lw_files->styleSheet() != "")
    {
        m_ui->lw_files->setStyleSheet("");
        m_ui->lw_files->clear();

    }

    //TBD: Add checking for duplicates
    //TBD: Check for valid movie files
    m_ui->lw_files->addItems(filenames);
}

MainWindow::~MainWindow()
{
    delete m_ui;
}
