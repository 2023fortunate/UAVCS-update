#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>
#include <QDebug>

#include "FileThread.h"
#include "Include/MainWidget.h"
#include "Include/MapForm.h"
#include "Include/SettingWidget.h"
#include "Include/signals.h"
#include <Include/showtrack.h>

extern int hisVideo;
// controller 用于 启动子线程 和 处理子线程执行的结果
class Controller : public QObject
{
Q_OBJECT

    QThread workerThread ;

public:
    explicit Controller(QObject *parent = nullptr);

    ~Controller() override ;

public slots:
    static void handleResults(int result);  // 处理子线程执行的结果

signals:
    void operate(const int);  // 发送信号，触发线程
};

#endif //DEL_CONTROLLER_H
