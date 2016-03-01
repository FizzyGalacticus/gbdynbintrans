#include "cpu.h"
#include "ui_cpu.h"
#include <iostream>
using std::cout;
using std::endl;

Cpu::Cpu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Cpu),
    _programCounter(0),
    _regBank(new RegisterBank),
    _opDecoder(new OpcodeDecoder(":opcodes.json", this)),
    _retrievedConst(false),
    _retrievedConstWidth(false)
{
    ui->setupUi(this);
    ui->instructionLayout->addWidget(this->_opDecoder);
    ui->registerLayout->addWidget(this->_regBank);

    connect(this, SIGNAL(programHexChanged()), this, SLOT(resetStyle()));
    connect(this, SIGNAL(programCounterHasChanged(int)), this, SLOT(resetStyle()));
    connect(this->ui->nextInstructionButton, SIGNAL(pressed()), this, SLOT(nextInstructionButtonPressed()));
    connect(this->ui->programCounterLineEdit, SIGNAL(textChanged(QString)), this, SLOT(programCounterLineEditTextChanged(QString)));
    connect(this, SIGNAL(opcodeChanged(QString, RegisterBank *)), this->_opDecoder, SLOT(opcodeChanged(QString, RegisterBank *)));
    connect(this, SIGNAL(programCounterHasChanged(int)), this->_regBank, SLOT(programCounterChanged(int)));
    connect(this->_opDecoder, SIGNAL(instructionChanged(string,Operand&,Operand&)), this->_regBank, SLOT(instructionChanged(string,Operand&,Operand&)));
}

Cpu::~Cpu()
{
    delete ui;
}

void Cpu::setProgramCounter(const int pc) {
    if(pc > this->_programHex.size()/2-1)
        return;

    this->_programCounter = pc;

    emit this->programCounterHasChanged(this->getProgramCounter());
    emit this->opcodeChanged(this->getOpcode(), this->_regBank);
}

int Cpu::getProgramCounter() const {
    return this->_programCounter;
}

void Cpu::setProgramHex(QString hex) {
    this->_programHex = hex;
    this->setProgramCounter(0);

    emit this->programHexChanged();
}

const QString Cpu::getOpcode() {
    return this->_programHex.mid(this->getProgramCounter()*2,2);
}

void Cpu::resetStyle() {
    QString temp = "<div style=\"font-family: 'Lucida Console'; font-size: 16pt;\">";

    temp += formatProgramHex( this->_programHex.mid(0,this->getProgramCounter()*2) );
    temp += "<span class=\"active\" style=\"color: red;\">";
    temp += formatProgramHex( this->_programHex.mid(this->getProgramCounter()*2,2) );
    temp += "</span>";
    temp += formatProgramHex( this->_programHex.mid(this->getProgramCounter()*2+2,-1) );
    temp += "</div>";

    this->ui->textBrowser->setHtml(temp);
}

void Cpu::nextInstructionButtonPressed() {
    if(this->_retrievedConst) {
        if(this->_retrievedConstWidth) {
            this->setProgramCounter(this->getProgramCounter()+3);
            this->_retrievedConst = this->_retrievedConstWidth = false;
        }
        else {
            this->setProgramCounter(this->getProgramCounter()+2);
            this->_retrievedConst = this->_retrievedConstWidth = false;
        }
    }
    else this->setProgramCounter(this->getProgramCounter()+1);
}

void Cpu::programCounterLineEditTextChanged(QString newCounter) {
    int counterInteger = newCounter.toInt();
    if(counterInteger > this->_programHex.size()/2-1)
        return;

    this->setProgramCounter(counterInteger);
}

int Cpu::get8BitConst() {
    QString constHex = this->_programHex.mid(this->getProgramCounter()*2+2,2);
    int constInt = constHex.toInt();
    this->_retrievedConst = true;
    this->_retrievedConstWidth = false;
    return constInt;
}

int Cpu::get16BitConst() {
    QString constHex = this->_programHex.mid(this->getProgramCounter()*2+2,4);
    int constInt = constHex.toInt();
    this->_retrievedConst = true;
    this->_retrievedConstWidth = true;
    return constInt;
}

QString Cpu::formatProgramHex(const QString str) const {
    QString retStr = str;

    if(retStr.size() == 2) {
        retStr += " ";
        return retStr;
    }

    for(int i = 2; i < retStr.size(); i+=3)
        retStr.insert(i, " ");

    retStr += " ";

    return retStr;
}
