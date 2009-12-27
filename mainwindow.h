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
    void setStartButtonEnabled(bool enabled);

public slots:
    void addConvertingFile(QString file);
    void addCompletedFile(QString file);

signals:
    void startClicked();
    void inputFilesAdded();

private slots:
    void addFilesClicked();
    void selectDirectoryClicked();
    void startButtonClicked();

private:
    Ui::MainWindow *m_ui;
};

#endif // MAINWINDOW_H
