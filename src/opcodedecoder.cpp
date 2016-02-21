#include "opcodedecoder.h"
#include "ui_opcodedecoder.h"
#include <iostream>
using std::cout;
using std::endl;
#include <QFile>

OpcodeDecoder::OpcodeDecoder(QString filename, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OpcodeDecoder),
    _opcodes()
{
    ui->setupUi(this);

    QFile * jsonFile = new QFile(filename);

    jsonFile->open(QFile::ReadOnly);
    string fileContents = jsonFile->readAll().toStdString();
    jsonFile->close();

    Json::Value root;   // will contains the root value after parsing.
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(fileContents.c_str(), root );

    if(!parsingSuccessful) {
        // report to the user the failure and their locations in the document.
        QString err = "Failed to parse configuration\n";
        err += QString(reader.getFormatedErrorMessages().c_str());
        this->ui->instructionLabel->setText(err);
    } else {
        Json::Value unprefixed = root["unprefixed"];

        for(auto i = unprefixed.begin(); i != unprefixed.end(); i++) {
            //add to map here
        }
    }
}

OpcodeDecoder::~OpcodeDecoder()
{
    delete ui;
}
