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
    void setProgramHex(QString);

signals:
    void programCounterHasChanged(const int);

public slots:


private:
    Ui::ProgramCounter *ui;

    __int16 _programCounter;
    QString _programHex;
};

#endif // PROGRAMCOUNTER_H
