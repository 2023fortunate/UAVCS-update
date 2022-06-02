#include "Include/MainWidget.h"
#include "Include/MapForm.h"
#include "Include/SettingWidget.h"
#include "Include/signals.h"
#include <QApplication>  //包含一个应用程序类对象
#include <QThread>
#include <zmq.h>
#include <QObject>
#include <Include/RecThread.h>
#include <Include/FileThread.h>
#include <Include/mouthread.h>
#include <Include/MapThread.h>
#include <Include/MapDataThread.h>
#include <Include/MainThread.h>
#include <Include/AirThread.h>
#include <Include/jsonwrite.h>
#include <Include/showtrack.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QDebug>
//#include <Include/GetData.h>

using namespace cv;

bool G_add2 = false;
bool G_jian2 = false;

int pointX;
int pointY;
QString uiID;
QString commandType;

int click_x;
int click_y;

double G_px1;
double G_px2;
double G_px3;
double G_px4;
double G_py1;
double G_py2;
double G_py3;
double G_py4;
QThread* thread10;
//main程序入口，argc命令行变量的数量，argv命令行变量的数组
int main(int argc, char *argv[])
{
    //Mat sb = cv::imread("D:/UAVCS-update/照片/1.jpg");
    //imshow("sb",sb);
    //a应用程序对象，在Qt中，应用程序对象，有且仅有一个
    QApplication a(argc, argv);


//    QDesktopWidget *desktop = QApplication::desktop();
    // 显示当前显示器的数量
//    int screenNum = desktop->numScreens();
//    qDebug() << "screen_num" << screenNum;
//    qDebug() << "screen_num";

//实例化窗口对象，继承Qwidget
    MainWidget *mainWidget = new MainWidget();
    MapForm *mapForm = new MapForm();
    SettingWidget *settingWidget = new SettingWidget();
    ShowTrack *st = new ShowTrack(mainWidget, mapForm, settingWidget);


//窗口对象，默认不会显示，必须要调用show方法显示窗口
    mainWidget->show();

    mapForm->show();

    settingWidget->showMaximized();

//    GD g;
//    g.initA("192.168.1.105");
//    std::cout<<g.AGet()<<std::endl;
    // 生成json文件
    JsonWrite jw(mainWidget, mapForm, settingWidget);

//    //将三个界面一次设置到主机，显示器1，显示器2上
//    mainWidget->setGeometry(desktop->screenGeometry(2));
//    mapForm->setGeometry(desktop->screenGeometry(0));
//    settingWidget->setGeometry(desktop->screenGeometry(1));

    RecThread *recvThread = new RecThread(mainWidget, mapForm, settingWidget, st);
    MouThread *mouseThread = new MouThread();
    AirThread *airSimThread = new AirThread(mainWidget, mapForm, settingWidget, st,
                                            settingWidget->ui->csscComboBox,
                                            settingWidget->ui->csscComboBox_2,
                                            settingWidget->ui->csscComboBox_3,
                                            settingWidget->ui->csscComboBox_4,0);
    AirThread *airSimThread1 = new AirThread(mainWidget, mapForm, settingWidget, st,
                                            settingWidget->ui->csscComboBox,
                                            settingWidget->ui->csscComboBox_2,
                                            settingWidget->ui->csscComboBox_3,
                                            settingWidget->ui->csscComboBox_4,1);
    AirThread *airSimThread2 = new AirThread(mainWidget, mapForm, settingWidget, st,
                                            settingWidget->ui->csscComboBox,
                                            settingWidget->ui->csscComboBox_2,
                                            settingWidget->ui->csscComboBox_3,
                                            settingWidget->ui->csscComboBox_4,2);
    AirThread *airSimThread3 = new AirThread(mainWidget, mapForm, settingWidget, st,
                                            settingWidget->ui->csscComboBox,
                                            settingWidget->ui->csscComboBox_2,
                                            settingWidget->ui->csscComboBox_3,
                                            settingWidget->ui->csscComboBox_4,3);
    MapThread *mapThread = new MapThread(mainWidget, mapForm, settingWidget, st);
    MainThread *mainThread = new MainThread(mainWidget, mapForm, settingWidget, st);
    MapDataThread *mapDataThread = new MapDataThread(mainWidget, mapForm, settingWidget, st);
    FileThread *fileThread = new FileThread(mainWidget, mapForm, settingWidget, st);


    QThread* thread1 = new QThread();
    QThread* thread2 = new QThread();
    QThread* thread3 = new QThread();
    QThread* thread4 = new QThread();
    QThread* thread5 = new QThread();
    QThread* thread6 = new QThread();
    QThread* thread7 = new QThread();
    QThread* thread8 = new QThread();
    QThread* thread9 = new QThread();
    thread10 = new QThread();

    recvThread->moveToThread(thread1);
    mouseThread->moveToThread(thread2);
    airSimThread->moveToThread(thread3);
    airSimThread1->moveToThread(thread4);
    airSimThread2->moveToThread(thread5);
    airSimThread3->moveToThread(thread6);
    mapThread->moveToThread(thread7);
    mainThread->moveToThread(thread8);
    mapDataThread->moveToThread(thread9);
    fileThread->moveToThread(thread10);


    QObject::connect(thread1, SIGNAL(started()), recvThread, SLOT(slot_runRecievedMsg()));
    QObject::connect(thread2, SIGNAL(started()), mouseThread, SLOT(slot_runClick()));
    QObject::connect(thread3, SIGNAL(started()), airSimThread, SLOT(slot_recieveAirSimMsg()));
    QObject::connect(thread4, SIGNAL(started()), airSimThread1, SLOT(slot_recieveAirSimMsg()));
    QObject::connect(thread5, SIGNAL(started()), airSimThread2, SLOT(slot_recieveAirSimMsg()));
    QObject::connect(thread6, SIGNAL(started()), airSimThread3, SLOT(slot_recieveAirSimMsg()));
    QObject::connect(thread7, SIGNAL(started()), mapThread, SLOT(slot_recieveMapMsg()));
    QObject::connect(thread8, SIGNAL(started()), mainThread, SLOT(slot_recieveMainMsg()));
    QObject::connect(thread9, SIGNAL(started()), mapDataThread, SLOT(slot_recieveMapDataMsg()));
    QObject::connect(thread10, SIGNAL(started()), fileThread, SLOT(doWork()));
//    QObject::connect(thread10, &QThread::finished, fileThread, &QObject::deleteLater);

    thread1->start();
    thread2->start();
    thread3->start();
    thread4->start();
    thread5->start();
    thread6->start();
    thread7->start();
    thread8->start();
    thread9->start();
//    thread10->start();
//让应用程序对象进入消息循环，让代码阻塞到这行，类似于system("pause")
    return a.exec();
}
