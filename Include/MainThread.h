#ifndef MAINTHREAD_H
#define MAINTHREAD_H

#include<QObject>
#include<string>
#include<QJsonArray>
#include<zmq.h>
#include<QDebug>
#include<QVector>
#include<QCursor>
#include<QJsonDocument>
#include<QJsonObject>
#include<QDesktopWidget>
#include <string>
#include "string.h"


#include "Include/signals.h"
#include "Include/GetData.h"
#include "Include/GetVedio.h"
#include "Include/MapDataThread.h"
#include "Include/MapForm.h"

extern QString uiID;
extern int start;
extern int finish1;//围捕结束，开始写文件
extern int state;
extern int hisVideo;

class MainThread : public Signals
{
    Q_OBJECT
private:
    void *subscriber;
    QJsonObject commandJson;
    std::map<std::string,size_t> pr;
    std::string curr_name;
public:
    MainThread(MainWidget *mw, MapForm *mf, SettingWidget *sw, ShowTrack *st):Signals (mw, mf, sw, st)
    {
        connect(this, SIGNAL(sentUAVMainData(QJsonObject)), mw, SLOT(setUAVMainData(QJsonObject)));
    }
    ~MainThread();
    QJsonObject objFinal1;
    int count1 = 0;
    int finish2 = 0;//文件写入结束
    bool removeFolderContent1(const QString &folderDir);
    //清除jsonObject对象内容
    void clearJsonObject1(QJsonObject &object);
signals:
    void sentUAVMainData(QJsonObject uav);

public slots:
    void slot_recieveMainMsg();

};

#endif // MAINTHREAD_H
