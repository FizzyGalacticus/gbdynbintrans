/* CS 441 - System Architecture
 * Project #2 - gbdynbintrans - mainwindow.h
 * Bucky Frost & Dustin Dodson
 *
 * This class, as the name suggests, acts as
 * the main window for the application. Its
 * sole purpose is to allow the user to
 * choose a ROM file, and display the CPU
 * operations as they happen.
 */

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

signals:
    void fileNameChanged(const QString filename);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void viewMemoryTriggered();

private:
    Ui::MainWindow *ui;

    QString _filename;
    QFileDialog * _fileDialog;
    Cpu * _cpu;
};

#endif // MAINWINDOW_H
