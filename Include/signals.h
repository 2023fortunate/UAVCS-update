#ifndef SIGNALS_H
#define SIGNALS_H

#include <QObject>
#include<string>
#include <QDebug>
#include<QJsonArray>
#include<QJsonObject>
#include <QStringList>
#include <QPixMap>
#include "MapForm.h"
#include "MainWidget.h"
#include "SettingWidget.h"
#include "showtrack.h"


class Signals;
// 定义函数指针数组
typedef void (Signals::*pFuns)(int, int);

class Signals : public QObject
{
    Q_OBJECT

signals:
    void nullSignal(int rdd1, int rdd2);

    //mainwidget
    void voiceIndex(int airID, int videoID);
//    void voicePattern(int patternID, int rdd2);
    void eyeHighShow(int index, int rdd2);

    void voiceAcclerate(int rdd1, int rdd2);
    void voiceDecelerate(int rdd1, int rdd2);
//    void voiceFreedom(int rdd1, int rdd2);
    //mainwidget新增
//    void changeMode(int airID, int modeID);


    //mapWidget
    void handEnlargeMap(int rdd1, int rdd2);
    void handDecreaseMap(int rdd1, int rdd2);
//    void voiceShowOrbit(int index, int rdd2);

    //新增
    void voiceEnlargeMap(int rdd1, int rdd2);
    void voiceDecreaseMap(int rdd1, int rdd2);
    void voiceSwitchMap(int rdd1, int rdd2);
    void voiceSwitchVideo(int rdd1, int rdd2);

    void handLeftMove(int offset, int rdd2);
    void handRightMove(int offset, int rdd2);
    void handUpMove(int offset, int rdd2);
    void handDownMove(int offset, int rdd2);


    //SettingWidget
//    void handBackPlay(int index, int rdd2);
//    void handRecoverPlay(int index, int rdd2);
    void handEnlargeVideo(int index, int rdd2);
    void handRecoverVideo(int rdd1, int rdd2);
    //新增
    void voiceEnlargeVideo(int index, int rdd2);
    void voiceRecoverVideo(int rdd1, int rdd2);
    //弹框
    void voicePopWindow(int rdd1, int rdd2);
    void handEnlargeImage(int rdd1, int rdd2);
    void handDecreaseImage(int rdd1, int rdd2);
//    void voiceShowOrbit(int index, int rdd2);

    void handLeftImage(int offset, int rdd2);
    void handRightImage(int offset, int rdd2);

    void popWindowRecover(int rdd1, int rdd2);

    void history(int rdd1, int rdd2);

    void voiceShowOrbit(int rdd1, int rdd2);

    void voiceAllVideo(int rdd1, int rdd2);

    void voiceSudu(int rdd1, int rdd2);

    void hisFinish(int rdd1, int rdd2);

    void timeShift(int rdd1, int rdd2);
//    void resultReady(const int result);  // 线程完成工作时发送的信号
//    void sentUAVMainData(QJsonObject uav);
//    void sentUAVImg(QPixmap pixmap);
//    void sentUAVData(QJsonArray uav);
//    void RefreshUAV(int num);
//    void sentData(QJsonObject uav);
//    void sentData1(QJsonObject uav);
//    void sentData2(QJsonObject uav);
//    void sentData3(QJsonObject uav);
//    void sentImg(QPixmap pixmap,QString uav_name,int index);
//    void sentImg1(QPixmap pixmap,QString uav_name,int index);
//    void sentImg2(QPixmap pixmap,QString uav_name,int index);
//    void sentImg3(QPixmap pixmap,QString uav_name,int index);
//    void sentUAVName(QStringList list);



public:
    int test = 5;

    ShowTrack *st;
    MainWidget *mainWidget;
    MapForm *mapForm;
    SettingWidget *settingWidget;

    pFuns signalFun[31] = {
        &Signals::nullSignal,

        //mainwidget
        &Signals::voiceIndex,
        &Signals::eyeHighShow,

        &Signals::voiceAcclerate,
        &Signals::voiceDecelerate,

        //mapWidget
        &Signals::handEnlargeMap,
        &Signals::handDecreaseMap,

        &Signals::voiceEnlargeMap,
        &Signals::voiceDecreaseMap,
        &Signals::voiceSwitchMap,
        &Signals::voiceSwitchVideo,

        &Signals::handLeftMove,
        &Signals::handRightMove,
        &Signals::handUpMove,
        &Signals::handDownMove,

        //SettingWidget
        &Signals::handEnlargeVideo,
        &Signals::handRecoverVideo,

        &Signals::voiceEnlargeVideo,
        &Signals::voiceRecoverVideo,
        //mainwidget新增
        &Signals::voicePopWindow,
        &Signals::handEnlargeImage,
        &Signals::handDecreaseImage,
        &Signals::handLeftImage,
        &Signals::handRightImage,
        &Signals::popWindowRecover,
        &Signals::history,
        &Signals::voiceShowOrbit,
        &Signals::voiceAllVideo,
        &Signals::voiceSudu,
        &Signals::hisFinish,
        &Signals::timeShift

    };

