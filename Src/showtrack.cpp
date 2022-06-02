#include "Include/showtrack.h"
#include <QDebug>

ShowTrack::ShowTrack(MainWidget *mw, MapForm *mf, SettingWidget *sw)
{
    this->mainWidget = mw;
    this->mapForm = mf;
    this->settingWidget = sw;

    count = 0;
    lastID = 0;

    w1 = new QWidget(mainWidget);
//    w2 = new QWidget(mainWidget);
//    w3 = new QWidget(mainWidget);
//    w4 = new QWidget(mainWidget);

}
ShowTrack::~ShowTrack()
{

}

void ShowTrack::setMyStyle(QWidget *wid, int w, int h)
{
    wid->setWindowFlags(Qt::FramelessWindowHint);
    wid->resize(w,h);
    wid->setStyleSheet("border-image: url(:/Image/show.png);");
}

void ShowTrack::deleteList(QList<QPoint> point)
{
    foreach(auto item, point)
        point.removeOne(item);
}

void ShowTrack::updatePos(QJsonObject jb)
{
    qDebug() << "===================================";
    qDebug() << "jsonMessage" << jb;
    pointX = jb.value("logicX").toInt();
    pointY = jb.value("logicY").toInt();
    uiID = jb.value("logicID").toInt();
    uiID = 2;
    std::cout<<"pointX = "<<pointX<<std::endl;
    std::cout<<"pointY = "<<pointY<<std::endl;
    std::cout<<"uiID = "<<uiID<<std::endl;
    if(uiID != lastID)
    {
        delete w1;
//        delete w2;
//        delete w3;
//        delete w4;
//        deleteList(pos_list_w2);
//        deleteList(pos_list_w3);
//        deleteList(pos_list_w4);

        if(uiID == 1)
        {
            w1 = new QWidget(mainWidget);
//            w2 = new QWidget(mainWidget);
//            w3 = new QWidget(mainWidget);
//            w4 = new QWidget(mainWidget);
        }
        else if (uiID == 2) {
            w1 = new QWidget(mapForm);
//            w2 = new QWidget(mapForm);
//            w3 = new QWidget(mapForm);
//            w4 = new QWidget(mapForm);
        }
        else {
            w1 = new QWidget(settingWidget);
//            w2 = new QWidget(settingWidget);
//            w3 = new QWidget(settingWidget);
//            w4 = new QWidget(settingWidget);
        }

        w1->setVisible(true);
//        w2->setVisible(true);
//        w3->setVisible(true);
//        w4->setVisible(true);

        setMyStyle(w1, 34, 34);
//        setMyStyle(w2, 26, 26);
//        setMyStyle(w3, 18, 18);
//        setMyStyle(w4, 9, 9);
    }

//  更新意图控制点坐标轨迹
    w1->move(pointX, pointY);
    point = QPoint(pointX, pointY);
//    if(!count)
//    pos_list_w2 << point;
//   * count > 7 ? (count = 0): count++;

//    if(!pos_list_w4.isEmpty())
//        this->w4->move(pos_list_w4.takeFirst());
//    if(!pos_list_w3.isEmpty())
//    {
//        pos_list_w4 << pos_list_w3.first();
//        this->w3->move(pos_list_w3.takeFirst());
//    }
//    if(!pos_list_w2.isEmpty())
//    {
//        pos_list_w3 << pos_list_w2.first();
//        this->w2->move(pos_list_w2.takeFirst());
//    }

    lastID = uiID;
}
