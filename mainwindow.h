#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

#include "encodingmanager.h"
#include "misc.h"
#include "formatdelegate.h"
#include "format.h"

namespace Ui
{
    class MainWindow;
}

class EncodingManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool hasInputFiles();
    QString takeTopInputFile();
    QString getEncoderArguments();
    QString getOutputDirectory();
    void addInputFiles(QStringList filenames);
    ConsumptionLevel getConsumptionLevel();
    void addFormat(Format format);

public slots:
    void addConvertingFile(QString file);
    void moveFromConvertingToCompleted(QString file);

signals:
    void startClicked();
    void newInputFilesAdded(QStringList filenames);
    void consumptionLevelChanged();

private slots:
    void addFilesClicked();
    void selectDirectoryClicked();
    void startButtonClicked();
    void lowClicked();
    void mediumClicked();
    void maxClicked();

private:
    void updateStates();
    Ui::MainWindow *m_ui;
    FormatDelegate *m_formatDelegate;
};

#endif // MAINWINDOW_H
