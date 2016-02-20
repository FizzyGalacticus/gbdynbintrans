#include "registerbank.h"
#include "ui_registerbank.h"

RegisterBank::RegisterBank(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterBank),
    _A(0), _B(0), _C(0), _D(0),
    _E(0), _H(0), _L(0), _PC(0),
    _SP(0)
{
    ui->setupUi(this);
}

RegisterBank::~RegisterBank()
{
    delete ui;
}

__int16 RegisterBank::combineRegisters(const __int8 & highReg, const __int8 & lowReg) const {
    __int16 combinedRegisters = highReg;
    combinedRegisters = (combinedRegisters << 8) & lowReg;
    return combinedRegisters;
}

const pair<__int8, __int8> RegisterBank::decomposeRegisters(const __int16 & reg) {
    return pair<__int8, __int8>((reg >> 8), ((reg << 8) >> 8));
}

int RegisterBank::getA() const {
	return this->_A;
}

void RegisterBank::setA(const int temp) {
	this->_A = temp;
}

int RegisterBank::getB() const {
    return this->_B;
}

void RegisterBank::setB(const int temp) {
	this->_B = temp;
}

int RegisterBank::getC() const {
	return this->_C;
}

void RegisterBank::setC(const int temp) {
	this->_C = temp;
}

int RegisterBank::getD() const {
	return this->_D;
}

void RegisterBank::setD(const int temp) {
	this->_D = temp;
}

int RegisterBank::getE() const {
	return this->_E;
}

void RegisterBank::setE(const int temp) {
	this->_E = temp;
}

int RegisterBank::getH() const {
	return this->_H;
}

void RegisterBank::setH(const int temp) {
	this->_H = temp;
}

int RegisterBank::getL() const {
	return this->_L;
}

void RegisterBank::setL(const int temp) {
	this->_L = temp;
}

int RegisterBank::getBC() const {
    return this->combineRegisters(this->getB(), this->getC());
}

void RegisterBank::setBC(const int temp) {
	pair<__int8, __int8> regs = decomposeRegisters((__int16)temp);
	this->setB(regs.first);
	this->setC(regs.second);
}

int RegisterBank::getDE() const {
	return this->combineRegisters(this->getD(), this->getE());
}

void RegisterBank::setDE(const int temp) {
	pair<__int8, __int8> regs = decomposeRegisters((__int16)temp);
	this->setD(regs.first);
	this->setE(regs.second);
}

int RegisterBank::getHL() const {
	return this->combineRegisters(this->getH(), this->getL());
}

void RegisterBank::setHL(const int temp) {
	pair<__int8, __int8> regs = decomposeRegisters((__int16)temp);
	this->setH(regs.first);
	this->setL(regs.second);
}

int RegisterBank::getPC() const {
	return this->_PC;
}

void RegisterBank::setPC(const int temp) {
	this->_PC = temp;
}

int RegisterBank::getSP() const {
	return this->_SP;
}

void RegisterBank::setSP(const int temp) {
	this->_SP = temp;
}