    Signals(MainWidget *mw, MapForm *mf, SettingWidget *sw, ShowTrack *showTrack)
    {
        mainWidget = mw;
        mapForm = mf;
        settingWidget = sw;
        st = showTrack;

        //mainWidget
        connect(this, SIGNAL(voiceIndex(int, int)), mainWidget, SLOT(showState(int)), Qt::QueuedConnection);
//        connect(this, SIGNAL(voicePattern(int, int)), mainWidget, SLOT(workPattern(int)), Qt::QueuedConnection);
        connect(this, SIGNAL(eyeHighShow(int, int)), mainWidget, SLOT(highShow(int)), Qt::QueuedConnection);

        connect(this, SIGNAL(voiceAcclerate(int, int)), mainWidget, SLOT(acclerate_v()), Qt::QueuedConnection);
        connect(this, SIGNAL(voiceDecelerate(int, int)), mainWidget, SLOT(decelerate_v()), Qt::QueuedConnection);
//        connect(this, SIGNAL(voiceFreedom(int, int)), mainWidget, SLOT(on_csscPushButton_13_clicked()), Qt::QueuedConnection);


        //mapForm
        connect(this, SIGNAL(handEnlargeMap(int, int)), mapForm, SLOT(mapEnlarge()), Qt::QueuedConnection);
        connect(this, SIGNAL(handDecreaseMap(int, int)), mapForm, SLOT(mapDecrease()), Qt::QueuedConnection);


        connect(this, SIGNAL(voiceEnlargeMap(int, int)), mapForm, SLOT(mapEnlarge()), Qt::QueuedConnection);
        connect(this, SIGNAL(voiceDecreaseMap(int, int)), mapForm, SLOT(mapDecrease()), Qt::QueuedConnection);
        connect(this, SIGNAL(voiceSwitchMap(int, int)), mapForm, SLOT(on_large_clicked()), Qt::QueuedConnection);
        connect(this, SIGNAL(voiceSwitchVideo(int, int)), mapForm, SLOT(on_large_clicked()), Qt::QueuedConnection);

        connect(this, SIGNAL(handLeftMove(int, int)), mapForm, SLOT(mapLeft(int)), Qt::QueuedConnection);
        connect(this, SIGNAL(handRightMove(int, int)), mapForm, SLOT(mapRight(int)), Qt::QueuedConnection);       
        connect(this, SIGNAL(handUpMove(int, int)), mapForm, SLOT(mapUp(int)), Qt::QueuedConnection);
        connect(this, SIGNAL(handDownMove(int, int)), mapForm, SLOT(mapDown(int)), Qt::QueuedConnection);



        //settingWidget
//        connect(this, SIGNAL(handBackPlay(int, int)), settingWidget, SLOT(backPlay(int)), Qt::QueuedConnection);
//        connect(this, SIGNAL(handRecoverPlay(int, int)), settingWidget, SLOT(recoverPlay(int)), Qt::QueuedConnection);
        connect(this, SIGNAL(handEnlargeVideo(int, int)), settingWidget, SLOT(enlargeOrFull(int)), Qt::QueuedConnection);
        connect(this, SIGNAL(handRecoverVideo(int, int)), settingWidget, SLOT(recoverFour1(int)), Qt::QueuedConnection);
        connect(this, SIGNAL(voiceEnlargeVideo(int, int)), settingWidget, SLOT(enlargeOrFull(int)), Qt::QueuedConnection);
        connect(this, SIGNAL(voiceRecoverVideo(int, int)), settingWidget, SLOT(recoverFour1(int)), Qt::QueuedConnection);

       //mainWidget新增
        //connect(this, SIGNAL(changeMode(int, int)), mainWidget, SLOT(modeChange(int,int)), Qt::QueuedConnection);
        connect(this, SIGNAL(voicePopWindow(int, int)), mainWidget, SLOT(popWindow(int, int)), Qt::QueuedConnection);
        connect(this, SIGNAL(handEnlargeImage(int, int)), mainWidget, SLOT(imageEnlarge()), Qt::QueuedConnection);
        connect(this, SIGNAL(handDecreaseImage(int, int)), mainWidget, SLOT(imageDecrease()), Qt::QueuedConnection);
        connect(this, SIGNAL(handLeftImage(int, int)), mainWidget, SLOT(imageLeft()), Qt::QueuedConnection);
        connect(this, SIGNAL(handRightImage(int, int)), mainWidget, SLOT(imageRight()), Qt::QueuedConnection);
        connect(this, SIGNAL(popWindowRecover(int, int)), mainWidget, SLOT(windowRecover()), Qt::QueuedConnection);
        connect(this, SIGNAL(history(int, int)), mapForm, SLOT(history(int,int)), Qt::QueuedConnection);
        connect(this, SIGNAL(history(int, int)), mainWidget, SLOT(showState1(int)), Qt::QueuedConnection);
        connect(this, SIGNAL(history(int, int)), settingWidget, SLOT(show_all(int)), Qt::QueuedConnection);
        connect(this, SIGNAL(voiceShowOrbit(int, int)), mapForm, SLOT(showOrbit(int)), Qt::QueuedConnection);
        connect(this, SIGNAL(voiceAllVideo(int, int)), settingWidget, SLOT(show_all(int)), Qt::QueuedConnection);
        connect(this, SIGNAL(voiceSudu(int, int)), mapForm, SLOT(sudu(int)), Qt::QueuedConnection);
        connect(this, SIGNAL(hisFinish(int, int)), mapForm, SLOT(handleResults()), Qt::QueuedConnection);
        connect(this, SIGNAL(timeShift(int, int)), mapForm, SLOT(shiftTime(int)), Qt::QueuedConnection);


    }
    ~Signals(){}
};

#endif // SIGNALS_H
