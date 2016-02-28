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

    void add(Operand & op1, Operand & op2);

    void sub(Operand & op1, Operand & op2);

    getPtr getRegisterAccessor(string);

public slots:
    void instructionChanged(string, Operand &, Operand &);

private slots:
    void registerValuesHaveChanged();
    void programCounterChanged(const int);

signals:
    void valuesChanged();
    void stackPointerPositionChanged(const int);

private:

    __int16 combineRegisters(const __int8 &, const __int8 &) const;
    const pair<__int8, __int8> decomposeRegisters(const __int16 &);
    int * getGetFunction(const QString);
    void * getSetFunction(const QString);

    Ui::RegisterBank *ui;
    get_function_map _getAlias;
    set_function_map _setAlias;
    function_map _functionAlias;
    __int8 _A, _B, _C, _D, _E, _H, _L, _flags;
    __int16 _PC, _SP;
};

#endif // REGISTERBANK_H
