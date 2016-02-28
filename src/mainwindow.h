#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include "cpu.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void openFileDialogTriggered();
    void exitTriggered();
    void aboutDialogTriggered();
    void loadROM(QString filename);

signals:
    void fileNameChanged(QString filename);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QString _filename;
    QFileDialog * _fileDialog;
    Cpu * _cpu;
};

#endif // MAINWINDOW_H
