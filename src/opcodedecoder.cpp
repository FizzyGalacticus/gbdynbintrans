#include "opcodedecoder.h"
#include "ui_opcodedecoder.h"

OpcodeDecoder::OpcodeDecoder(QString filename, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OpcodeDecoder)
{
    ui->setupUi(this);
}

OpcodeDecoder::~OpcodeDecoder()
{
    delete ui;
}
