/* CS 441 - System Architecture
 * Project #2 - gbdynbintrans - aboutdialog.cpp
 * Bucky Frost & Dustin Dodson
 */

#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    connect(ui->okayPushButton, SIGNAL(clicked(bool)), this, SLOT(okayPushButtonClicked()));
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::okayPushButtonClicked() {
    this->close();
}
