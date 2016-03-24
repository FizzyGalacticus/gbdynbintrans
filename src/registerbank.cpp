/* CS 441 - System Architecture
 * Project #2 - gbdynbintrans - registerbank.cpp
 * Bucky Frost & Dustin Dodson
 */

#include "registerbank.h"
#include "ui_registerbank.h"
#include <utility>
using std::pair;
using std::make_pair;

/*
 * Name: RegisterBank
 * Pre-conditions: None
 * Post-conditions: Will have created a valid RegisterBank
 *     object, with all registers set to 0.
 */
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

    /*
     * The rest of this constructor is horrible and yucky. Unless you want to
     * lose your mind, I suggest turning back now. Read at your own risk!
     */

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
    this->_functionAlias.insert(make_pair<string, fnPtr>("inc", &RegisterBank::inc));
    this->_functionAlias.insert(make_pair<string, fnPtr>("nd", &RegisterBank::nd));
    this->_functionAlias.insert(make_pair<string, fnPtr>("orr", &RegisterBank::orr));
    this->_functionAlias.insert(make_pair<string, fnPtr>("xorr", &RegisterBank::xorr));
    this->_functionAlias.insert(make_pair<string, fnPtr>("cp", &RegisterBank::cp));

    emit this->valuesChanged();
}

/*
 * Name: ~RegisterBank
 * Pre-conditions: None
 * Post-conditions: Cleans up all of the RegisterBank UI.
 */
RegisterBank::~RegisterBank()
{
    delete ui;
}

/*
 * Name: combineRegisters
 * Pre-conditions: Operands must both be valid 8-bit integers.
 * Post-conditions: Returns a 16-bit integer with the first 
 *     operand's bits as the first 8 bits, and the second
 *     operand's bits as the last 8 bits.
 */
uint16_t RegisterBank::combineRegisters(const uint8_t & highReg, const uint8_t & lowReg) const {
    uint16_t combinedRegisters = highReg;
    combinedRegisters = (combinedRegisters << 8) | lowReg;
    return combinedRegisters;
}

/*
 * Name: decomposeRegisters
 * Pre-conditions: Operand must be a valid 16-bit integer.
 * Post-conditions: Returns a pair containing two 8-bit integers,
 *     the first being the first 8 bits of the operand, the
 *     second being the last 8 bits.
 */
const pair<uint8_t, uint8_t> RegisterBank::decomposeRegisters(const uint16_t & reg) {
    return pair<uint8_t, uint8_t>((reg >> 8), ((reg << 8) >> 8));
}

/*
 * Name: clearFlags
 * Pre-conditions: None
 * Post-conditions: Clears all arithmetic flags.
 */
void RegisterBank::clearFlags() {
    this->_flags = 0;
    emit this->valuesChanged();
}

/*
 * Name: setZFlag
 * Pre-conditions: None
 * Post-conditions: Sets the bit representing Z in the
 *     8-bit flag integer.
 */
void RegisterBank::setZFlag() {
    this->_flags = this->_flags | 0x80;
    emit this->valuesChanged();
}

/*
 * Name: setOFlag
 * Pre-conditions: None
 * Post-conditions: Sets the bit representing O in the
 *     8-bit flag register.
 */
void RegisterBank::setOFlag() {
    this->_flags = this->_flags | 0x40;
    emit this->valuesChanged();
}

/*
 * Name: setHCFlag
 * Pre-conditions: None
 * Post-conditions: Sets the bit representing HC in the
 *     8-bit flag register.
 */
void RegisterBank::setHCFlag() {
    this->_flags = this->_flags | 0x20;
    emit this->valuesChanged();
}

/*
 * Name: setCFlag
 * Pre-conditions: None
 * Post-conditions: Sets the bit representing C in the
 *     8-bit flag register.
 */
void RegisterBank::setCFlag() {
    this->_flags = this->_flags | 0x10;
    emit this->valuesChanged();
}

/*
 * Name: getZFlag
 * Pre-conditions: None
 * Post-conditions: Returns true if the bit representing
 *     Z in the 8-bit flag register is 1.
 */
bool RegisterBank::getZFlag() {
    return ( (this->_flags & 0x80) > 1);
}

/*
 * Name: getOFlag
 * Pre-conditions: None
 * Post-conditions: Returns true if the bit representing
 *     O in the 8-bit flag register is 1.
 */
bool RegisterBank::getOFlag() {
    return ( (this->_flags & 0x40) > 1);
}

/*
 * Name: getHCFlag
 * Pre-conditions: None
 * Post-conditions: Returns true if the bit representing
 *     HC in the 8-bit flag register is 1.
 */
bool RegisterBank::getHCFlag() {
    return ( (this->_flags & 0x20) > 1);
}

/*
 * Name: getCFlag
 * Pre-conditions: None
 * Post-conditions: Returns true if the bit representing
 *     C in the 8-bit flag register is 1.
 */
