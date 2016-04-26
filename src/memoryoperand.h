#ifndef MEMORYOPERAND_H
#define MEMORYOPERAND_H

#include "operand.h"
#include "memorybank.h"


class MemoryOperand : public Operand
{
    public:
        MemoryOperand(MemoryBank *, const uint8_t, bool mode = 0, QObject * parent = 0);

        void setValue(const int);
        int getVal();
        QString getType();

    private:
        MemoryBank * _memory;
        const uint8_t _address;
        const bool _mode; //0 for 8 bit, 1 for 16 bit
};

#endif // MEMORYOPERAND_H
