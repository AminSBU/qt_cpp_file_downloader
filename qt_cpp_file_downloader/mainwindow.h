#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "getURL.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void startDownload();
    void checkInternetAndStartDownload();
    void BrowseFileDialog();
    void getURLDialog();

private:
    Ui::MainWindow *ui;
    getURL *getURL;
};
#endif // MAINWINDOW_H
