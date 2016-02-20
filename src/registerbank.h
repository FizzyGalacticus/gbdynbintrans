#ifndef REGISTERBANK_H
#define REGISTERBANK_H

#include <QWidget>
#include <utility>
using std::pair;

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

signals:
    void valueChanged();
    void stackPointerPositionChanged(const int);

private:
    __int16 combineRegisters(const __int8 &, const __int8 &) const;
    const pair<__int8, __int8> decomposeRegisters(const __int16 &);
    Ui::RegisterBank *ui;
    __int8 _A, _B, _C, _D, _E, _H, _L, _flags;
    __int16 _PC, _SP;
};

#endif // REGISTERBANK_H
