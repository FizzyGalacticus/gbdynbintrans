#ifndef REGISTERBANK_H
#define REGISTERBANK_H

#include <QWidget>

namespace Ui {
class RegisterBank;
}

class RegisterBank : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterBank(QWidget *parent = 0);
    ~RegisterBank();

signals:
    void valueChanged();
    void stackPointerPositionChanged(const int);

private:
    Ui::RegisterBank *ui;
    __int8 _A, _B, _C, _D, _E, _H, _L, _flags;
    __int16 _PC, _SP;
};

#endif // REGISTERBANK_H
