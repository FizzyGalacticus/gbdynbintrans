/* CS 441 - System Architecture
 * Project #2 - gbdynbintrans - operand.h
 * Bucky Frost & Dustin Dodson
 *
 * This class is to abstract the method
 * of getting a value, whether the value
 * originates from a register or be a
 * constant, this allows us to perform
 * the same operation without worrying
 * about it.
 */

#ifndef OPERAND_H
#define OPERAND_H

#include <QObject>
#include <string>
using std::string;
#include "registerbank.h"

class RegisterBank;

class Operand : public QObject
{
    Q_OBJECT
public slots:

signals:

public:
    Operand(RegisterBank *, string, QObject *parent = 0);
    Operand(const int, QObject *parent=0);

    void setRegisterBank(RegisterBank *);
    void setValue(const int);
    int getVal() const;
    const string getRegisterName();

private:
//    typedef RegisterBank::getPtr getPtr;

    RegisterBank * _regBank;
//    getPtr _regVal;
    int _constVal;
    string _registerName;
};

#endif // OPERAND_H
