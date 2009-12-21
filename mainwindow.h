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

private slots:
    void addFilesClicked();
    void selectDirectoryClicked();
    void startClicked();
    void encoderFinished();
    void addConvertingFile(QString file);
    void addCompletedFile(QString file);

private:
    Ui::MainWindow *m_ui;
    EncodingManager *m_encodingManager;
};

#endif // MAINWINDOW_H
