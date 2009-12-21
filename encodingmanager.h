#ifndef ENCODINGMANAGER_H
#define ENCODINGMANAGER_H

#include <QThread>
#include <QListWidget>
#include <QLabel>

#include "mainwindow.h"

class MainWindow;

class EncodingManager : public QThread
{
    Q_OBJECT

public:
    EncodingManager(MainWindow *ui);
    void run();

signals:
    void convertingFile(QString file);
    void completedFile(QString file);

private:
    MainWindow *m_ui;
};

#endif // ENCODINGMANAGER_H
