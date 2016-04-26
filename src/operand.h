/* CS 441 - System Architecture
 * Project #2 - gbdynbintrans - operand.h
 * Bucky Frost & Dustin Dodson
 *
 * This class is to abstract the method
 * of getting a value, whether the value
 * originates from a register or be a
 * constant, this allows us to perform
 * the same operation without worrying
 * about it.
 */

#ifndef OPERAND_H
#define OPERAND_H

#include <QObject>

class Operand : public QObject
{
    Q_OBJECT
public slots:

signals:

public:
    Operand(QObject *parent=0);

    virtual void setValue(const int) = 0;
    virtual int getVal() = 0;
    virtual QString getType() = 0;

private:

};

#endif // OPERAND_H
