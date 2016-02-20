#include "registerbank.h"
#include "ui_registerbank.h"

RegisterBank::RegisterBank(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterBank)
{
    ui->setupUi(this);
}

RegisterBank::~RegisterBank()
{
    delete ui;
}
