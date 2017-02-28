#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

#include <QDirIterator>
#include <QTextStream>
#include <QFile>
#include <QCryptographicHash>
#include <QByteArray>

#define MAX_HEADER_HASH_SIZE 3500

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //clusteringImages("/media/user/disk1/photoParser/detect");
    //QPixmap image("C:\\Users\\admin\\Documents\\1.jpg");
    this->myButton = (QPushButton*) this->findChild<QWidget*>("pushButton");
    this->pathReader = (QLineEdit*) this->findChild<QWidget*>("lineEdit");
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QVector<QString> MainWindow::filesLoadFromPath(const QString base, QVector<QString> extPattern)
{
    QVector<QString> result;

    QDirIterator it(base, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString path = it.filePath();

        for (auto i : extPattern)
            if (path.endsWith(i, Qt::CaseInsensitive))
                result.push_back(path);
        it.next();
    }
    return result;
}

QString MainWindow::getHash(QString path) {
    QCryptographicHash hasher(QCryptographicHash::Md5);

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) return "";
    QByteArray blob = file.read(MAX_HEADER_HASH_SIZE);

    if (blob.isEmpty()) return "";

    hasher.addData(blob);

    return QString(hasher.result().toHex());
}

void MainWindow::clusteringImages(const QString base)
{
    QVector<QString> patterns;
    patterns.push_back(".h");
    patterns.push_back(".cpp");

    QVector<QString> rawfiles = filesLoadFromPath(base, patterns);
    if (rawfiles.isEmpty()) return;

    QFile data("output.txt");
    if (!data.open(QFile::WriteOnly | QFile::Truncate)) {
        std::cout << "cannot open file" << std::endl;
        return;
    }
    QTextStream out(&data);
    for (auto i : rawfiles)
    {
        out << getHash(i) << " " << i << endl;
        files[getHash(i)].push_back(i);
    }
}

void MainWindow::on_pushButton_clicked()
{
    clusteringImages("/media/user/disk1/photoParser/detect");
}
