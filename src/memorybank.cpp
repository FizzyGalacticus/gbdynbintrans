#include "memorybank.h"
#include "ui_memorybank.h"
#include <utility>
using std::make_pair;
#include <vector>
using std::vector;
#include <QListWidgetItem>
#include <algorithm>
using std::sort;
#include <QDebug>

MemoryBank::MemoryBank(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::MemoryBank),
    _memory(unordered_map<uint16_t, uint8_t>()),
    _viewPosition(0)
{
    ui->setupUi(this);
    connect(ui->nextButton, SIGNAL(clicked(bool)), this, SLOT(nextViewButtonPressed()));
    connect(ui->prevButton, SIGNAL(clicked(bool)), this, SLOT(prevViewButtonPressed()));
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

    this->updateView();
}

void MemoryBank::setWord(const uint16_t addr, const uint16_t & word) {
	this->setByte(addr, (word >> 8));
    this->setByte(addr+1,((word << 8) >> 8));
}

void MemoryBank::nextViewButtonPressed() {
    const int maxPosition = (this->_memory.size()/11-1);

    if(this->_viewPosition < maxPosition) {
        this->_viewPosition++;
        this->updateView();
    }
}

void MemoryBank::prevViewButtonPressed() {
    if(this->_viewPosition > 0) {
        this->_viewPosition--;
        this->updateView();
    }
}

void MemoryBank::updateView() {
    this->ui->listOne->clear();
    this->ui->listTwo->clear();

    const unsigned int viewCount = 11,
              startingPos = this->_viewPosition*viewCount;

    vector<uint16_t> keys;

    for(auto i : this->_memory)
        keys.push_back(i.first);

    sort(keys.begin(), keys.end());

    for(auto i = startingPos; i < startingPos+viewCount && i < keys.size(); i++) {
        QListWidgetItem * item = new QListWidgetItem;
        QString addr = QString::number(keys[i], 16);

        while(addr.size() < 4) addr = "0" + addr;

        item->setText(addr + ": " + QString::number(this->getByte(i)));
        this->ui->listOne->addItem(item);
    }

    for(auto i = startingPos+viewCount; i < startingPos+2*viewCount && i < keys.size(); i++) {
        QListWidgetItem * item = new QListWidgetItem;
        item->setText(QString::number(keys[i]) + ": " + QString::number(this->getByte(i)));
        this->ui->listTwo->addItem(item);
    }
}
