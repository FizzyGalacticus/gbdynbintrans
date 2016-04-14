#include "memorybank.h"
#include "ui_memorybank.h"
#include <utility>
using std::make_pair;

MemoryBank::MemoryBank(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MemoryBank),
    _memory(unordered_map<uint16_t, uint8_t>())
{
    ui->setupUi(this);
}

MemoryBank::~MemoryBank() {
    delete ui;
}
uint8_t MemoryBank::getByte(const uint16_t addr) {
    if(this->_memory.find(addr) == this->_memory.end())
        this->_memory.insert(make_pair(addr, 0));

    return this->_memory[addr];
}

uint16_t MemoryBank::getWord(const uint16_t addr) {
	uint8_t byte1 = this->getByte(addr),
            byte2 = this->getByte(addr+1);

    return int((byte1 << 8) | byte2);
}

void MemoryBank::setByte(const uint16_t addr, const uint8_t & val) {
    this->_memory[addr] = val;
}

void MemoryBank::setWord(const uint16_t addr, const uint16_t & word) {
	this->setByte(addr, (word >> 8));
    this->setByte(addr+1,((word << 8) >> 8));
}
