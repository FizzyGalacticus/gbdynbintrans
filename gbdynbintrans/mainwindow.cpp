#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _fileDialog(new QFileDialog),
    _filename("")
{
    ui->setupUi(this);

    connect(ui->actionOpen,SIGNAL(triggered(bool)),this, SLOT(openFileDialogTriggered()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
