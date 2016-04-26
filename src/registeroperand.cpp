#include "registeroperand.h"
#include <utility>
using std::make_pair;

RegisterOperand::RegisterOperand(RegisterBank * regBank, QString registerName, QObject *parent) :
    Operand(parent),
    _regBank(regBank),
    _registerName(registerName),
    _getAlias(),
    _setAlias()
{
    /* Map register strings to corresponding getters */
    this->_getAlias.insert(make_pair<string, getPtr >("A", &RegisterBank::getA));
    this->_getAlias.insert(make_pair<string, getPtr >("B", &RegisterBank::getB));
    this->_getAlias.insert(make_pair<string, getPtr >("C", &RegisterBank::getC));
    this->_getAlias.insert(make_pair<string, getPtr >("D", &RegisterBank::getD));
    this->_getAlias.insert(make_pair<string, getPtr >("E", &RegisterBank::getE));
    this->_getAlias.insert(make_pair<string, getPtr >("H", &RegisterBank::getH));
    this->_getAlias.insert(make_pair<string, getPtr >("L", &RegisterBank::getL));
    this->_getAlias.insert(make_pair<string, getPtr >("BC", &RegisterBank::getBC));
    this->_getAlias.insert(make_pair<string, getPtr >("DE", &RegisterBank::getDE));
    this->_getAlias.insert(make_pair<string, getPtr >("HL", &RegisterBank::getHL));
    this->_getAlias.insert(make_pair<string, getPtr >("PC", &RegisterBank::getPC));
    this->_getAlias.insert(make_pair<string, getPtr >("SP", &RegisterBank::getSP));

    /* Map register strings to corresponding setters */
    this->_setAlias.insert(make_pair<string, setPtr >("A", &RegisterBank::setA));
    this->_setAlias.insert(make_pair<string, setPtr >("B", &RegisterBank::setB));
    this->_setAlias.insert(make_pair<string, setPtr >("C", &RegisterBank::setC));
    this->_setAlias.insert(make_pair<string, setPtr >("D", &RegisterBank::setD));
    this->_setAlias.insert(make_pair<string, setPtr >("E", &RegisterBank::setE));
    this->_setAlias.insert(make_pair<string, setPtr >("H", &RegisterBank::setH));
    this->_setAlias.insert(make_pair<string, setPtr >("L", &RegisterBank::setL));
    this->_setAlias.insert(make_pair<string, setPtr >("BC", &RegisterBank::setBC));
    this->_setAlias.insert(make_pair<string, setPtr >("DE", &RegisterBank::setDE));
    this->_setAlias.insert(make_pair<string, setPtr >("HL", &RegisterBank::setHL));
    this->_setAlias.insert(make_pair<string, setPtr >("PC", &RegisterBank::setPC));
    this->_setAlias.insert(make_pair<string, setPtr >("SP", &RegisterBank::setSP));
}

void RegisterOperand::setValue(const int val) {
    (this->_regBank->*(this->_setAlias.at(this->_registerName.toStdString())))(val);
}

int RegisterOperand::getVal() {
    return (this->_regBank->*(this->_getAlias.at(this->_registerName.toStdString())))();
}

QString RegisterOperand::getType() {
    return "REGISTER";
}

const QString RegisterOperand::getRegisterName() const{
    return this->_registerName;
}
