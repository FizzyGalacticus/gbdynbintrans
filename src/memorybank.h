#ifndef MEMORYBANK_H
#define MEMORYBANK_H

#include <QDialog>
#include <unordered_map>
using std::unordered_map;

namespace Ui {
class MemoryBank;
}

class MemoryBank : public QDialog
{
    Q_OBJECT
    public:
        explicit MemoryBank(QDialog *parent = 0);
        ~MemoryBank();

        uint8_t getByte(const uint16_t);
        uint16_t getWord(const uint16_t);

        void setByte(const uint16_t, const uint8_t &);
        void setWord(const uint16_t, const uint16_t &);

    signals:

    public slots:
        void nextViewButtonPressed();
        void prevViewButtonPressed();

    private:
        void updateView();

    	Ui::MemoryBank *ui;

        unordered_map<uint16_t, uint8_t> _memory;
        int _viewPosition;
};

#endif // MEMORYBANK_H
