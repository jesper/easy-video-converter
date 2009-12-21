#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

#include "encodingmanager.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void addFilesClicked();
    void selectDirectoryClicked();
    void startClicked();
    void encoderFinished();
    void addConvertingFile(QListWidgetItem *item);
    void addCompletedFile(QListWidgetItem *item);

private:
    Ui::MainWindow *m_ui;
    EncodingManager *m_encodingManager;
};

#endif // MAINWINDOW_H
