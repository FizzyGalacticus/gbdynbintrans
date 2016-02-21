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
    _regBank(new RegisterBank),
    _pc(new ProgramCounter)
{
    ui->setupUi(this);
    ui->registerLayout->addWidget(this->_regBank);
    ui->programCounterLayout->addWidget(this->_pc);

    connect(ui->actionOpen,SIGNAL(triggered(bool)), this, SLOT(openFileDialogTriggered()));
    connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(exitTriggered()));
    connect(ui->actionAbout, SIGNAL(triggered(bool)), this, SLOT(aboutDialogTriggered()));
    connect(this, SIGNAL(fileNameChanged(QString)), this, SLOT(loadROM(QString)));
    connect(this->_pc, SIGNAL(programCounterHasChanged(int)), this->_regBank, SLOT(programCounterChanged(int)));

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
    inFile.seekg(900);

    while(inFile >> data) {
        if((int)data < 16)
            programText += "0";
        programText += QString::number((int)data, 16);
        if(programText.contains("ffffffff"))
            break;
    }
    inFile.close();

    if(programText.size())
        this->_pc->setProgramHex(programText);
    else
        this->_pc->setProgramHex("Could not open " + filename + ". This has not yet been implemented.");
}
