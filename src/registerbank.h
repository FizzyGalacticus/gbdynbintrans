#ifndef REGISTERBANK_H
#define REGISTERBANK_H

#include <QWidget>
#include <utility>
using std::pair;
#include <unordered_map>
using std::unordered_map;
#include <string>
using std::string;

namespace Ui {
class RegisterBank;
}

class RegisterBank : public QWidget
{
    Q_OBJECT

public:
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

    void add(const QString op1, const QString op2);
    void add(const QString op1, const int op2);

private slots:
    void registerValuesHaveChanged();
    void programCounterChanged(const int);

signals:
    void valuesChanged();
    void stackPointerPositionChanged(const int);

private:
    /* Typdefs needed for passing function pointers */
    typedef int (RegisterBank::*getPtr)(void) const;
    typedef void (RegisterBank::*setPtr)(int);
    typedef std::map<string, getPtr> get_function_map;
    typedef std::map<string, setPtr> set_function_map;

    __int16 combineRegisters(const __int8 &, const __int8 &) const;
    const pair<__int8, __int8> decomposeRegisters(const __int16 &);
    int * getGetFunction(const QString);
    void * getSetFunction(const QString);

    Ui::RegisterBank *ui;
    get_function_map _getAlias;
    set_function_map _setAlias;
    __int8 _A, _B, _C, _D, _E, _H, _L, _flags;
    __int16 _PC, _SP;
};

#endif // REGISTERBANK_H
