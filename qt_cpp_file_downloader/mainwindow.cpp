#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QDebug>
#include <QProgressDialog>
#include <QTimer>
#include <QProcess>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->Download_Button, &QPushButton::clicked, this, &MainWindow::checkInternetAndStartDownload);

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::BrowseFileDialog);
}

void MainWindow::BrowseFileDialog()
{
    QString directory =
    QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this, tr("Find Files"), QDir::currentPath()));

    if (!directory.isEmpty()) {
        QDir dir(directory);
        QStringList files = dir.entryList(QDir::Files);

        foreach (const QString &file, files)
        {
            qDebug() << "File found: " << file;
        }
    }
}

void MainWindow::checkInternetAndStartDownload()
{
    QProcess process;
    process.start("ping", QStringList() << "google.com");
    process.waitForFinished();

    QByteArray result = process.readAllStandardOutput();
    QString resultString = QString::fromUtf8(result);

    if (resultString.contains("Reply from")) {
        qDebug() << "Internet connection is available. Starting download...";
        startDownload();
    } else {
        qDebug() << "No internet connection available.";
    }
}

void MainWindow::startDownload()
{
    // Get URL from textbox
    QString url = ui->downoadAdress_text->text();

    // check if URL is null and empty
    if (url.isEmpty()) {
        qDebug() << "Download link is empty";
        return;
    }

    // consider manager variable to check request from internet
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    request.setUrl(QUrl(url));

    // get reply of manager from internet
    QNetworkReply *reply = manager->get(request);
    // create dialog windows
    QProgressDialog *progressDialog = new QProgressDialog("Downloading file...", "Abort", 0, 100, this);
    progressDialog->setWindowModality(Qt::WindowModal);

    // connect Progressbar to reply
    connect(reply, &QNetworkReply::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal) {
        /* set maximum and bytesToReceive */
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

