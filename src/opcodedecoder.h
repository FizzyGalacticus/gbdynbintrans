#ifndef OPCODEDECODER_H
#define OPCODEDECODER_H

#include <QWidget>

namespace Ui {
class OpcodeDecoder;
}

class OpcodeDecoder : public QWidget
{
    Q_OBJECT

public:
    explicit OpcodeDecoder(QString filename, QWidget *parent = 0);
    ~OpcodeDecoder();

private:
    Ui::OpcodeDecoder *ui;
};

#endif // OPCODEDECODER_H
