#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _fileDialog(new QFileDialog),
    _filename("")
{
    ui->setupUi(this);

    connect(ui->actionOpen,SIGNAL(triggered(bool)),this, SLOT(openFileDialogTriggered()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* SLOTS */
void MainWindow::openFileDialogTriggered() {
    QString newFileName = this->_fileDialog->getOpenFileName(this, tr("Open ROM"), "", tr("GameBoy Files (*.gb)"));

    if(newFileName != this->_filename) {
        this->_filename = newFileName;
        emit this->fileNameChanged(this->_filename);
        qDebug() << this->_filename;
    }
}

void MainWindow::loadROM(QString filename) {

}
