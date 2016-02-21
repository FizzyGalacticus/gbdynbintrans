#include "programcounter.h"
#include "ui_programcounter.h"
#include <iostream>
using std::cout;
using std::endl;

ProgramCounter::ProgramCounter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgramCounter),
    _programCounter(0)
{
    ui->setupUi(this);
    connect(this, SIGNAL(programHexChanged()), this, SLOT(resetStyle()));
    connect(this, SIGNAL(programCounterHasChanged(int)), this, SLOT(resetStyle()));
    connect(this->ui->nextInstructionButton, SIGNAL(pressed()), this, SLOT(nextInstructionButtonPressed()));
}

ProgramCounter::~ProgramCounter()
{
    delete ui;
}

void ProgramCounter::setProgramCounter(const int pc) {
    if(pc > this->_programHex.size()/2-1)
        return;

    this->_programCounter = pc;

    emit this->programCounterHasChanged(this->getProgramCounter());
}

int ProgramCounter::getProgramCounter() const {
    return this->_programCounter;
}

void ProgramCounter::setProgramHex(QString hex) {
    this->_programHex = hex;
    this->setProgramCounter(4);

    emit this->programHexChanged();
}

const QString ProgramCounter::getOpcode() {
    return this->_programHex.mid(this->getProgramCounter()*2,2);
}

void ProgramCounter::resetStyle() {
    QString temp = "<div style=\"font-family: 'Lucida Console'; font-size: 16pt;\">";

    temp += formatProgramHex( this->_programHex.mid(0,this->getProgramCounter()*2) );
    temp += "<span class=\"active\" style=\"color: red;\">";
    temp += formatProgramHex( this->_programHex.mid(this->getProgramCounter()*2,2) );
    temp += "</span>";
    temp += formatProgramHex( this->_programHex.mid(this->getProgramCounter()*2+2,-1) );
    temp += "</div>";

    this->ui->textBrowser->setHtml(temp);
}

void ProgramCounter::nextInstructionButtonPressed() {
    this->setProgramCounter(this->getProgramCounter()+1);
}

QString ProgramCounter::formatProgramHex(const QString str) const {
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
