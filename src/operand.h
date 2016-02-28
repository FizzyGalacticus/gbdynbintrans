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
