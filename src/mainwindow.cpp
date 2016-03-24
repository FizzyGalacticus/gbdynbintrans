/* CS 441 - System Architecture
 * Project #2 - gbdynbintrans - mainwindow.cpp
 * Bucky Frost & Dustin Dodson
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include <QDir>
#include <fstream>
using std::ifstream;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _filename(""),
    _fileDialog(new QFileDialog),
    _cpu(new Cpu)
{
    ui->setupUi(this);
    ui->centralLayout->addWidget(this->_cpu);

    connect(ui->actionOpen,SIGNAL(triggered(bool)), this, SLOT(openFileDialogTriggered()));
    connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(exitTriggered()));
    connect(ui->actionAbout, SIGNAL(triggered(bool)), this, SLOT(aboutDialogTriggered()));
    connect(this, SIGNAL(fileNameChanged(QString)), this, SLOT(loadROM(QString)));

    this->_fileDialog->setDirectory(QDir().currentPath() + "../../res/test_asm");
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
    inFile.seekg(512);

    while(inFile.read((char *)&data,1)) {
        if((int)data < 16)
            programText += "0";
        programText += QString::number((int)data, 16);
        if(programText.contains("c32f027d"))
            break;
    }
    inFile.close();

    if(programText.size())
        this->_cpu->setProgramHex(programText);
    else
        this->_cpu->setProgramHex("Could not open " + filename + ". This has not yet been implemented.");
}
