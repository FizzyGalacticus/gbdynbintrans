#include "constantoperand.h"

ConstantOperand::ConstantOperand(const int val, QObject * parent) :
    Operand(parent),
    _value(val)
{

}

void ConstantOperand::setValue(const int val) {
    this->_value = val;
}

int ConstantOperand::getVal() {
    return this->_value;
}

QString ConstantOperand::getType() {
    return "CONSTANT";
}
