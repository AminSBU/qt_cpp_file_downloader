#include "geturldialog.h"
#include "ui_geturldialog.h"

getURLDialog::getURLDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::getURLDialog)
{
    ui->setupUi(this);
}

getURLDialog::~getURLDialog()
{
    delete ui;
}
