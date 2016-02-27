#ifndef OPCODEDECODER_H
#define OPCODEDECODER_H

#include <QWidget>
#include <unordered_map>
using std::unordered_map;
#include "json/json.h"
#include <string>
using std::string;

namespace Ui {
class OpcodeDecoder;
}

class OpcodeDecoder : public QWidget
{
    Q_OBJECT

public:
    explicit OpcodeDecoder(QString filename, QWidget *parent = 0);
    ~OpcodeDecoder();

private:
    struct Instruction {
        int _numBytes:2;
        int _numOps:2;
        int _flagZ:1;
        int _flagH:1;
        int _flagN:1;
        int _flagC:1;
        char _opcode[2];
        const char * _op1;
        const char * _op2;
        const char * _mnemonic;
        const char * _function;

        Instruction(const char * opcode) {
            _opcode[0] = opcode[0];
            _opcode[1] = opcode[1];

            _numBytes = 0;
            _numOps = 0;
            _flagZ = 0;
            _flagH = 0;
            _flagN = 0;
            _flagC = 0;
            _op1 = NULL;
            _op2 = NULL;
            _mnemonic = NULL;
            _function = NULL;
        }
    };

    Ui::OpcodeDecoder *ui;
    unordered_map<string, Instruction> _opcodes;
};

#endif // OPCODEDECODER_H
