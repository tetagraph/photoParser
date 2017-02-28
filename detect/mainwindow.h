#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMap>
#include <QString>
#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QVector<QString> filesLoadFromPath(const QString base, QVector<QString> extPattern);

    void clusteringImages(const QString base);

    QString getHash(QString path);
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    QPushButton * myButton;

    QLineEdit * pathReader;

    QMap<QString, QVector<QString>> files;
};

#endif // MAINWINDOW_H
