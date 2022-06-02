#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include <QtGui>
#include <QApplication>
#include <QImage>
#include"CSSCToolButton.h"
#include <QQueue>


extern double G_px1;
extern double G_px2;
extern double G_px3;
extern double G_px4;
extern double G_py1;
extern double G_py2;
extern double G_py3;
extern double G_py4;


class MapWidget : public QWidget
{
    Q_OBJECT

private slots:

public:
    QPixmap pix;
    int action;          //动作(放大,缩小,移动...)

    QRect Paint;         //绘画区域

    QImage image;        //打开的图片

    QList<QPair<QString,QPoint>> pointList3;//保存所有要画的起点
    QList<QPair<QString,QPoint>> pointList4;//保存所有要画的终点
    QPair<QString,QPoint> startPoint3; //线段起点
    QPair<QString,QPoint> endPoint4; //线段终点

    QPoint uav1[3000];//保存uav1
    QPoint uav2[3000];//保存uav2
    QPoint uav3[3000];//保存uav3
    QPoint uav4[3000];//保存uav4
    QPoint monitor[3000];//保存侦察机monitor
    QPoint drone[3000];//保存敌机drone

    int length = 3000;//保存数组的长度

    double ratio;              //缩放比例
    double maxRatio;          //最大的缩放比例，导入图片时计算得到
    QPoint offset;           //鼠标移动一次的图片偏移值
    QPoint Alloffset;          //总偏移
    QPoint oldMouse;           //鼠标移动时上一次的位置
    bool pressed;              //鼠标左键是否被按下



    double ofx = 0;
    double ofy = 0;

    int timeCount = 0;

    bool event(QEvent *event);               //鼠标时间
    void wheelEvent(QWheelEvent *event);     //鼠标滑轮事件
    void paintEvent(QPaintEvent *event);     //绘图事件

    enum  Type {
        None          = 0,
        Amplification ,
        Shrink,
        His,
        Lift,
        Right,
        Up,
        Down,
        Move,
        Reset,
        first_air,
        second_air,
        third_air,
        fourth_air,
        fir_sec_air,
        thi_fou_air,
        all_air,
        Large
    };
    void setAction(int value);
    void setPoint1(QList<QPair<QString,QPoint>>  pointList,int find,int first_find);
    void setPoint2(QList<QPair<QString,QPoint>>  pointList,int find,int first_find);

    explicit MapWidget(QWidget *parent = 0);

    //重写定时器事件
    void timerEvent(QTimerEvent *);

    double px1;
    double px2;
    double px3;
    double px4;
    double py1;
    double py2;
    double py3;
    double py4;

public slots:
};

#endif // MAPWIDGET_H
