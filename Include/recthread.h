#ifndef RECTHREAD_H
#define RECTHREAD_H
#include<QObject>
#include<string>
#include<QJsonArray>
#include<zmq.h>
#include<QDebug>
#include<QVector>
#include<QPoint>
#include<QCursor>
#include<QJsonDocument>
#include<QJsonObject>
#include<QDesktopWidget>
#include<QMetaType>
#include<QThread>

#include"signals.h"
#include "Include/mysm.h"
#include "Include/sap.h"
#include "Include/guess.h"
#include "Include/showtrack.h"
#include "Include/Controller.h"


extern QString uiID;
extern int click_x;
extern int click_y;
extern int hisVideo;

class RecThread : public Signals
{
    Q_OBJECT
private:
    void *subscriber;
    QJsonObject commandJson;
    Guess G;

public:
    RecThread(MainWidget *mw, MapForm *mf, SettingWidget *sw, ShowTrack *st):Signals (mw, mf, sw, st)
    {
        connect(this, SIGNAL(deliverMesssage(QJsonObject)), st, SLOT(updatePos(QJsonObject)));
    }
    ~RecThread();

    //命令解析函数
    QString eyeParse(int lX, int lY, QJsonObject rootObj, QString logicId);
    void moveCursor(int aX, int aY, QJsonObject rootObj);
    bool commandParse(QJsonObject commandJson, QVector<QString>&para, QString curControl, QJsonObject rootObj, QString logicId);
    vector<pair<int,int>> v1,v2;
    void show(int a_x, int a_y, QString id);
    bool release();
    bool conflict(vector<pair<int, int>>Clicks, vector<pair<int, int>>Gazes, POINT p, int a, int b, int c, int d, int e, int f);
    QVector<QString> curController1;
    QVector<QString> curController2;
    QVector<QString> curController3;

signals:
    void signal_recievedMsg();
    void deliverMesssage(QJsonObject messageObject);
public slots:
    void slot_runRecievedMsg();
    void slot_recvPoint(QPoint p);

};


#endif // RECTHREAD_H
