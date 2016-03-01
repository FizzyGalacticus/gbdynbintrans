#ifndef OPCODEDECODER_H
#define OPCODEDECODER_H

#include <QWidget>
#include <unordered_map>
using std::unordered_map;
#include "json/json.h"
#include <string>
using std::string;
#include "operand.h"

namespace Ui {
class OpcodeDecoder;
}

class OpcodeDecoder : public QWidget
{
    Q_OBJECT

public slots:
    void opcodeChanged(const QString, RegisterBank *);

signals:
    instructionChanged(string, Operand &, Operand &);

public:
    explicit OpcodeDecoder(QString filename, QWidget *parent = 0);
    ~OpcodeDecoder();

private:
    struct Instruction {
        unsigned int _numBytes:2;
        unsigned int _numOps:2;
        unsigned int _flagZ:1;
        unsigned int _flagH:1;
        unsigned int _flagN:1;
        unsigned int _flagC:1;
        char _opcode[2];
        string _op1;
        string _op2;
        string _mnemonic;
        string _function;

        Instruction(const char * opcode) {
            _opcode[0] = opcode[0];
            _opcode[1] = opcode[1];

            _numBytes = 0;
            _numOps = 0;
            _flagZ = 0;
            _flagH = 0;
            _flagN = 0;
            _flagC = 0;
            _op1 = "";
            _op2 = "";
            _mnemonic = "";
            _function = "";
        }
    };

    Operand * initOp(const string &, RegisterBank *);

    Ui::OpcodeDecoder *ui;
    unordered_map<string, Instruction> _opcodes;
    Instruction _currentInstruction;
};

#endif // OPCODEDECODER_H
