#ifndef AIRTHREAD_H
#define AIRTHREAD_H

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
#include <string>
#include "string.h"

#include "Include/signals.h"
#include "Include/GetData.h"
#include "Include/GetVedio.h"
#include "Include/MapDataThread.h"
#include "Include/MapForm.h"

extern QString uiID;
extern int start;
extern int finish1;
extern int state;
extern int hisVideo;
class AirThread : public Signals
{
    Q_OBJECT
private:
    void *subscriber;
    QJsonObject commandJson;
    CSSCComboBox* cBoxs[4];
    std::vector<GV>gds;
    std::map<std::string,size_t> pr;
    int idx;
    std::string curr_name;
public:
//    RecThread(void *rq, QDesktopWidget *dt);
    AirThread(MainWidget *mw, MapForm *mf, SettingWidget *sw, ShowTrack *st,
              CSSCComboBox* B1=NULL,CSSCComboBox* B2=NULL,CSSCComboBox* B3=NULL,CSSCComboBox* B4=NULL,int idx_=0):Signals (mw, mf, sw, st)
    {
        connect(this, SIGNAL(sentUAVName(QStringList)), sw, SLOT(setUAVName(QStringList)));
        connect(this, SIGNAL(sentData(QJsonObject)), sw, SLOT(setData(QJsonObject)));
        connect(this, SIGNAL(sentData1(QJsonObject)), sw, SLOT(setData1(QJsonObject)));
        connect(this, SIGNAL(sentData2(QJsonObject)), sw, SLOT(setData2(QJsonObject)));
        connect(this, SIGNAL(sentData3(QJsonObject)), sw, SLOT(setData3(QJsonObject)));
        connect(this, SIGNAL(sentImg(QPixmap,QString,int)), sw, SLOT(setImage(QPixmap,QString,int)));
        connect(this, SIGNAL(sentImg1(QPixmap,QString,int)), sw, SLOT(setImage1(QPixmap,QString,int)));
        connect(this, SIGNAL(sentImg2(QPixmap,QString,int)), sw, SLOT(setImage2(QPixmap,QString,int)));
        connect(this, SIGNAL(sentImg3(QPixmap,QString,int)), sw, SLOT(setImage3(QPixmap,QString,int)));
    //    connect(this, SIGNAL(RefreshUAV(int)), sw, SLOT(RefreshWindow(int)));
        cBoxs[0] = B1;
        cBoxs[1] = B2;
        cBoxs[2] = B3;
        cBoxs[3] = B4;
        idx = idx_;
    //    desktop = dt;

    //    test
    //    qDebug() <<"emit signal!";
    //    slot_runRecievedMsg();
    //    qDebug() <<"emited signal!";
    }
    ~AirThread();
    QJsonObject objFinal3;
    QJsonObject objFinal31;
    QJsonObject objFinal32;
    QJsonObject objFinal33;
    QJsonObject objFinal34;
    QVector<int> count3 = {0,0,0,0};
    int count31 = 0;
    QVector<int> finish2 = {0,0,0,0};
    int finish3 = 0;

    bool removeFolderContent3(const QString &folderDir);
    //清除jsonObject对象内容
    void clearJsonObject3(QJsonObject &object);

//    命令解析函数
//    char *s_recv(void *socket);
//    char *s_recv(void *socket, int flag);

//    QDesktopWidget *desktop;
//    Signals *signal = new Signals();

signals:
    //void signal_recievedMsg();
    void sentData(QJsonObject uav);
    void sentData1(QJsonObject uav);
    void sentData2(QJsonObject uav);
    void sentData3(QJsonObject uav);
    void sentImg(QPixmap pixmap,QString uav_name,int index);
    void sentImg1(QPixmap pixmap,QString uav_name,int index);
    void sentImg2(QPixmap pixmap,QString uav_name,int index);
    void sentImg3(QPixmap pixmap,QString uav_name,int index);
    void sentUAVName(QStringList list);
//    void RefreshUAV(int num);

public slots:
    void slot_recieveAirSimMsg();

};

#endif // AIRTHREAD_H
