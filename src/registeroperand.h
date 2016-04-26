#ifndef REGISTEROPERAND_H
#define REGISTEROPERAND_H

#include "operand.h"
#include "registerbank.h"

class RegisterOperand : public Operand
{
    public:
        RegisterOperand(RegisterBank *, QString, QObject * parent = 0);

        void setValue(const int);
        int getVal();
        QString getType();

        const QString getRegisterName() const;

    private:
        typedef int (RegisterBank::*getPtr)(void) const;
        typedef void (RegisterBank::*setPtr)(int);
        typedef std::map<string, getPtr> get_function_map;
        typedef std::map<string, setPtr> set_function_map;

        RegisterBank * _regBank;
        const QString _registerName;
        get_function_map _getAlias;
        set_function_map _setAlias;
};

#endif // REGISTEROPERAND_H
