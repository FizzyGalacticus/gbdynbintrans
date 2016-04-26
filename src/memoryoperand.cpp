#include "memoryoperand.h"

MemoryOperand::MemoryOperand(MemoryBank * memBank, const uint8_t addr, bool mode, QObject *parent) :
    Operand(parent),
    _memory(memBank),
    _address(addr),
    _mode(mode)
{

}

void MemoryOperand::setValue(const int val) {
    if(this->_mode)
        this->_memory->setWord(this->_address, val);
    else this->_memory->setByte(this->_address, val);
}

int MemoryOperand::getVal() {
    if(this->_mode)
        return this->_memory->getWord(this->_address);
    else return this->_memory->getByte(this->_address);
}

QString MemoryOperand::getType() {
    return "MEMORY";
}
