#ifndef REGISTER_H
#define REGISTER_H

#include <QObject>

class Register : public QObject
{
    Q_OBJECT
public slots:

signals:

public:
    explicit Register(QString name, QObject *parent = 0);

private:

};

#endif // REGISTER_H