bool RegisterBank::getCFlag() {
    return ( (this->_flags & 0x10) > 1);
}

/*
 * Name: getA
 * Pre-conditions: None
 * Post-conditions: Returns the contents of the A register.
 */
int RegisterBank::getA() const {
    return this->_A;
}

/*
 * Name: setA
 * Pre-conditions: Operand must be a valid integer.
 * Post-conditions: Will set the contents of the A
 *     register to the value in temp.
 */
void RegisterBank::setA(const int temp) {
    this->_A = temp;
    emit this->valuesChanged();
}

/*
 * Name: getB
 * Pre-conditions: None
 * Post-conditions: Returns the contents of the B register.
 */
int RegisterBank::getB() const {
    return this->_B;
}

/*
 * Name: setB
 * Pre-conditions: Operand must be a valid integer.
 * Post-conditions: Will set the contents of the B
 *     register to the value in temp.
 */
void RegisterBank::setB(const int temp) {
    this->_B = temp;
    emit this->valuesChanged();
}

/*
 * Name: getC
 * Pre-conditions: None
 * Post-conditions: Returns the contents of the C register.
 */
int RegisterBank::getC() const {
    return this->_C;
}

/*
 * Name: setC
 * Pre-conditions: Operand must be a valid integer.
 * Post-conditions: Will set the contents of the C
 *     register to the value in temp.
 */
void RegisterBank::setC(const int temp) {
    this->_C = temp;
    emit this->valuesChanged();
}

/*
 * Name: getD
 * Pre-conditions: None
 * Post-conditions: Returns the contents of the D register.
 */
int RegisterBank::getD() const {
    return this->_D;
}

/*
 * Name: setD
 * Pre-conditions: Operand must be a valid integer.
 * Post-conditions: Will set the contents of the D
 *     register to the value in temp.
 */
void RegisterBank::setD(const int temp) {
    this->_D = temp;
    emit this->valuesChanged();
}

/*
 * Name: getE
 * Pre-conditions: None
 * Post-conditions: Returns the contents of the E register.
 */
int RegisterBank::getE() const {
    return this->_E;
}

/*
 * Name: setE
 * Pre-conditions: Operand must be a valid integer.
 * Post-conditions: Will set the contents of the E
 *     register to the value in temp.
 */
void RegisterBank::setE(const int temp) {
    this->_E = temp;
    emit this->valuesChanged();
}

/*
 * Name: getH
 * Pre-conditions: None
 * Post-conditions: Returns the contents of the H register.
 */
int RegisterBank::getH() const {
    return this->_H;
}

/*
 * Name: setH
 * Pre-conditions: Operand must be a valid integer.
 * Post-conditions: Will set the contents of the H
 *     register to the value in temp.
 */
void RegisterBank::setH(const int temp) {
    this->_H = temp;
    emit this->valuesChanged();
}

/*
 * Name: getL
 * Pre-conditions: None
 * Post-conditions: Returns the contents of the L register.
 */
int RegisterBank::getL() const {
    return this->_L;
}

/*
 * Name: setL
 * Pre-conditions: Operand must be a valid integer.
 * Post-conditions: Will set the contents of the L
 *     register to the value in temp.
 */
void RegisterBank::setL(const int temp) {
    this->_L = temp;
    emit this->valuesChanged();
}

/*
 * Name: getBC
 * Pre-conditions: None
 * Post-conditions: Returns the contents of the BC register.
 */
int RegisterBank::getBC() const {
    return this->combineRegisters(this->getB(), this->getC());
}

/*
 * Name: setBC
 * Pre-conditions: Operand must be a valid integer.
 * Post-conditions: Will set the contents of the BC
 *     register to the value in temp.
 */
void RegisterBank::setBC(const int temp) {
    pair<uint8_t, uint8_t> regs = decomposeRegisters((uint16_t)temp);
    this->setB(regs.first);
    this->setC(regs.second);
    emit this->valuesChanged();
}

/*
 * Name: getDE
 * Pre-conditions: None
 * Post-conditions: Returns the contents of the DE register.
 */
int RegisterBank::getDE() const {
    return this->combineRegisters(this->getD(), this->getE());
}

/*
 * Name: setDE
 * Pre-conditions: Operand must be a valid integer.
 * Post-conditions: Will set the contents of the DE
 *     register to the value in temp.
 */
void RegisterBank::setDE(const int temp) {
    pair<uint8_t, uint8_t> regs = decomposeRegisters((uint16_t)temp);
    this->setD(regs.first);
    this->setE(regs.second);
    emit this->valuesChanged();
}

/*
 * Name: getHL
 * Pre-conditions: None
 * Post-conditions: Returns the contents of the HL register.
 */
