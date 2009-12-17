#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    connect(m_ui->pb_addFiles, SIGNAL(clicked()), this, SLOT(addFilesPressed()));

    //Unbold and set the size of the font in the list widget.
    QFont listFont = m_ui->lw_files->font();
    listFont.setBold(false);
    listFont.setPointSize(9);
    m_ui->lw_files->setFont(listFont);
}

void MainWindow::addFilesPressed()
{
    addFiles(QFileDialog::getOpenFileNames(this, QLatin1String("Select video files to convert")));
}

void MainWindow::addFiles(QStringList filenames)
{
    //TBD: Add checking for duplicates
    //TBD: Check for valid movie files
    m_ui->lw_files->addItems(filenames);
}

MainWindow::~MainWindow()
{
    delete m_ui;
}
