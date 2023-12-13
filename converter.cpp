#include "converter.h"

ConverterExt::ConverterExt(){

}


QFuture<int> ConverterExt::ExecuteCommand264(QString file , QString outputString){

    QFuture<int> future = QtConcurrent::run(
        &ConverterExt::PerformTask264, this , file , outputString);

    return future;
}

QFuture<int> ConverterExt::ExecuteCommand265(QString file , QString outputString){

    QFuture<int> future = QtConcurrent::run(
        &ConverterExt::PerformTask265, this , file , outputString);

    return future;
}

int ConverterExt::PerformTask265(QString file , QString outputString){

    QProcess process;
    process.setWorkingDirectory( QDir::currentPath());
    process.start("./ffmpeg" , QStringList() << "-i"  << file << "-c:v" << "libx265" << "-vtag" << "hvc1" << outputString);
    process.waitForFinished(-1);
    return 1;
}


int ConverterExt::PerformTask264(QString file , QString outputString){

    QProcess process;
    process.setWorkingDirectory( QDir::currentPath());
    process.start("./ffmpeg" , QStringList() << "-i"  << file  << outputString);
    process.waitForFinished(-1);
    return 1;
}
