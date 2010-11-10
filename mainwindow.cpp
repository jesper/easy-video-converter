#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>

//TBD - Make required fields UI more intuitive. Red text isn't enough
//TBD - Allow dragging of files into input files list

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    connect(m_ui->pb_addFiles, SIGNAL(clicked()), this, SLOT(addFilesClicked()));
    connect(m_ui->pb_directory, SIGNAL(clicked()), this, SLOT(selectDirectoryClicked()));

    connect(m_ui->pb_start, SIGNAL(clicked()), this, SLOT(startButtonClicked()));

    connect(m_ui->rb_low, SIGNAL(clicked()), this, SLOT(lowClicked()));
    connect(m_ui->rb_medium, SIGNAL(clicked()), this, SLOT(mediumClicked()));
    connect(m_ui->rb_max, SIGNAL(clicked()), this, SLOT(maxClicked()));

    updateStates();

    m_formatDelegate = new FormatDelegate(this);
    m_ui->cb_format->setItemDelegate(m_formatDelegate);
}

void MainWindow::addFormat(Format format)
{
    m_ui->cb_format->addItem(format.getName(), format.getArgs());
}

ConsumptionLevel MainWindow::getConsumptionLevel()
{
    if (m_ui->rb_low->isChecked())
        return Low;

    if (m_ui->rb_medium->isChecked())
        return Medium;

    if (m_ui->rb_max->isChecked())
        return Max;

    //Should never happen
    return Low;
}

void MainWindow::lowClicked()
{
    m_ui->rb_max->setChecked(false);
    m_ui->rb_medium->setChecked(false);

    emit consumptionLevelChanged();
}

void MainWindow::mediumClicked()
{
    m_ui->rb_max->setChecked(false);
    m_ui->rb_low->setChecked(false);

    emit consumptionLevelChanged();
}

void MainWindow::maxClicked()
{
    m_ui->rb_low->setChecked(false);
    m_ui->rb_medium->setChecked(false);

    emit consumptionLevelChanged();
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
    updateStates();
}

void MainWindow::moveFromConvertingToCompleted(QString filename)
{
    //Find the item in the Converting list widget
    QList<QListWidgetItem *> items = m_ui->lw_converting->findItems(filename, Qt::MatchExactly);

    //Remove the item from the Converting list widget
    m_ui->lw_converting->takeItem(m_ui->lw_converting->row(items.first()));

    m_ui->lw_completed->addItem(filename);

    updateStates();
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

    //TBD - Check that the directory is writable/etc
    m_ui->l_directory->setText(dir);

    updateStates();
}

QString MainWindow::getOutputDirectory()
{
    return m_ui->l_directory->text();
}

void MainWindow::updateStates()
{
    bool startEnabled = true;

    //No input files, disable
    if (m_ui->lw_files->count() == 0)
    {
        m_ui->pb_addFiles->setStyleSheet("color :red");
        startEnabled = false;
    }
    else
    {
        m_ui->pb_addFiles->setStyleSheet("");
    }

    //Files being converted, disable
    if (m_ui->lw_converting->count() != 0)
        startEnabled = false;

    //No output directory, disable
    if (m_ui->l_directory->text().isNull())
    {
        m_ui->pb_directory->setStyleSheet("color :red");
        startEnabled = false;
    }
    else
    {
        m_ui->pb_directory->setStyleSheet("");
    }

    m_ui->pb_start->setEnabled(startEnabled);
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
    updateStates();
}

MainWindow::~MainWindow()
{
    delete m_ui;
}
