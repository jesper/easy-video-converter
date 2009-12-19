#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    connect(m_ui->pb_addFiles, SIGNAL(clicked()), this, SLOT(addFilesClicked()));
    connect(m_ui->pb_directory, SIGNAL(clicked()), this, SLOT(selectDirectoryClicked()));

    //TBD: Disable "start" button untill files are added and output dir/format are selected.
    connect(m_ui->pb_start, SIGNAL(clicked()), this, SLOT(startClicked()));

    m_encodingManager = new EncodingManager(m_ui->lw_files);
}

void MainWindow::startClicked()
{
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
