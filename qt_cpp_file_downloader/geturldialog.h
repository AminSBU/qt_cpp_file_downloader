#ifndef GETURLDIALOG_H
#define GETURLDIALOG_H

#include <QDialog>

namespace Ui {
class getURLDialog;
}

class getURLDialog : public QDialog
{
    Q_OBJECT

public:
    explicit getURLDialog(QWidget *parent = nullptr);
    ~getURLDialog();

private:
    Ui::getURLDialog *ui;
};

#endif // GETURLDIALOG_H
