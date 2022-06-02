#ifndef MAPDATATHREAD_H
#define MAPDATATHREAD_H

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
#include<CSSCComboBox.h>

#include "string.h"
#include <string>

#include"Include/signals.h"
#include "Include/GetData.h"
#include "Include/GetVedio.h"
#include "Include/mapwidget.h"
#include "Include/MapForm.h"



extern QString uiID;
extern int start;
extern int finish1;
extern int state;
extern int finish4;//围捕结束，开始写文件
extern int hisVideo;


class MapDataThread : public Signals
{
    Q_OBJECT
private:
    void *subscriber;
    QJsonObject commandJson;
    std::vector<GV>gds;
    std::map<std::string,size_t> pr;
    std::string curr_name;
    MapWidget *mapWidget;
    CSSCComboBox* cBoxs[4];
    int idx;
    int first_find;
    int record[2]={0,0};
    int finish3 = 0;//发现敌机，巡航结束，进入围捕模式
    int count2 = 0;
    int finish2 = 0;//文件写入结束


public:
    MapDataThread(MainWidget *mw, MapForm *mf, SettingWidget *sw, ShowTrack *st):Signals (mw, mf, sw, st)
    {
        connect(this, SIGNAL(sentUAVData(QJsonArray)), mf, SLOT(setUAVData(QJsonArray)));
        connect(this, SIGNAL(RefreshUAV(int)), sw, SLOT(RefreshWindow(int)));
        connect(this, SIGNAL(RefreshUAV(int)), mw, SLOT(changeIndex(int)));
    }
    ~MapDataThread();
    //清除jsonObject对象内容
    void clearJsonObject(QJsonObject &object);

    QJsonObject objFinal2;
    QJsonValue drone_x;
    QJsonValue drone_y;

signals:

    void sentUAVData(QJsonArray uav);
    void RefreshUAV(int num);

public slots:
    void slot_recieveMapDataMsg();


};

#endif // MAPDATATHREAD_H
