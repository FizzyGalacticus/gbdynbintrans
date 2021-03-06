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

OpcodeDecoder::OpcodeDecoder(QString filename, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OpcodeDecoder),
    _opcodes(),
    _currentInstruction("00")
{
    ui->setupUi(this);

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
        Json::Value unprefixed = root["unprefixed"];

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
            this->_opcodes.insert(make_pair(opcode, instr));
        }
    }
}

OpcodeDecoder::~OpcodeDecoder()
{
    delete ui;
}

Operand * OpcodeDecoder::initOp(const string & opStr, RegisterBank * regBank) {
    Operand * op;

    if(opStr == "d8" || opStr == "a8")
        op = new Operand( ( (Cpu *)this->parent() )->get8BitConst() );
    else if(opStr == "d16" || opStr == "a16")
        op = new Operand( ( (Cpu *)this->parent() )->get16BitConst() );
    else op = new Operand(regBank, opStr);

    return op;
}

void OpcodeDecoder::opcodeChanged(const QString opcode, RegisterBank * regBank) {
    if(this->_opcodes.find(opcode.toStdString()) != this->_opcodes.end()) {
        this->_currentInstruction = this->_opcodes.at(opcode.toStdString());

        if(this->_currentInstruction._function == "")
            this->_currentInstruction = this->_opcodes.at("00");

        QString instruction = this->_currentInstruction._mnemonic.c_str();

        if(this->_currentInstruction._numOps >0) {
            instruction += (QString(" ") + this->_currentInstruction._op1.c_str());

            if(this->_currentInstruction._numOps > 1)
                instruction += (QString(", ") + this->_currentInstruction._op2.c_str());
        }

        this->ui->instructionLabel->setText(instruction);

        Operand * op1 = this->initOp(this->_currentInstruction._op1, regBank),
                * op2 = this->initOp(this->_currentInstruction._op2, regBank);

        emit this->instructionChanged(this->_currentInstruction._function, *op1, *op2);
    }
    else this->_currentInstruction = this->_opcodes.at("00");
}
