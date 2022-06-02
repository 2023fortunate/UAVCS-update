#ifndef MAPTHREAD_H
#define MAPTHREAD_H

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
extern int hisVideo;
class MapThread : public Signals
{
    Q_OBJECT
private:
    void *subscriber;
    QJsonObject commandJson;
    std::vector<GV>gds;
    std::map<std::string,size_t> pr;
    std::string curr_name;
    MapWidget *mapWidget;
public:
    MapThread(MainWidget *mw, MapForm *mf, SettingWidget *sw, ShowTrack *st):Signals (mw, mf, sw, st)
    {
//        connect(this, SIGNAL(sentUAVData(QJsonArray)), mf, SLOT(setUAVData(QJsonArray)));
        connect(this, SIGNAL(sentUAVImg(QPixmap)), mf, SLOT(setUAVImg(QPixmap)));
    }
    ~MapThread();
    QJsonObject objFinal2;
    int count2 = 0;
    int finish2 = 0;
    bool removeFolderContent1(const QString &folderDir);
    //清除jsonObject对象内容
    void clearJsonObject1(QJsonObject &object);

signals:

//    void sentUAVData(QJsonArray uav);
    void sentUAVImg(QPixmap pixmap);

public slots:
    void slot_recieveMapMsg();

};

#endif // MAPTHREAD_H
