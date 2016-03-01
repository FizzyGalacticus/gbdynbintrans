#include "registerbank.h"
#include "ui_registerbank.h"
#include <utility>
using std::pair;
using std::make_pair;

RegisterBank::RegisterBank(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterBank),
    _getAlias(),
    _setAlias(),
    _functionAlias(),
    _A(0), _B(0), _C(0),
    _D(0), _E(0), _H(0),
    _L(0), _flags(0), _PC(0),
    _SP(0)
{
    ui->setupUi(this);
    connect(this, SIGNAL(valuesChanged()), this, SLOT(registerValuesHaveChanged()));

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

    /*Map strings to RegisterBank function pointers*/
    this->_functionAlias.insert(make_pair<string, fnPtr>("ld", &RegisterBank::ld));
    this->_functionAlias.insert(make_pair<string, fnPtr>("add", &RegisterBank::add));
    this->_functionAlias.insert(make_pair<string, fnPtr>("sub", &RegisterBank::sub));

    emit this->valuesChanged();
}

RegisterBank::~RegisterBank()
{
    delete ui;
}

__int16 RegisterBank::combineRegisters(const __int8 & highReg, const __int8 & lowReg) const {
    __int16 combinedRegisters = highReg;
    combinedRegisters = (combinedRegisters << 8) | lowReg;
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
	emit this->valuesChanged();
}

int RegisterBank::getB() const {
    return this->_B;
}

void RegisterBank::setB(const int temp) {
	this->_B = temp;
	emit this->valuesChanged();
}

int RegisterBank::getC() const {
	return this->_C;
}

void RegisterBank::setC(const int temp) {
	this->_C = temp;
	emit this->valuesChanged();
}

int RegisterBank::getD() const {
	return this->_D;
}

void RegisterBank::setD(const int temp) {
	this->_D = temp;
	emit this->valuesChanged();
}

int RegisterBank::getE() const {
	return this->_E;
}

void RegisterBank::setE(const int temp) {
	this->_E = temp;
	emit this->valuesChanged();
}

int RegisterBank::getH() const {
	return this->_H;
}

void RegisterBank::setH(const int temp) {
	this->_H = temp;
	emit this->valuesChanged();
}

int RegisterBank::getL() const {
	return this->_L;
}

void RegisterBank::setL(const int temp) {
	this->_L = temp;
	emit this->valuesChanged();
}

int RegisterBank::getBC() const {
    return this->combineRegisters(this->getB(), this->getC());
}

void RegisterBank::setBC(const int temp) {
	pair<__int8, __int8> regs = decomposeRegisters((__int16)temp);
	this->setB(regs.first);
	this->setC(regs.second);
	emit this->valuesChanged();
}

int RegisterBank::getDE() const {
	return this->combineRegisters(this->getD(), this->getE());
}

void RegisterBank::setDE(const int temp) {
	pair<__int8, __int8> regs = decomposeRegisters((__int16)temp);
	this->setD(regs.first);
	this->setE(regs.second);
	emit this->valuesChanged();
}

int RegisterBank::getHL() const {
	return this->combineRegisters(this->getH(), this->getL());
}

void RegisterBank::setHL(const int temp) {
	pair<__int8, __int8> regs = decomposeRegisters((__int16)temp);
	this->setH(regs.first);
	this->setL(regs.second);
	emit this->valuesChanged();
}

int RegisterBank::getPC() const {
	return this->_PC;
}

void RegisterBank::setPC(const int temp) {
	this->_PC = temp;
	emit this->valuesChanged();
}

int RegisterBank::getSP() const {
	return this->_SP;
}

void RegisterBank::setSP(const int temp) {
	this->_SP = temp;
	emit this->valuesChanged();
}

void RegisterBank::ld(Operand &op1, Operand &op2) {
    this->sub(op1, op1);
    this->add(op1, op2);
}

void RegisterBank::add(Operand & op1,  Operand & op2) {
    setPtr setFn = this->_setAlias.at(op1.getRegisterName());
    (this->*setFn)(op1.getVal() + op2.getVal());
}

void RegisterBank::sub(Operand & op1, Operand & op2) {
    setPtr setFn = this->_setAlias.at(op1.getRegisterName());
    (this->*setFn)(op1.getVal() - op2.getVal());
}

RegisterBank::getPtr RegisterBank::getRegisterAccessor(string registerName) {
    if(this->_getAlias.find(registerName) != this->_getAlias.end())
        return this->_getAlias.at(registerName);

    return NULL;
}

void RegisterBank::instructionChanged(string fn, Operand & op1, Operand & op2) {
    if(this->_functionAlias.find(fn) != this->_functionAlias.end()) {
        fnPtr function = this->_functionAlias.at(fn);
        (this->*function)(op1, op2);
    }
}

void RegisterBank::registerValuesHaveChanged() {
    this->ui->labelAValue->setText(QString::number(this->getA()));
    this->ui->labelBValue->setText(QString::number(this->getB()));
    this->ui->labelCValue->setText(QString::number(this->getC()));
    this->ui->labelDValue->setText(QString::number(this->getD()));
    this->ui->labelEValue->setText(QString::number(this->getE()));
    this->ui->labelHValue->setText(QString::number(this->getH()));
    this->ui->labelLValue->setText(QString::number(this->getL()));
    this->ui->labelBCValue->setText(QString::number(this->getBC()));
    this->ui->labelDEValue->setText(QString::number(this->getDE()));
    this->ui->labelHLValue->setText(QString::number(this->getHL()));
    this->ui->labelPCValue->setText(QString::number(this->getPC()));
    this->ui->labelSPValue->setText(QString::number(this->getSP()));
}

void RegisterBank::programCounterChanged(const int newCounter) {
    this->setPC(newCounter);
}
