#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

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
    void addFilesPressed();
    void selectDirectoryPressed();

private:
    Ui::MainWindow *m_ui;
};

#endif // MAINWINDOW_H
