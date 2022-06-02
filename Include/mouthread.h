#ifndef MOUTHREAD_H
#define MOUTHREAD_H
#include<QObject>
#include<QString>
#include<QDebug>
#include<windows.h>
#include <QPoint>
#include <QThread>

extern QString uiID;

class MouThread : public QThread
{
    Q_OBJECT
public:
    explicit MouThread(QObject* parent = 0)
    {

    }
    ~MouThread();

protected:
    void run();
signals:
    void signal_Click(QPoint p);

public slots:
    void slot_runEvent();
};
#endif   //MOUTHREAD_H
