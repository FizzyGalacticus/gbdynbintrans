/* CS 441 - System Architecture
 * Project #2 - gbdynbintrans - opcodedecoder.cpp
 * Bucky Frost & Dustin Dodson
 */

#include "opcodedecoder.h"
#include "ui_opcodedecoder.h"
#include <QFile>
#include <utility>
using std::make_pair;
#include "cpu.h"
#include <string>
using std::string;
#include "registeroperand.h"
#include "constantoperand.h"
#include "memoryoperand.h"
#include <QDebug>

OpcodeDecoder::OpcodeDecoder(RegisterBank * regBank, MemoryBank * memBank, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OpcodeDecoder),
    _unprefixedOpcodes(),
    _prefixedOpcodes(),
    _regBank(regBank),
    _memory(memBank),
    _opcodeFileName(":opcodes.json"),
    _currentInstruction("00")
{
    ui->setupUi(this);

    /*Map strings to RegisterBank function pointers*/
    this->_functionAlias.insert(make_pair<string, fnPtr>(string("ld"), &OpcodeDecoder::ld));
    this->_functionAlias.insert(make_pair<string, fnPtr>(string("jpConditional"), &OpcodeDecoder::jpConditional));
    this->_functionAlias.insert(make_pair<string, fnPtr>(string("add"), &OpcodeDecoder::add));
    this->_functionAlias.insert(make_pair<string, fnPtr>(string("sub"), &OpcodeDecoder::sub));
    this->_functionAlias.insert(make_pair<string, fnPtr>(string("inc"), &OpcodeDecoder::inc));
    this->_functionAlias.insert(make_pair<string, fnPtr>(string("dec"), &OpcodeDecoder::dec));
    this->_functionAlias.insert(make_pair<string, fnPtr>(string("nd"), &OpcodeDecoder::nd));
    this->_functionAlias.insert(make_pair<string, fnPtr>(string("orr"), &OpcodeDecoder::orr));
    this->_functionAlias.insert(make_pair<string, fnPtr>(string("xorr"), &OpcodeDecoder::xorr));
    this->_functionAlias.insert(make_pair<string, fnPtr>(string("cp"), &OpcodeDecoder::cp));
    this->_functionAlias.insert(make_pair<string, fnPtr>(string("testBit"), &OpcodeDecoder::testBit));
    this->_functionAlias.insert(make_pair<string, fnPtr>(string("resetBit"), &OpcodeDecoder::resetBit));
    this->_functionAlias.insert(make_pair<string, fnPtr>(string("setBit"), &OpcodeDecoder::setBit));

    this->parseOpcodeJSON(this->_opcodeFileName, "unprefixed", this->_unprefixedOpcodes);
    this->parseOpcodeJSON(this->_opcodeFileName, "cbprefixed", this->_prefixedOpcodes);
}

OpcodeDecoder::~OpcodeDecoder() {
    delete ui;
}

void OpcodeDecoder::parseOpcodeJSON(const QString & filename, const QString & rootJSON, unordered_map<std::__cxx11::string, Instruction> & opcodeMap) {
    QFile * jsonFile = new QFile(filename);

    jsonFile->open(QFile::ReadOnly);
    string fileContents = jsonFile->readAll().toStdString();
    jsonFile->close();

    Json::Value root;   // will contains the root value after parsing.
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(fileContents.c_str(), root );

    if(!parsingSuccessful) {
        // report to the user the failure and their locations in the document.
        QString err = "Failed to parse configuration\n";
        err += QString(reader.getFormattedErrorMessages().c_str());
        this->ui->instructionLabel->setText(err);
    } else {
        Json::Value unprefixed = root[rootJSON.toStdString()];

        for(auto i = unprefixed.begin(); i != unprefixed.end(); i++) {
            string opcode = i.name().substr(2,2);

            if(opcode.size() == 1)
                opcode = "0" + opcode;

            Instruction instr(opcode.c_str());

            //Temporarily store values into Json::Value objects
            Json::Value mnemonic = (*i)["mnemonic"];
            Json::Value flags = (*i)["flags_ZHNC"];
            Json::Value bytes = (*i)["bytes"];
            Json::Value operandCount = (*i)["operand_count"];
            Json::Value operand1 = (*i)["operand1"];
            Json::Value operand2 = (*i)["operand2"];
            Json::Value function = (*i)["function"];

            //Set values in Instruction object
            instr._mnemonic = mnemonic.asString();

            if(!flags.isNull()) {
                instr._flagZ = (flags[0] == "-" ? 0 : 1);
                instr._flagH = (flags[1] == "-" ? 0 : 1);
                instr._flagN = (flags[2] == "-" ? 0 : 1);
                instr._flagC = (flags[3] == "-" ? 0 : 1);
            }

            if(!operand1.isNull())
                instr._op1 = operand1.asString();
            if(!operand2.isNull())
                instr._op2 = operand2.asString();

            instr._numOps = operandCount.asInt();
            instr._numBytes = bytes.asInt();

            if(!function.isNull())
                instr._function = function.asString();

            //Add instruction to map
            opcodeMap.insert(make_pair(opcode, instr));
            qDebug() << opcode.c_str();
        }
    }
}

