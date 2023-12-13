#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QProcess>
#include <QMessageBox>
#include <QTextCodec>
#include <thread>
#include <future>
#include "converter.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


#define NOT_SELECTED 0
#define CONVERT_264 1
#define CONVERT_265 2

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString file;
    QString file_short;
    void handleResults();
    void startWorkInAThread(QString ext);
    void static ConvertVideo(QString file , QString outputString);
    QFutureWatcher<int> *watcher;
public slots:
    void ConvertComplete();
private slots:

    void on_OpenFile_clicked();

    void on_Convert_clicked();

private:
    Ui::MainWindow *ui;
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
};
#endif // MAINWINDOW_H
