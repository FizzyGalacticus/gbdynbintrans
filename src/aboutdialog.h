/* CS 441 - System Architecture
 * Project #2 - gbdynbintrans - aboutdialog.h
 * Bucky Frost & Dustin Dodson
 *
 * This class is meant only to provide basic
 * information within the application about
 * its creators.
 */

#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT

public slots:
    void okayPushButtonClicked();

public:
    explicit AboutDialog(QWidget *parent = 0);
    ~AboutDialog();

private:
    Ui::AboutDialog *ui;
};

#endif // ABOUTDIALOG_H
