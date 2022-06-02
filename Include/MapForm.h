#ifndef MAPFORM_H
#define MAPFORM_H

#include "CSSCWidget.h"
#include "mapwidget.h"
#include <QObject>
#include "MainWidget.h"
#include "SettingWidget.h"
#include <QThread>
extern int pointX;
extern int pointY;
extern QString uiID;
extern QString commandType;
extern int finish4;
extern int hisVideo;
extern int uav_index;
extern int uav_state;
extern double his_sudu;
extern qint64 timelapse;
extern int restart;
extern int stopThread;
extern QThread* thread10;
namespace Ui {
class MapForm;
}

class MapForm : public CSSCWidget
{
    Q_OBJECT

public:
    MapWidget *mapWidget;
    SettingWidget *sw;

    Ui::MapForm *ui;

    MapForm(QWidget *parent = 0);

    ~MapForm();

    int find = 0;
    int first_find = 0;
    int uav_index1 = 0;
    int uav_state1 = 0;
    int order = 0;
//    int finish = 0;

//    int his = 0;

//    int hisCount1 = 0;

//    int hisCount2 = 0;

//    int rootSize = 0;

//    static QList<QPoint> f_points;

    //重写定时器事件
    void timerEvent(QTimerEvent *);

//    QThread *workerThread;

private:
    QList<QPair<QString,QPoint>> pointList1;//保存所有要画的起点
    QList<QPair<QString,QPoint>> pointList2;//保存所有要画的终点
//    QPair<QString,QPoint> startPoint1; //线段起点
//    QPair<QString,QPoint> endPoint2; //线段终点


public slots:

   void setUAVData(QJsonArray uav);

   void setUAVImg(QPixmap pixmap);

   void on_MapForm_sigMinButtonClicked();

   void on_MapForm_sigMaxButtonClicked();

   void on_big_clicked();

   void on_small_clicked();

   void on_orbit_1_clicked();

   void on_orbit_2_clicked();

   void on_orbit_3_clicked();

   void on_orbit_4_clicked();

   void on_orbit_1_2_clicked();

   void on_orbit_3_4_clicked();

   void on_orbit_1_2_3_4_clicked();

   //定义关于地图操作的几个槽函数
   //地图放大
   void mapEnlarge();

   //地图缩小
   void mapDecrease();

   //地图左移
   void mapLeft(int moveX);

   //地图右移
   void mapRight(int moveX);

   //地图上移
   void mapUp(int moveY);

   //地图下移
   void mapDown(int moveY);

   void showOrbit(int index);

   void history(int uav,int state);

   void sudu(int index);
   void handleResults();  // 处理子线程执行的结果

   void shiftTime(int index);


private slots:
   void on_large_clicked();
};

#endif // FORM_H
