#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    connect(m_ui->pb_addFiles, SIGNAL(clicked()), this, SLOT(addFilesPressed()));
}

void MainWindow::addFilesPressed()
{
    addFiles(QFileDialog::getOpenFileNames(this, QLatin1String("Select video files to convert")));
}

void MainWindow::addFiles(QStringList filenames)
{
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
