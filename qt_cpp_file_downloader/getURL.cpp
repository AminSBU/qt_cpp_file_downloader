#include "getURL.h"
#include "ui_getURL.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QDebug>
#include <QProgressDialog>
#include <QTimer>
#include <QProcess>
#include <QFileDialog>

getURL::getURL(QWidget *parent)
    : QWidget(parent)
{
    Ui.setupUi(this);
}

void getURL::getURLDialog()
{

}
