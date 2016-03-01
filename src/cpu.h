#ifndef CPU_H
#define CPU_H

#include <QWidget>
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

signals:
    void programCounterHasChanged(const int);
    void programHexChanged();
    void opcodeChanged(const QString, RegisterBank *);

public slots:

private slots:
    void resetStyle();
    void nextInstructionButtonPressed();
    void programCounterLineEditTextChanged(QString);

private:
    QString formatProgramHex(const QString) const;

    Ui::Cpu *ui;

    __int16 _programCounter;
    QString _programHex;
    RegisterBank * _regBank;
    OpcodeDecoder * _opDecoder;
    bool _retrievedConst, _retrievedConstWidth; //retrievedConstWidth 0 for 8bit 1 for 16bit
};

#endif // CPU_H
