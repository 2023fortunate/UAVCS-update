#include "Include/RecvCommandThread.h"

RecvCommandThread::RecvCommandThread(QObject *parent):QObject(parent)
{
    connect(&eyeMoveProcess,SIGNAL(readyRead()),this,SLOT(onRecvCmdFromEMP()));
//    QString program = "D:\\QtProject\\build-untitled3-Desktop_Qt_5_6_3_MinGW_32bit-Release\\release\\untitled3.exe";
//    eyeMoveProcess.start(program);
}

void RecvCommandThread::onRecvCmdFromEMP()
{
    QString commandStr =  QString(eyeMoveProcess.readAll());
    qDebug() << commandStr;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(commandStr.toLocal8Bit().data());
    QJsonObject commandJson = jsonDoc.object();
    if(commandJson.value("command").toString() == "MoveCursor"){
        int x = commandJson.value("x").toInt();
        int y = commandJson.value("y").toInt();
        QPoint cursorPos(x,y);
        QCursor::setPos(cursorPos);
    }
}

RecvCommandThread::~RecvCommandThread()
{

}
