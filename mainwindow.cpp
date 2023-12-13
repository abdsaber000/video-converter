#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QDir dir;
    dir.mkdir("output");
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    qDebug() << "I'm here";
    system("taskkill/im ffmpeg.exe -F");
    qDebug() << "All Done.";
    delete ui;
}



void MainWindow::on_OpenFile_clicked()
{
    ui->Status->setText("لم يتم البدء");
    QString fileName = QFileDialog::getOpenFileName(this , "open the file");

    QString fileShortName = "";
    for(int i = fileName.size() - 1; i >= 0; i--){
        if(fileName[i] == QChar('/')){
            break;
        }
        fileShortName.push_back(fileName[i]);
    }

    std::reverse(fileShortName.begin() , fileShortName.end());
    file = fileName;
    //QString fileShortName = extractShortName(fileName);
    ui->fileName->setText(fileShortName);
    file_short = fileShortName;
}


void MainWindow::ConvertVideo(QString file, QString outputString){
    QProcess process;
    process.setWorkingDirectory( QDir::currentPath());
    process.start("./ffmpeg" , QStringList() << "-i"  << file << "-c:v" << "libx265" << "-vtag" << "hvc1" << outputString);
    process.waitForFinished(-1);

}

void MainWindow::on_Convert_clicked()
{

    qDebug() << QDir::currentPath();
    QString ext = ui->textEdit->toPlainText();
    int selectedEncoder = NOT_SELECTED;
    if(ui->B264->isCheckable()){
        selectedEncoder = CONVERT_264;
    }

    if(ui->B265->isCheckable()){
        selectedEncoder = CONVERT_265;
    }
    if(ext.isEmpty()){
        QString error = "خطأ";
        QString errorMessage = "لا يوجد صيغة";
        QMessageBox::information(this ,error , errorMessage);
        return;
    }

    if(file.isEmpty()){
        QString error = "خطأ";
        QString errorMessage = "لم يتم ادخال ملف";
        QMessageBox::information(this ,error , errorMessage);
        return;
    }

    if(selectedEncoder == NOT_SELECTED){
        QString error = "خطأ";
        QString errorMessage = "لم يتم تحديد نوع التشفير";
        QMessageBox::information(this ,error , errorMessage);
        return;
    }

    QWidget::setEnabled(false);

    QString outputString  = "./output/" + file_short + "." + ext;
    ConverterExt conv;
    QFuture<int> future;

    if(selectedEncoder == CONVERT_264)
        future = conv.ExecuteCommand264(file , outputString);
    else
        future = conv.ExecuteCommand265(file , outputString);

    watcher = new QFutureWatcher<int>(this);
    connect(watcher , SIGNAL(finished()) , this , SLOT(ConvertComplete()));
    watcher->setFuture(future);
    ui->Status->setText("جاري التحويل");

}


void MainWindow::ConvertComplete(){
    QMessageBox::information(this ,"done" , "File converted");
    ui->Status->setText("اكتمل");
    QWidget::setEnabled(true);
}


