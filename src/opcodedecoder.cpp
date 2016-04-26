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
        }
    }
}

Operand * OpcodeDecoder::initOp(const string & opStr, RegisterBank * regBank) {
    Operand * op;
    int opNum = -1;

    //Test if opStr is an integer
    try{opNum = std::stoi(opStr);}
    catch(std::invalid_argument e){}

    if(opStr == "d8" || opStr == "a8")
        op = new Operand( ( (Cpu *)this->parent() )->get8BitConst() );
    else if(opStr == "d16" || opStr == "a16")
        op = new Operand( ( (Cpu *)this->parent() )->get16BitConst() );
    else if(opNum > -1)
        op = new Operand(opNum);
    else op = new Operand(regBank, opStr);

    return op;
}

void OpcodeDecoder::opcodeChanged(const QString opcode, RegisterBank * regBank) {
    if(opcode == "cb" && !(((Cpu *)this->parent())->getMode())) {
        ((Cpu *)this->parent())->setMode(1);

        QString newOp = QString::number(((Cpu *)this->parent())->get8BitConst(), 16);
        if(newOp.size() == 1) newOp = "0" + newOp;

        this->opcodeChanged(newOp, regBank);
    }
    else if(((Cpu *)this->parent())->getMode() && this->_prefixedOpcodes.find(opcode.toStdString()) != this->_prefixedOpcodes.end()) {
        ((Cpu *)this->parent())->setMode(1);
        this->_currentInstruction = this->_prefixedOpcodes.at(opcode.toStdString());

        if(this->_currentInstruction._function == "") {
            this->_currentInstruction = this->_unprefixedOpcodes.at("00");
            ((Cpu *)this->parent())->setMode(0);
        }

        QString instruction = this->_currentInstruction._mnemonic.c_str();

        if(this->_currentInstruction._numOps > 0) {
            instruction += (QString(" ") + this->_currentInstruction._op1.c_str());

            if(this->_currentInstruction._numOps > 1)
                instruction += (QString(", ") + this->_currentInstruction._op2.c_str());
        }

        this->ui->instructionLabel->setText(instruction);

        Operand * op1 = this->initOp(this->_currentInstruction._op1, regBank),
                * op2 = this->initOp(this->_currentInstruction._op2, regBank);

        ((Cpu *)this->parent())->setMode(0);

        emit this->instructionChanged(this->_currentInstruction._function, *op1, *op2);
    }
    else if(this->_unprefixedOpcodes.find(opcode.toStdString()) != this->_unprefixedOpcodes.end()) {
        this->_currentInstruction = this->_unprefixedOpcodes.at(opcode.toStdString());

        if(this->_currentInstruction._function == "")
            this->_currentInstruction = this->_unprefixedOpcodes.at("00");

        QString instruction = this->_currentInstruction._mnemonic.c_str();

        if(this->_currentInstruction._numOps > 0) {
            instruction += (QString(" ") + this->_currentInstruction._op1.c_str());

            if(this->_currentInstruction._numOps > 1)
                instruction += (QString(", ") + this->_currentInstruction._op2.c_str());
        }

        this->ui->instructionLabel->setText(instruction);

        Operand * op1 = this->initOp(this->_currentInstruction._op1, regBank),
                * op2 = this->initOp(this->_currentInstruction._op2, regBank);

        emit this->instructionChanged(this->_currentInstruction._function, *op1, *op2);
    }
    else this->_currentInstruction = this->_unprefixedOpcodes.at("00");
}
