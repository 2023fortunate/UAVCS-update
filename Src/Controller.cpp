#include "Include/Controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{
    MainWidget *mainWidget = new MainWidget();
    MapForm *mapForm = new MapForm();
    SettingWidget *settingWidget = new SettingWidget();
    ShowTrack *st = new ShowTrack(mainWidget, mapForm, settingWidget);
    FileThread *fileThread = new FileThread(mainWidget, mapForm, settingWidget, st);


    // 调用 moveToThread 将该任务交给 workThread
    fileThread->moveToThread(&workerThread);

    // operate 信号发射后启动线程工作
    connect(this, SIGNAL(operate(const int)), fileThread, SLOT(doWork(int)));

    // 该线程结束时销毁
    connect(&workerThread, &QThread::finished, fileThread, &QObject::deleteLater);

    // 线程结束后发送信号，对结果进行处理
    connect(fileThread, SIGNAL(resultReady(int)), this, SLOT(handleResults(int)));

    // 启动线程
    workerThread.start();

    // 发射信号，开始执行
//    qDebug() << "emit the signal to execute!" ;
//    qDebug() << "\tCurrent thread ID:" << QThread::currentThreadId() << '\n' ;
    extern int hisVideo;
    emit operate(hisVideo);
}

// 析构函数中调用 quit() 函数结束线程
Controller::~Controller()
{
    workerThread.quit();
    workerThread.wait();
}

void Controller::handleResults(const int result)
{
    extern int hisVideo;
    qDebug() << "hisVideo  Controller==" << hisVideo ;
    qDebug() << "result  Controller==" << result ;
}
