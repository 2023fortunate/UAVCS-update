#ifndef FILETHREAD_H
#define FILETHREAD_H

#include<QObject>
#include<string>
#include<QDebug>
#include<QVector>

#include<QCursor>
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>
#include<QDesktopWidget>
#include<CSSCComboBox.h>

#include"Include/signals.h"
#include "MapForm.h"
#include "MainWidget.h"
#include "SettingWidget.h"
#include "showtrack.h"


extern QString uiID;
extern int hisVideo;
extern int uav_state;
extern double his_sudu;
extern int restart;
extern int stopThread;
extern qint64 timelapse;
class FileThread : public Signals
{
    Q_OBJECT
private:

public:
    ShowTrack *showTrack;
    MainWidget *mainWidget;
    MapForm *mapForm;
    SettingWidget *settingWidget;

    FileThread(MainWidget *mw, MapForm *mf, SettingWidget *sw, ShowTrack *st):Signals (mw, mf, sw, st)
    {    
        mainWidget = mw;
        mapForm = mf;
        settingWidget = sw;
        showTrack = st;
        // 线程结束后发送信号，对结果进行处理
        //设置界面
        connect(this, SIGNAL(sentUAVMainData(QJsonObject)), mainWidget, SLOT(setUAVMainData(QJsonObject)), Qt::QueuedConnection);
        connect(this, SIGNAL(RefreshUAV(int)), mainWidget, SLOT(changeIndex(int)), Qt::QueuedConnection);

        connect(this, SIGNAL(resultReady()), mapForm, SLOT(handleResults()), Qt::QueuedConnection);
        //侦察机视频
        connect(this, SIGNAL(sentUAVImg(QPixmap)), mapForm, SLOT(setUAVImg(QPixmap)), Qt::QueuedConnection);
        //地图界面
        connect(this, SIGNAL(sentUAVData(QJsonArray)), mapForm, SLOT(setUAVData(QJsonArray)), Qt::QueuedConnection);

        connect(this, SIGNAL(RefreshUAV(int)), settingWidget, SLOT(RefreshWindow(int)), Qt::QueuedConnection);
        //视频界面
        connect(this, SIGNAL(sentUAVName(QStringList)), settingWidget, SLOT(setUAVName(QStringList)), Qt::QueuedConnection);
        connect(this, SIGNAL(sentData(QJsonObject)), settingWidget, SLOT(setData(QJsonObject)), Qt::QueuedConnection);
        connect(this, SIGNAL(sentData1(QJsonObject)), settingWidget, SLOT(setData1(QJsonObject)), Qt::QueuedConnection);
        connect(this, SIGNAL(sentData2(QJsonObject)), settingWidget, SLOT(setData2(QJsonObject)), Qt::QueuedConnection);
        connect(this, SIGNAL(sentData3(QJsonObject)), settingWidget, SLOT(setData3(QJsonObject)), Qt::QueuedConnection);
        connect(this, SIGNAL(sentImg(QPixmap,QString,int)), settingWidget, SLOT(setImage(QPixmap,QString,int)), Qt::QueuedConnection);
        connect(this, SIGNAL(sentImg1(QPixmap,QString,int)), settingWidget, SLOT(setImage1(QPixmap,QString,int)), Qt::QueuedConnection);
        connect(this, SIGNAL(sentImg2(QPixmap,QString,int)), settingWidget, SLOT(setImage2(QPixmap,QString,int)), Qt::QueuedConnection);
        connect(this, SIGNAL(sentImg3(QPixmap,QString,int)), settingWidget, SLOT(setImage3(QPixmap,QString,int)), Qt::QueuedConnection);
    }
    ~FileThread();
    int sumOfCount(int t1,int t2,int t3,int t4,int t5,int t6,int t7);
    qint64 findMin(qint64 t1,qint64 t2,qint64 t3,qint64 t4,qint64 t5,qint64 t6,qint64 t7);
    qint64 findMax(qint64 t1,qint64 t2,qint64 t3,qint64 t4,qint64 t5,qint64 t6,qint64 t7);

    int count1 = 0;
    int count21 = 0;
    int count22 = 0;
    int count31 = 0;
    int count32 = 0;
    int count33 = 0;
    int count34 = 0;

    int rootSize1 = 0;
    int rootSize21 = 0;
    int rootSize22 = 0;
    int rootSize31 = 0;
    int rootSize32 = 0;
    int rootSize33 = 0;
    int rootSize34 = 0;

    qint64 time1;
    qint64 time21;
    qint64 time22;
    qint64 time31;
    qint64 time32;
    qint64 time33;
    qint64 time34;
    qint64 maxtime1;
    qint64 maxtime21;
    qint64 maxtime22;
    qint64 maxtime31;
    qint64 maxtime32;
    qint64 maxtime33;
    qint64 maxtime34;
    QVector<qint64> minTime={0,0};
    qint64 minTime1;
    qint64 maxTime;
    qint64 timeLength;
    qint64 timelapse1;
    QVector<int> sigTime={0,0,0,0,0,0,0};

signals:
    void resultReady();  // 线程完成工作时发送的信号
    void sentUAVMainData(QJsonObject uav);
    void sentUAVImg(QPixmap pixmap);
    void sentUAVData(QJsonArray uav);
    void RefreshUAV(int num);
    void sentData(QJsonObject uav);
    void sentData1(QJsonObject uav);
    void sentData2(QJsonObject uav);
    void sentData3(QJsonObject uav);
    void sentImg(QPixmap pixmap,QString uav_name,int index);
    void sentImg1(QPixmap pixmap,QString uav_name,int index);
    void sentImg2(QPixmap pixmap,QString uav_name,int index);
    void sentImg3(QPixmap pixmap,QString uav_name,int index);
    void sentUAVName(QStringList list);

public slots:
    void doWork();


};

#endif // FILETHREAD_H
