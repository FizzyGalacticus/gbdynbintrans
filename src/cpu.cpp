/* CS 441 - System Architecture
 * Project #2 - gbdynbintrans - cpu.cpp
 * Bucky Frost & Dustin Dodson
 */

#include "cpu.h"
#include "ui_cpu.h"
#include <chrono>
#include <fstream>
using std::ifstream;
#include <QDebug>

Cpu::Cpu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Cpu),
    _isRunning(false),
    _regBank(new RegisterBank),
    _memory(new MemoryBank),
    _opDecoder(new OpcodeDecoder(this->_regBank, this->_memory, this)),
    _retrievedConst(false),
    _retrievedConstWidth(false),
    _mode(false)
{
    ui->setupUi(this);
    ui->instructionLayout->addWidget(this->_opDecoder);
    ui->registerLayout->addWidget(this->_regBank);

    connect(this->_regBank, SIGNAL(programCounterChanged(int)), this, SLOT(programCounterChanged(int)));
    connect(this, SIGNAL(opcodeChanged(QString)), this->_opDecoder, SLOT(opcodeChanged(QString)));
    connect(this->ui->runButton, SIGNAL(pressed()), this, SLOT(runThread()));
    connect(this->ui->pauseButton, SIGNAL(pressed()), this, SLOT(pause()));
    connect(this->ui->nextInstructionButton, SIGNAL(pressed()), this, SLOT(nextInstructionButtonPressed()));
    connect(this->ui->programCounterLineEdit, SIGNAL(textChanged(QString)), this, SLOT(programCounterLineEditTextChanged(QString)));
    connect(this, SIGNAL(opcodeChanged(QString, RegisterBank *)), this->_opDecoder, SLOT(opcodeChanged(QString, RegisterBank *)));
    connect(this, SIGNAL(programCounterHasChanged(int)), this->_regBank, SLOT(programCounterChanged(int)));
    connect(this->_opDecoder, SIGNAL(instructionChanged(string,Operand&,Operand&)), this->_regBank, SLOT(instructionChanged(string,Operand&,Operand&)));
    connect(this->_regBank, SIGNAL(jumpTriggered(int)), this, SLOT(jumpTriggered(int)));
}

Cpu::~Cpu()
{
    this->pause();

    delete ui;
}

void Cpu::loadROM(const QString filename) {
    uint8_t data;

    ifstream inFile(filename.toStdString().c_str(), std::ios::binary);
    inFile.seekg(500);

    while(inFile.read((char *)&data,1) && int(inFile.tellg()) < 1024) {
        this->_memory->setByte(int(inFile.tellg()), data);
    }
    inFile.close();

    this->formatProgramHex();
}

void Cpu::programCounterChanged(const int programCounter) {
    this->formatProgramHex();

    QString opCode = QString::number(this->_memory->getByte(programCounter), 16);

    if(opCode.size() < 2)
        opCode = "0" + opCode;

    emit this->opcodeChanged(opCode);
}

void Cpu::nextInstructionButtonPressed() {
    if(this->_retrievedConst) {
        if(this->_retrievedConstWidth) {
            this->_retrievedConst = this->_retrievedConstWidth = false;
            this->_regBank->setPC(this->_regBank->getPC()+3);
        }
        else {
            this->_retrievedConst = this->_retrievedConstWidth = false;
            this->_regBank->setPC(this->_regBank->getPC()+2);
        }
    }
    else this->_regBank->setPC(this->_regBank->getPC()+1);
}

void Cpu::programCounterLineEditTextChanged(QString newCounter) {
    int counterInteger = newCounter.toInt();
    if(counterInteger > QString("7fff").toInt(NULL, 16))
        return;

    this->_regBank->setPC(counterInteger);
}

void Cpu::run() {
    this->_isRunning = true;

    while(this->_isRunning) {
        this->nextInstructionButtonPressed();
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}

void Cpu::pause() {
    if(this->_isRunning) {
        this->_isRunning = false;
        this->_runningThread.join();
    }
}

void Cpu::runThread() {
    if(!this->_isRunning)
        this->_runningThread = std::thread(&Cpu::run, this);
}

/*
 * This function pulls a 8-bit integer from the binary
 */
int Cpu::get8BitConst() {
    int constInt = this->_memory->getByte(this->_regBank->getPC()+1);
    this->_retrievedConst = true;
    this->_retrievedConstWidth = false;
    return constInt;
}

/*
 * This function pulls a 16-bit integer from the binary
 */
int Cpu::get16BitConst() {
    int constInt = this->_memory->getWord(this->_regBank->getPC()+1);
    this->_retrievedConst = true;
    this->_retrievedConstWidth = true;
    return constInt;
}

bool Cpu::getMode() {
    return this->_mode;
}

void Cpu::setMode(bool mode) {
    this->_mode = mode;
}

MemoryBank * Cpu::getMemory() {
    return this->_memory;
}

void Cpu::jumpTriggered(const int position) {
    this->_retrievedConst = this->_retrievedConstWidth = false;
    this->_regBank->setPC(position);
}

void Cpu::formatProgramHex() const {
    QString hexStr = "<div style=\"font-family: 'Lucida Console'; font-size: 16pt;\">";

    for(int i = 512; i < 0x7FFF; i++) {
        QString tempStr = QString::number(this->_memory->getByte(i), 16);
        if(tempStr.size() < 2) tempStr = "0" + tempStr;

        if(i == this->_regBank->getPC()) {
            hexStr += "<span class=\"active\" style=\"color: red;\">";
            hexStr += tempStr;
            hexStr += "</span> ";
            continue;
        }

        hexStr += (tempStr + " ");
    }

    hexStr += "</div>";

    this->ui->textBrowser->setHtml(hexStr);
}
