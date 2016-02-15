#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _filename(""),
    _fileDialog(new QFileDialog)
{
    ui->setupUi(this);

    connect(ui->actionOpen,SIGNAL(triggered(bool)),this, SLOT(openFileDialogTriggered()));
    connect(this, SIGNAL(fileNameChanged(QString)), this, SLOT(loadROM(QString)));
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
//    OPEN FILE
//    READ BYTE FROM FILE
//    CONVERT BYTE TO HEX
//    ADD HEX TO QSTRING
//    SET QSTRING TO TEXTEDIT TEXT
    this->ui->programCounterTextEdit->setText("Could not open " + filename + ". This has not yet been implemented.");
}
