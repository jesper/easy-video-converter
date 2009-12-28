#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

#include "encodingmanager.h"

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
    QString getOutputDirectory();
    void addInputFiles(QStringList filenames);

public slots:
    void addConvertingFile(QString file);
    void moveFromConvertingToCompleted(QString file);

signals:
    void startClicked();
    void newInputFilesAdded(QStringList filenames);

private slots:
    void addFilesClicked();
    void selectDirectoryClicked();
    void startButtonClicked();

private:
    void updateStartButtonState();
    Ui::MainWindow *m_ui;
};

#endif // MAINWINDOW_H
