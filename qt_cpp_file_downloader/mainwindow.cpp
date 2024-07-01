#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QDebug>
#include <QProgressDialog>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->Download_Button, &QPushButton::clicked, this, &MainWindow::startDownload);
}

void MainWindow::startDownload()
{
    QString url = ui->downoadAdress_text->text();
    if (url.isEmpty()) {
        qDebug() << "Download link is empty";
        return;
    }

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    request.setUrl(QUrl(url));

    QNetworkReply *reply = manager->get(request);

    QProgressDialog *progressDialog = new QProgressDialog("Downloading file...", "Abort", 0, 100, this);
    progressDialog->setWindowModality(Qt::WindowModal);

    connect(reply, &QNetworkReply::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal) {
        progressDialog->setMaximum(bytesTotal);
        progressDialog->setValue(bytesReceived);

        if (progressDialog->wasCanceled()) {
            reply->abort();
            return;
        }
    });

    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();
            QFile file("downloaded_file.mp3");
            if (file.open(QFile::WriteOnly)) {
                file.write(data);
                file.close();
                qDebug() << "File downloaded successfully";
            } else {
                qDebug() << "Error saving file";
            }
        } else {
            qDebug() << "Error downloading file: " << reply->errorString();
        }

        progressDialog->close();
        reply->deleteLater();
        manager->deleteLater();
    });

    connect(progressDialog, &QProgressDialog::canceled, [=]() {
        reply->abort();
    });

    progressDialog->show();

    // Clean up the dialog and timer after it's closed
    connect(progressDialog, &QProgressDialog::destroyed, [=]() {
        reply->deleteLater();
        manager->deleteLater();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

