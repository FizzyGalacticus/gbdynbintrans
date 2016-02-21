#ifndef PROGRAMCOUNTER_H
#define PROGRAMCOUNTER_H

#include <QWidget>

namespace Ui {
class ProgramCounter;
}

class ProgramCounter : public QWidget
{
    Q_OBJECT

public:
    explicit ProgramCounter(QWidget *parent = 0);
    ~ProgramCounter();

    void setProgramCounter(const int);
    int getProgramCounter() const;
    void setText(QString);

public slots:
    void programCounterHasChanged(const int);

private:
    Ui::ProgramCounter *ui;

    __int16 _programCounter;
};

#endif // PROGRAMCOUNTER_H
