/* CS 441 - System Architecture
 * Project #2 - gbdynbintrans - opcodedecoder.h
 * Bucky Frost & Dustin Dodson
 *
 * This class uses the "opcodes.json" file that
 * we have, grabs all of the opcodes, and parses
 * the commands as they come in from the CPU.
 */

#ifndef OPCODEDECODER_H
#define OPCODEDECODER_H

#include <QWidget>
#include <unordered_map>
using std::unordered_map;
#include "json/json.h"
#include <string>
using std::string;
#include "operand.h"
#include "memorybank.h"
#include "registerbank.h"
#include <utility>
using std::pair;

namespace Ui {
class OpcodeDecoder;
}

class OpcodeDecoder : public QWidget
{
    Q_OBJECT

public slots:
    void opcodeChanged(const QString);
    void callFunction(string fn, Operand * op1, Operand * op2);

signals:
    void instructionChanged(string, Operand &, Operand &);

public:
    explicit OpcodeDecoder(RegisterBank *, MemoryBank *, QWidget *parent=0);
    ~OpcodeDecoder();

private:
    typedef void (OpcodeDecoder::*fnPtr)(Operand *, Operand *);
    typedef std::map<string, fnPtr> function_map;

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

    void parseOpcodeJSON(const QString &, const QString &, unordered_map<string, Instruction> &);
    void executeOpcode(Operand *, Operand *);

    /*           Opcode Functions                 */
    void ld(Operand *, Operand *);
    void jpAbsolute(Operand *);
    void jpConditional(Operand *, Operand *);
    void add(Operand *, Operand *);
    void sub(Operand *, Operand *);
    void inc(Operand *, Operand *);
    void dec(Operand *, Operand *);
    void nd(Operand *, Operand *); //and, or & xor are c++ keywords
    void orr(Operand *, Operand *);
    void xorr(Operand *, Operand *);
    void cp(Operand *, Operand *);
    void testBit(Operand *, Operand *);
    void resetBit(Operand *, Operand *);
    void setBit(Operand *, Operand *);
    /**********************************************/

    Operand * initOp(const string &);

    Ui::OpcodeDecoder *ui;
    unordered_map<string, Instruction> _unprefixedOpcodes, _prefixedOpcodes;
    RegisterBank * _regBank;
    MemoryBank * _memory;
    const QString _opcodeFileName;
    Instruction _currentInstruction;
    function_map _functionAlias;
};

#endif // OPCODEDECODER_H
