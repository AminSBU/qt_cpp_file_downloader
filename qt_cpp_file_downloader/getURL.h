#ifndef GETURL_H
#define GETURL_H
#include <QMainWindow>
#include <QWidget>
#include "ui_getURL.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class getURL : public QWidget
{
    Q_OBJECT

public:
    getURL(QWidget *parent = nullptr);
    ~getURL();

    void getURLDialog();

private:
    Ui::getURL *ui;
};
#endif // GETURL_H
