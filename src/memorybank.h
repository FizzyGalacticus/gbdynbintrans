#ifndef MEMORYBANK_H
#define MEMORYBANK_H

#include <QWidget>
#include <unordered_map>
using std::unordered_map;

namespace Ui {
class MemoryBank;
}

class MemoryBank : public QWidget
{
    Q_OBJECT
    public:
        explicit MemoryBank(QWidget *parent = 0);
        ~MemoryBank();

        uint8_t getByte(const uint16_t);
        uint16_t getWord(const uint16_t);

        void setByte(const uint16_t, const uint8_t &);
        void setWord(const uint16_t, const uint16_t &);

    signals:

    public slots:

    private:
    	Ui::MemoryBank *ui;

        unordered_map<uint16_t, uint8_t> _memory;
};

#endif // MEMORYBANK_H
