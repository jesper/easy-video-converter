#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    connect(m_ui->pb_addFiles, SIGNAL(clicked()), this, SLOT(addFilesClicked()));
    connect(m_ui->pb_directory, SIGNAL(clicked()), this, SLOT(selectDirectoryClicked()));

    //TBD: Disable "start" button untill files are added and output dir/format are selected.
    connect(m_ui->pb_start, SIGNAL(clicked()), this, SLOT(startButtonClicked()));
}

QString MainWindow::takeTopInputFile()
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
    updateStartButtonState();
}

void MainWindow::moveFromConvertingToCompleted(QString filename)
{
    //Find the item in the Converting list widget
    QList<QListWidgetItem *> items = m_ui->lw_converting->findItems(filename, Qt::MatchExactly);

    //Remove the item from the Converting list widget
    m_ui->lw_converting->takeItem(m_ui->lw_converting->row(items.first()));

    m_ui->lw_completed->addItem(filename);

    updateStartButtonState();
}

void MainWindow::startButtonClicked()
{
    emit startClicked();
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

     updateStartButtonState();
}

QString MainWindow::getOutputDirectory()
{
    return m_ui->l_directory->text();
}

void MainWindow::updateStartButtonState()
{
    bool enabled = true;

    //No input files, disable
    if (m_ui->lw_files->count() == 0)
        enabled = false;

    //Files being converted, disable
    if (m_ui->lw_converting->count() != 0)
        enabled = false;

    //No output directory, disable
    if (m_ui->l_directory->text().isNull())
        enabled = false;

    m_ui->pb_start->setEnabled(enabled);
}

void MainWindow::addFilesClicked()
{
    QStringList filenames = QFileDialog::getOpenFileNames(this, QLatin1String("Select video files to convert"));

    //No files selected? Return
    if (filenames.length() == 0)
        return;

    //TBB - Add checking for duplicates

    emit newInputFilesAdded(filenames);
}

void MainWindow::addInputFiles(QStringList filenames)
{
    m_ui->lw_files->addItems(filenames);
    updateStartButtonState();
}

MainWindow::~MainWindow()
{
    delete m_ui;
}
