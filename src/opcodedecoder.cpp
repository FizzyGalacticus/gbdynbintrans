#include "opcodedecoder.h"
#include "ui_opcodedecoder.h"
#include <iostream>
using std::cout;
using std::endl;
#include <QFile>
#include <utility>
using std::make_pair;

OpcodeDecoder::OpcodeDecoder(QString filename, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OpcodeDecoder),
    _opcodes()
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
        err += QString(reader.getFormatedErrorMessages().c_str());
        this->ui->instructionLabel->setText(err);
    } else {
        Json::Value unprefixed = root["unprefixed"];

        for(auto i = unprefixed.begin(); i != unprefixed.end(); i++) {
            string opcode = i.name().substr(2,2);
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
            instr._mnemonic = mnemonic.asCString();
//            instr._flagZ =
//            instr._flagH =
//            instr._flagN =
//            instr._flagC =

            if(!operand1.isNull())
                instr._op1 = operand1.asCString();
            if(!operand2.isNull())
                instr._op2 = operand2.asCString();

            instr._numOps = operandCount.asInt();
            instr._numBytes = bytes.asInt();

            if(!function.isNull())
                instr._function = function.asCString();

            //Add instruction to map
            this->_opcodes.insert(make_pair(opcode, instr));
            cout << instr._mnemonic << endl;
        }
    }
}

OpcodeDecoder::~OpcodeDecoder()
{
    delete ui;
}
