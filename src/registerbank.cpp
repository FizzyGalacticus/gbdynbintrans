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
    this->_functionAlias.insert(make_pair<string, fnPtr>("jpConditional", &RegisterBank::jpConditional));
    this->_functionAlias.insert(make_pair<string, fnPtr>("add", &RegisterBank::add));
    this->_functionAlias.insert(make_pair<string, fnPtr>("sub", &RegisterBank::sub));

    emit this->valuesChanged();
}

RegisterBank::~RegisterBank()
{
    delete ui;
}

uint16_t RegisterBank::combineRegisters(const uint8_t & highReg, const uint8_t & lowReg) const {
    uint16_t combinedRegisters = highReg;
    combinedRegisters = (combinedRegisters << 8) | lowReg;
    return combinedRegisters;
}

const pair<uint8_t, uint8_t> RegisterBank::decomposeRegisters(const uint16_t & reg) {
    return pair<uint8_t, uint8_t>((reg >> 8), ((reg << 8) >> 8));
}

void RegisterBank::clearFlags() {
    this->_flags = 0;
    emit this->valuesChanged();
}

void RegisterBank::setZFlag() {
    this->_flags = this->_flags | 0x80;
    emit this->valuesChanged();
}

void RegisterBank::setOFlag() {
    this->_flags = this->_flags | 0x40;
    emit this->valuesChanged();
}

void RegisterBank::setHCFlag() {
    this->_flags = this->_flags | 0x20;
    emit this->valuesChanged();
}

void RegisterBank::setCFlag() {
    this->_flags = this->_flags | 0x10;
    emit this->valuesChanged();
}

bool RegisterBank::getZFlag() {
    return ( (this->_flags & 0x80) > 1);
}

bool RegisterBank::getOFlag() {
    return ( (this->_flags & 0x40) > 1);
}

bool RegisterBank::getHCFlag() {
    return ( (this->_flags & 0x20) > 1);
}

bool RegisterBank::getCFlag() {
    return ( (this->_flags & 0x10) > 1);
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
    pair<uint8_t, uint8_t> regs = decomposeRegisters((uint16_t)temp);
	this->setB(regs.first);
	this->setC(regs.second);
	emit this->valuesChanged();
}

int RegisterBank::getDE() const {
	return this->combineRegisters(this->getD(), this->getE());
}

void RegisterBank::setDE(const int temp) {
    pair<uint8_t, uint8_t> regs = decomposeRegisters((uint16_t)temp);
	this->setD(regs.first);
	this->setE(regs.second);
	emit this->valuesChanged();
}

int RegisterBank::getHL() const {
	return this->combineRegisters(this->getH(), this->getL());
}

void RegisterBank::setHL(const int temp) {
    pair<uint8_t, uint8_t> regs = decomposeRegisters((uint16_t)temp);
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

void RegisterBank::ld(Operand & op1, Operand & op2) {
    this->sub(op1, op1);
    this->add(op1, op2);
}

void RegisterBank::jpAbsolute(Operand & op1) {
    this->setPC(op1.getVal()-900);
    emit this->jumpTriggered(this->getPC());
}

void RegisterBank::jpConditional(Operand & op1, Operand & op2) {
    if(op1.getRegisterName() == "")
        this->jpAbsolute(op1);
    else if(op1.getRegisterName() == "Z" && this->getZFlag())
        this->jpAbsolute(op2);
    else if(op1.getRegisterName() == "NZ" && !this->getZFlag())
        this->jpAbsolute(op2);
    else if(op1.getRegisterName() == "C" && this->getCFlag())
        this->jpAbsolute(op2);
    else if(op1.getRegisterName() == "NC" && !this->getCFlag())
        this->jpAbsolute(op2);
}

void RegisterBank::add(Operand & op1,  Operand & op2) {
    this->clearFlags(); //Clear flags

    const int original = op1.getVal();

    setPtr setFn = this->_setAlias.at(op1.getRegisterName());
    (this->*setFn)(op1.getVal() + op2.getVal());

    //Set flags
    if(op1.getVal() == 0)
        this->setZFlag();
    if(original <= 15 && op1.getVal() > 15)
        this->setHCFlag();
    if(op2.getVal() > 0 && op1.getVal() < original)
        this->setCFlag();
}

void RegisterBank::sub(Operand & op1, Operand & op2) {
    this->clearFlags(); //Clear flags

    const int original = op1.getVal();

    setPtr setFn = this->_setAlias.at(op1.getRegisterName());
    (this->*setFn)(op1.getVal() - op2.getVal());

    //Set flags
    if(op1.getVal() == 0)
        this->setZFlag();
    if(op2.getVal() > 0 && op1.getVal() > original)
        this->setCFlag();
    this->setOFlag();
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
    this->ui->zeroFlagValue->setText(QString::number((this->_flags & 0x80)>>7));
    this->ui->subOpFlagValue->setText(QString::number((this->_flags & 0x40)>>6));
    this->ui->hCarryFlagValue->setText(QString::number((this->_flags & 0x20)>>5));
    this->ui->carryFlagValue->setText(QString::number((this->_flags & 0x10)>>4));
}

void RegisterBank::programCounterChanged(const int newCounter) {
    this->setPC(newCounter);
}