void OpcodeDecoder::callFunction(string fn, Operand * op1, Operand * op2) {
    if(this->_functionAlias.find(fn) != this->_functionAlias.end()) {
        fnPtr function = this->_functionAlias.at(fn);
        (this->*function)(op1, op2);
    }
}

void OpcodeDecoder::ld(Operand * op1, Operand * op2) {
    this->sub(op1, op1);
    this->add(op1, op2);
    this->_regBank->clearFlags();
}

void OpcodeDecoder::jpAbsolute(Operand * op1) {
    this->_regBank->setPC(op1->getVal()+512);
//    emit this->jumpTriggered(this->_regBank->getPC());
}

void OpcodeDecoder::jpConditional(Operand * op1, Operand * op2) {
    if(op1->getType() != "REGISTER")
        this->jpAbsolute(op1);
    else {
        RegisterOperand * regOp = (RegisterOperand *)op1;
        if(regOp->getRegisterName() == "Z" && this->_regBank->getZFlag())
            this->jpAbsolute(op2);
        else if(regOp->getRegisterName() == "NZ" && !this->_regBank->getZFlag())
            this->jpAbsolute(op2);
        else if(regOp->getRegisterName() == "C" && this->_regBank->getCFlag())
            this->jpAbsolute(op2);
        else if(regOp->getRegisterName() == "NC" && !this->_regBank->getCFlag())
            this->jpAbsolute(op2);
    }
}

void OpcodeDecoder::add(Operand * op1,  Operand * op2) {
    this->_regBank->clearFlags(); //Clear flags

    const int original = op1->getVal();

    op1->setValue(op1->getVal() + op2->getVal());

    //Set flags
    if(op1->getVal() == 0)
        this->_regBank->setZFlag();
    if(original <= 15 && op1->getVal() > 15)
        this->_regBank->setHCFlag();
    if(op2->getVal() > 0 && op1->getVal() < original)
        this->_regBank->setCFlag();
}

void OpcodeDecoder::sub(Operand * op1, Operand * op2) {
    this->_regBank->clearFlags(); //Clear flags

    const int original = op1->getVal();

    op1->setValue(op1->getVal() - op2->getVal());

    //Set flags
    if(op1->getVal() == 0)
        this->_regBank->setZFlag();
    if(op2->getVal() > 0 && op1->getVal() > original)
        this->_regBank->setCFlag();
    this->_regBank->setOFlag();
}

void OpcodeDecoder::inc(Operand * op1, Operand * op2) {
    op2->setValue(1);
    this->add(op1, op2);
}

void OpcodeDecoder::dec(Operand * op1, Operand * op2) {
    op2->setValue(1);
    this->sub(op1, op2);
}

void OpcodeDecoder::nd(Operand * op1, Operand * op2) {
    this->_regBank->setA(this->_regBank->getA() & op1->getVal());
}

void OpcodeDecoder::orr(Operand * op1, Operand * op2) {
    this->_regBank->setA(this->_regBank->getA() | op1->getVal());
}

void OpcodeDecoder::xorr(Operand * op1, Operand * op2) {
    this->_regBank->setA(this->_regBank->getA() ^ op1->getVal());
}

void OpcodeDecoder::cp(Operand * op1, Operand * op2) {
    this->_regBank->clearFlags();

    const int A = this->_regBank->getA();
    const int cmpVal = op1->getVal();

    //Set flags
    if(A - cmpVal == 0)
        this->_regBank->setZFlag();
    if(cmpVal > 0 && (A - cmpVal) > A)
        this->_regBank->setCFlag();
    this->_regBank->setOFlag();
}

