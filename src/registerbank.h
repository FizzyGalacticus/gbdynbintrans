#ifndef REGISTERBANK_H
#define REGISTERBANK_H

#include <QWidget>
#include <utility>
using std::pair;
#include <unordered_map>
using std::unordered_map;
#include <string>
using std::string;
#include "operand.h"

class Operand;

namespace Ui {
class RegisterBank;
}

class RegisterBank : public QWidget
{
    Q_OBJECT

public:
    /* Typdefs needed for passing function pointers */
    typedef int (RegisterBank::*getPtr)(void) const;
    typedef void (RegisterBank::*setPtr)(int);
    typedef void (RegisterBank::*fnPtr)(Operand &, Operand &);
    typedef std::map<string, getPtr> get_function_map;
    typedef std::map<string, setPtr> set_function_map;
    typedef std::map<string, fnPtr> function_map;

    explicit RegisterBank(QWidget *parent = 0);
    ~RegisterBank();

    int getA() const;
    void setA(const int);

    int getB() const;
    void setB(const int);

    int getC() const;
    void setC(const int);

    int getD() const;
    void setD(const int);

    int getE() const;
    void setE(const int);

    int getH() const;
    void setH(const int);

    int getL() const;
    void setL(const int);

    int getBC() const;
    void setBC(const int);

    int getDE() const;
    void setDE(const int);

    int getHL() const;
    void setHL(const int);

    int getPC() const;
    void setPC(const int);

    int getSP() const;
    void setSP(const int);

    void ld(Operand &, Operand &);
    void jp(Operand &, Operand &);
    void add(Operand &, Operand &);
    void sub(Operand &, Operand &);

    getPtr getRegisterAccessor(string);

public slots:
    void instructionChanged(string, Operand &, Operand &);

private slots:
    void registerValuesHaveChanged();
    void programCounterChanged(const int);

signals:
    void valuesChanged();
    void jumpTriggered(const int);
    void stackPointerPositionChanged(const int);

private:
    uint16_t combineRegisters(const uint8_t &, const uint8_t &) const;
    const pair<uint8_t, uint8_t> decomposeRegisters(const uint16_t &);
    int * getGetFunction(const QString);
    void * getSetFunction(const QString);
    void clearFlags();
    void setZFlag();
    void setOFlag();
    void setHCFlag();
    void setCFlag();

    Ui::RegisterBank *ui;
    get_function_map _getAlias;
    set_function_map _setAlias;
    function_map _functionAlias;
    uint8_t _A, _B, _C, _D, _E, _H, _L, _flags;
    uint16_t _PC, _SP;
};

#endif // REGISTERBANK_H
