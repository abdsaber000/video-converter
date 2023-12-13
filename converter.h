#ifndef CONVERTER_H
#define CONVERTER_H

#include <QObject>
#include <QtConcurrent>
#include <QFuture>
#include <QProcess>
#include "mainwindow.h"
class ConverterExt : public QObject
{
    Q_OBJECT;
public:
    ConverterExt();
    QFuture<int> ExecuteCommand264(QString file , QString outputString);
    QFuture<int> ExecuteCommand265(QString file , QString outputString);
private :
    int PerformTask265(QString file , QString outputString);
    int PerformTask264(QString file , QString outputString);
};



#endif // CONVERTER_H