void OpcodeDecoder::testBit(Operand * op1, Operand * op2) {
    this->_regBank->clearFlags();

    int bitNum = pow(2, op1->getVal());

    bool bitIsSet = (op2->getVal() & bitNum);

    if(!bitIsSet)
        this->_regBank->setZFlag();

    this->_regBank->setHCFlag();
}

void OpcodeDecoder::resetBit(Operand * op1, Operand * op2) {
    this->_regBank->clearFlags();

    int newNum = op2->getVal() & ~(1 << op1->getVal());

    op2->setValue(newNum);
}

void OpcodeDecoder::setBit(Operand * op1, Operand * op2) {
    this->_regBank->clearFlags();

    int newNum = op2->getVal() | (1 << op1->getVal());

    op2->setValue(newNum);
}

Operand * OpcodeDecoder::initOp(const string & opStr) {
    int opNum = -1;

    //Test if opStr is an integer
    try{opNum = std::stoi(opStr);}
    catch(std::invalid_argument e){}

    if(opStr == "d8")
        return new ConstantOperand( ( (Cpu *)this->parent() )->get8BitConst() );
    else if(opStr == "d16")
        return new ConstantOperand( ( (Cpu *)this->parent() )->get16BitConst() );
    else if(opStr == "a8")
        return new MemoryOperand(this->_memory, ((Cpu *)this->parent() )->get8BitConst());
    else if(opStr == "a16")
        return new MemoryOperand(this->_memory, ((Cpu *)this->parent() )->get16BitConst(), true);
    else if(opNum > -1)
        return new ConstantOperand(opNum);
    else if(opStr == "")
        return new ConstantOperand(0);
    else return new RegisterOperand(this->_regBank, opStr.c_str());
}

void OpcodeDecoder::opcodeChanged(const QString opcode) {
    QString instruction;

    if(opcode == "cb" && !(((Cpu *)this->parent())->getMode())) {
        ((Cpu *)this->parent())->setMode(1);

        QString newOp = QString::number(((Cpu *)this->parent())->get8BitConst(), 16);
        if(newOp.size() == 1) newOp = "0" + newOp;

        this->opcodeChanged(newOp);
    }
    else if(((Cpu *)this->parent())->getMode() && this->_prefixedOpcodes.find(opcode.toStdString()) != this->_prefixedOpcodes.end()) {
        ((Cpu *)this->parent())->setMode(1);
        this->_currentInstruction = this->_prefixedOpcodes.at(opcode.toStdString());

        if(this->_currentInstruction._function == "") {
            this->_currentInstruction = this->_unprefixedOpcodes.at("00");
            ((Cpu *)this->parent())->setMode(0);
        }

        instruction = this->_currentInstruction._mnemonic.c_str();

        if(this->_currentInstruction._numOps > 0) {
            instruction += (QString(" ") + this->_currentInstruction._op1.c_str());

            if(this->_currentInstruction._numOps > 1)
                instruction += (QString(", ") + this->_currentInstruction._op2.c_str());
        }

        this->ui->instructionLabel->setText(instruction);

        Operand * op1 = this->initOp(this->_currentInstruction._op1),
                * op2 = this->initOp(this->_currentInstruction._op2);

        ((Cpu *)this->parent())->setMode(0);

        this->callFunction(this->_currentInstruction._function, op1, op2);
    }
    else if(this->_unprefixedOpcodes.find(opcode.toStdString()) != this->_unprefixedOpcodes.end()) {
        this->_currentInstruction = this->_unprefixedOpcodes.at(opcode.toStdString());

        if(this->_currentInstruction._function == "")
            this->_currentInstruction = this->_unprefixedOpcodes.at("00");

        instruction = this->_currentInstruction._mnemonic.c_str();

        if(this->_currentInstruction._numOps > 0) {
            instruction += (QString(" ") + this->_currentInstruction._op1.c_str());

            if(this->_currentInstruction._numOps > 1)
                instruction += (QString(", ") + this->_currentInstruction._op2.c_str());
        }

        this->ui->instructionLabel->setText(instruction);

        Operand * op1 = this->initOp(this->_currentInstruction._op1.c_str()),
                * op2 = this->initOp(this->_currentInstruction._op2.c_str());

        this->callFunction(this->_currentInstruction._function, op1, op2);
    }
    else {
        qDebug() << "Setting to NOP because code is undefined: " + opcode;
        this->_currentInstruction = this->_unprefixedOpcodes.at("00");
        instruction = this->_currentInstruction._mnemonic.c_str();
        this->ui->instructionLabel->setText(instruction);
    }
}