int RegisterBank::getHL() const {
    return this->combineRegisters(this->getH(), this->getL());
}

/*
 * Name: setHL
 * Pre-conditions: Operand must be a valid integer.
 * Post-conditions: Will set the contents of the HL
 *     register to the value in temp.
 */
void RegisterBank::setHL(const int temp) {
    pair<uint8_t, uint8_t> regs = decomposeRegisters((uint16_t)temp);
    this->setH(regs.first);
    this->setL(regs.second);
    emit this->valuesChanged();
}

/*
 * Name: getPC
 * Pre-conditions: None
 * Post-conditions: Returns the contents of the PC register.
 */
int RegisterBank::getPC() const {
    return this->_PC;
}

/*
 * Name: setPC
 * Pre-conditions: Operand must be a valid integer.
 * Post-conditions: Will set the contents of the PC
 *     register to the value in temp.
 */
void RegisterBank::setPC(const int temp) {
    this->_PC = temp;
    emit this->valuesChanged();
}

/*
 * Name: getSP
 * Pre-conditions: None
 * Post-conditions: Returns the contents of the SP register.
 */
int RegisterBank::getSP() const {
    return this->_SP;
}

/*
 * Name: setSP
 * Pre-conditions: Operand must be a valid integer.
 * Post-conditions: Will set the contents of the SP
 *     register to the value in temp.
 */
void RegisterBank::setSP(const int temp) {
    this->_SP = temp;
    emit this->valuesChanged();
}

/*
 * Name: ld
 * Pre-conditions: 
 * Post-conditions: 
 */
void RegisterBank::ld(Operand & op1, Operand & op2) {
    this->sub(op1, op1);
    this->add(op1, op2);
    this->clearFlags();
}

/*
 * Name: jpAbsolute
 * Pre-conditions: 
 * Post-conditions: 
 */
void RegisterBank::jpAbsolute(Operand & op1) {
    this->setPC(op1.getVal()-512);
    emit this->jumpTriggered(this->getPC());
}

/*
 * Name: jpConditional
 * Pre-conditions: 
 * Post-conditions: 
 */
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

/*
 * Name: add
 * Pre-conditions: 
 * Post-conditions: 
 */
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

/*
 * Name: sub
 * Pre-conditions: 
 * Post-conditions: 
 */
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

/*
 * Name: inc
 * Pre-conditions: 
 * Post-conditions: 
 */
void RegisterBank::inc(Operand & op1, Operand & op2) {
    op2.setValue(1);
    this->add(op1, op2);
}

/*
 * Name: dec
 * Pre-conditions: 
 * Post-conditions: 
 */
void RegisterBank::dec(Operand & op1, Operand & op2) {
    op2.setValue(1);
    this->sub(op1, op2);
}

/*
 * Name: nd
 * Pre-conditions: 
 * Post-conditions: 
 */
void RegisterBank::nd(Operand & op1, Operand & op2) {
    this->setA(this->getA() & op1.getVal());
}

/*
 * Name: orr
 * Pre-conditions: 
 * Post-conditions: 
 */
void RegisterBank::orr(Operand & op1, Operand & op2) {
    this->setA(this->getA() | op1.getVal());
}

/*
 * Name: xorr
 * Pre-conditions: 
 * Post-conditions: 
 */
void RegisterBank::xorr(Operand & op1, Operand & op2) {
    this->setA(this->getA() ^ op1.getVal());
}

/*
 * Name: cp
 * Pre-conditions: 
 * Post-conditions: 
 */
void RegisterBank::cp(Operand & op1, Operand & op2) {
    this->clearFlags();

    this->setOFlag();

    if(this->getA() == op1.getVal())
        this->setZFlag();
    if(this->getA() < op1.getVal())
        this->setCFlag();
    //Need to set flag HC "if no borrow from bit 4"
}

/*
 * Name: getRegisterAccessor
 * Pre-conditions: 
 * Post-conditions: 
 */
RegisterBank::getPtr RegisterBank::getRegisterAccessor(string registerName) {
    if(this->_getAlias.find(registerName) != this->_getAlias.end())
        return this->_getAlias.at(registerName);

    return NULL;
}

/*
 * Name: instructionChanged
 * Pre-conditions: 
 * Post-conditions: 
 */
void RegisterBank::instructionChanged(string fn, Operand & op1, Operand & op2) {
    if(this->_functionAlias.find(fn) != this->_functionAlias.end()) {
        fnPtr function = this->_functionAlias.at(fn);
        (this->*function)(op1, op2);
    }
}

/*
 * Name: registerValuesHaveChanged
 * Pre-conditions: 
 * Post-conditions: 
 */
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

/*
 * Name: programCounterChanged
 * Pre-conditions: 
 * Post-conditions: 
 */
void RegisterBank::programCounterChanged(const int newCounter) {
    this->setPC(newCounter);
}
