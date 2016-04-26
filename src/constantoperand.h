#ifndef CONSTANTOPERAND_H
#define CONSTANTOPERAND_H

#include "operand.h"

class ConstantOperand : public Operand
{
    public:
        ConstantOperand(const int, QObject * parent = 0);

        void setValue(const int);
        int getVal();
        QString getType();

    private:
        int _value;
};

#endif // CONSTANTOPERAND_H
