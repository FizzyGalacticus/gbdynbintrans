/* CS 441 - System Architecture
 * Project #2 - gbdynbintrans - mainwindow.cpp
 * Bucky Frost & Dustin Dodson
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include <QDir>
#include "memorybank.h"
#include <QDebug>

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
    connect(ui->actionViewMemory, SIGNAL(triggered(bool)), this, SLOT(viewMemoryTriggered()));
    connect(this, SIGNAL(fileNameChanged(const QString)), this->_cpu, SLOT(loadROM(const QString)));

    this->_fileDialog->setDirectory(QDir().currentPath() + "gbdynbintrans/res/test_asm");
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

void MainWindow::viewMemoryTriggered() {
    this->_cpu->getMemory()->show();
}
