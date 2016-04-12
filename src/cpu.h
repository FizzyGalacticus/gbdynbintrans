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

signals:
    void programCounterHasChanged(const int);
    void programHexChanged();
    void opcodeChanged(const QString, RegisterBank *);

public slots:
    void jumpTriggered(const int);

private slots:
    void resetStyle();
    void nextInstructionButtonPressed();
    void programCounterLineEditTextChanged(QString);
    void run();
    void pause();
    void runThread();

private:
    QString formatProgramHex(const QString) const;

    Ui::Cpu *ui;

    std::thread _runningThread;
    bool _isRunning;
    uint16_t _programCounter;
    QString _programHex;
    RegisterBank * _regBank;
    OpcodeDecoder * _opDecoder;
    bool _retrievedConst, _retrievedConstWidth; //retrievedConstWidth 0 for 8bit 1 for 16bit
    bool _mode; //mode 0 for 8bit 1 for 16bit
};

#endif // CPU_H
