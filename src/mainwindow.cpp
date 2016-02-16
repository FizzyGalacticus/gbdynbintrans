#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include <fstream>
using std::ifstream;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _filename(""),
    _fileDialog(new QFileDialog)
{
    ui->setupUi(this);

    connect(ui->actionOpen,SIGNAL(triggered(bool)), this, SLOT(openFileDialogTriggered()));
    connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(exitTriggered()));
    connect(ui->actionAbout, SIGNAL(triggered(bool)), this, SLOT(aboutDialogTriggered()));
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
    }
}

void MainWindow::exitTriggered() {
    this->close();
}

void MainWindow::aboutDialogTriggered() {
    AboutDialog * dialog = new AboutDialog(this);
    dialog->show();
}

void MainWindow::loadROM(QString filename) {
    unsigned char data;
    QString programText = "";

    ifstream inFile(filename.toStdString().c_str(), std::ios::binary);
    inFile.seekg(900);

    while(inFile >> data) programText += QString::number((int)data, 16);
    inFile.close();

    if(programText.size())
        this->ui->programCounterTextEdit->setText(programText);
    else
        this->ui->programCounterTextEdit->setText("Could not open " + filename + ". This has not yet been implemented.");
}
