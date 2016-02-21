#include "programcounter.h"
#include "ui_programcounter.h"
#include <QStyle>
#include <QDebug>

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
    emit this->programCounterHasChanged(this->getProgramCounter());
}

int ProgramCounter::getProgramCounter() const {
    return this->_programCounter;
}

void ProgramCounter::setProgramHex(QString hex) {
    this->_programHex = hex;

    QString temp = hex.mid(0,this->getProgramCounter()*2);
    temp += "<div class=\"active\">";
    temp += hex.mid(this->getProgramCounter()*2,2);
    temp += "</div>";
    temp += hex.mid(this->getProgramCounter()*2+2,-1);

    qDebug() << temp;

    this->ui->textEdit->setText(temp);
}
