#ifndef OPCODEDECODER_H
#define OPCODEDECODER_H

#include <QWidget>
#include <unordered_map>
using std::unordered_map;
#include "json/json.h"
#include <string>
using std::string;

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
    unordered_map<string, Json::Value> _opcodes;
};

#endif // OPCODEDECODER_H
