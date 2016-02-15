#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void openFileDialogTriggered();
    void loadROM(QString filename);

signals:
    void fileNameChanged(QString filename);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QFileDialog * _fileDialog;
    QString _filename;
};

#endif // MAINWINDOW_H
