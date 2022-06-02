#ifndef RECVCOMMANDTHREAD_H
#define RECVCOMMANDTHREAD_H

#include <QProcess>
#include <QCursor>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

class RecvCommandThread : public QObject
{
    Q_OBJECT
public:
    explicit RecvCommandThread(QObject *parent=0);
    ~RecvCommandThread();

private slots:
    void onRecvCmdFromEMP();

private:
    QProcess eyeMoveProcess;

};

#endif // RECVCOMMANDTHREAD_H
