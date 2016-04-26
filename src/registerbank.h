/* CS 441 - System Architecture
 * Project #2 - gbdynbintrans - registerbank.h
 * Bucky Frost & Dustin Dodson
 *
 * This class acts as the registers of the CPU.
 * There are methods that help abstract away
 * the arithmetic functions (which was a pain!)
 */

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

    void clearFlags();
    void setZFlag();
    void setOFlag();
    void setHCFlag();
    void setCFlag();
    bool getZFlag();
    bool getOFlag();
    bool getHCFlag();
    bool getCFlag();

public slots:
//    void instructionChanged(string, Operand &, Operand &);

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

    Ui::RegisterBank *ui;
    uint8_t _A, _B, _C, _D, _E, _H, _L, _flags;
    uint16_t _PC, _SP;
};

#endif // REGISTERBANK_H
