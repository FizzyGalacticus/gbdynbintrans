#include "operand.h"

Operand::Operand(RegisterBank * regBank, string reg, QObject *parent)
    : QObject(parent),
    _regBank(regBank),
    _registerName(reg)
{
//    this->_regVal = this->_regBank.getRegisterAccessor(this->_registerName);
}

Operand::Operand(const int constantInt, QObject *parent)
    : QObject(parent),
      _constVal(constantInt),
      _registerName("")
{
    this->_regBank = NULL;
}

int Operand::getVal() const {
    if(this->_regBank)
        return (this->_regBank->*(this->_regBank->getRegisterAccessor(this->_registerName)))();

    return this->_constVal;
}

const string Operand::getRegisterName() {
    return this->_registerName;
}
