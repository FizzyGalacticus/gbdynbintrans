#include "programcounter.h"
#include "ui_programcounter.h"
#include <QStyle>

ProgramCounter::ProgramCounter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgramCounter),
    _programCounter(0)
{
    ui->setupUi(this);
    ui->textEdit->setStyleSheet(".active {background-color: black; color: white;}");
}

ProgramCounter::~ProgramCounter()
{
    delete ui;
}

void ProgramCounter::setProgramCounter(const int pc) {
    this->_programCounter = pc;
}

int ProgramCounter::getProgramCounter() const {
    return this->_programCounter;
}

void ProgramCounter::setText(QString text) {

}

void ProgramCounter::programCounterHasChanged(const int pc) {
    this->setProgramCounter(pc);
}
