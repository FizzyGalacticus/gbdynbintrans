/* CS 441 - System Architecture
 * Project #2 - gbdynbintrans - main.cpp
 * Bucky Frost & Dustin Dodson
 */

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
