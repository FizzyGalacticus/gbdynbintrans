/* CS 441 - System Architecture
 * Project #2 - gbdynbintrans - cpu.h
 * Bucky Frost & Dustin Dodson
 *
 * This class acts as the CPU of our
 * translator. It gets the opcodes
 * and translates them into commands,
 * which in turn act on the register
 * bank.
 */

#ifndef CPU_H
#define CPU_H

#include <QWidget>
#include <thread>
using std::thread;
#include "opcodedecoder.h"
#include "registerbank.h"
#include "memorybank.h"

namespace Ui {
class Cpu;
}

class Cpu : public QWidget
{
    Q_OBJECT

public:
    explicit Cpu(QWidget *parent = 0);
    ~Cpu();

    void setProgramCounter(const int);
    int getProgramCounter() const;
    void setProgramHex(QString);
    const QString getOpcode();
    int get8BitConst();
    int get16BitConst();
    bool getMode();
    void setMode(bool);
    MemoryBank * getMemory();

signals:

public slots:
    void jumpTriggered(const int);
    void loadROM(const QString);

private slots:
    void programCounterChanged(const int);
    void nextInstructionButtonPressed();
    void programCounterLineEditTextChanged(QString);
    void run();
    void pause();
    void runThread();

private:
    void formatProgramHex() const;

    Ui::Cpu *ui;

    std::thread _runningThread;
    bool _isRunning;
    RegisterBank * _regBank;
    MemoryBank * _memory;
    OpcodeDecoder * _opDecoder;
    bool _retrievedConst, _retrievedConstWidth; //retrievedConstWidth 0 for 8bit 1 for 16bit
    bool _mode; //mode 0 for 8bit 1 for 16bit
};

#endif // CPU_H
