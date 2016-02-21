#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include "registerbank.h"
#include "programcounter.h"
#include "opcodedecoder.h"

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
    RegisterBank * _regBank;
    ProgramCounter * _pc;
    OpcodeDecoder * _opDecoder;
};

#endif // MAINWINDOW_H
