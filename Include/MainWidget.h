#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include<QMouseEvent>
#include<QPainter>
#include<QPoint>
#include<QList>
#include<math.h>
#include <QPixmap>
#include <QImage>
#include <QGraphicsBlurEffect>
#include <QPaintEvent>
#include "CSSCWidget.h"
#include "SettingWidget.h"
#include "mapwidget.h"
#include<QVector>
#include<QMediaPlayer>
#include<QVideoWidget>
#include<QMediaPlaylist>
#include<QUrl>
#include<QMovie>
#include<QPalette>
#include<QTimer>

extern bool G_add2;
extern bool G_jian2;

namespace Ui {
class MainWidget;
}
QT_BEGIN_NAMESPACE
extern Q_WIDGETS_EXPORT void qt_blurImage(QPainter *p, QImage &blurImage, qreal radius, bool quality, bool alphaOnly, int transposed = 0);
QT_END_NAMESPACE
class MainWidget : public CSSCWidget
{
    Q_OBJECT

public:
    Ui::MainWidget *ui;
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

    int action;          //动作(放大,缩小,移动...)

    //重写定时器事件
//    void timerEvent(QTimerEvent *);

    bool eventFilter(QObject *watched, QEvent *event);

    void showPaint(QList<QPointF> points);
//    void showPaint1();

//    void mousePressEvent(QMouseEvent *event);
//    void mouseReleaseEvent(QMouseEvent *event);

//    void paintEvent(QPaintEvent *e);

    //加速2
    bool add2;
    //减速2
    bool jian2;

    //初始化
    bool inited;

    static QList<QPointF> m_points;        //绘制点

    int uav_index = 0;//uav的名称，初始为0

    int Convert(int num);

    int shortNum(int num,int step);

    double ratio1;              //缩放比例(宽度)
    double ratio2;              //缩放比例（高度）

    int imgNum;

    QVector<QString> strArray;//多图片下，图片的路径集合

    //与Slider有关的播放控制变量
    QTimer * timer;
    int maxValue = 100;//设置进度条的最大值

    QVector<QString> poUAV;

    int his = 0;

    int hisCount = 0;

    int rootSize = 0;


private:
        QMediaPlayer *player1;
        QVideoWidget *videoWidget1;
        QMediaPlaylist *mediaList1;
        QString imgPath;
        qint64 playtime;
        QGraphicsBlurEffect *blureffect1;
        QGraphicsBlurEffect *blureffect2;
        QGraphicsBlurEffect *blureffect3;
        QGraphicsBlurEffect *blureffect4;
        QGraphicsBlurEffect *blureffect5;

public slots:
    void on_MainWidget_sigMinButtonClicked();

    void setUAVMainData(QJsonObject uav);

    void acclerate_v();

    void decelerate_v();

//    void on_csscPushButton_13_clicked();

    void on_csscToolButton_clicked();

    void on_csscToolButton_4_clicked();

    void on_csscToolButton_3_clicked();

    void on_csscToolButton_2_clicked();

    void on_csscToolButton_5_clicked();

    //显示不同无人机状态（修改无人机编号）
    void showState(int airID);
    void showState1(int airID);

    //修改无人机的工作模式
//    void workPattern(int patternID);

    void highShow(int index);

    void changeIndex(int index);

    void popWindow(int index1, int index2);

    void imageEnlarge();

    void imageDecrease();

    void imageFull();

    void imageLeft();

    void imageRight();

    void windowRecover();

    QString settime(qint64 playtime);

    void shortWords(QString dlgTitle,QString strInfo);
    void longWords(QString dlgTitle,QString strInfo);
    void wordImg(QString dlgTitle,QString strInfo1,QVector<QString> imgs);
    void img(QString dlgTitle,QString strInfo);
    void imgs(QString dlgTitle,QVector<QString> strArray);
    void moveImg(QString dlgTitle,QString strInfo);
    void video(QString dlgTitle,QString strInfo);


private slots:
    //void on_csscPicTextButton_clicked();
    //改变无人机的配置模式
//    void modeChange(int airID,int modeID);
//    void on_mode_currentIndexChanged(int index);
  //  void on_uav_name_currentTextChanged(const QString &arg1);
    void on_up_vx_clicked();
    void on_up_vy_clicked();
    void on_up_vz_clicked();
    void on_down_vx_clicked();
    void on_down_vy_clicked();
    void on_down_vz_clicked();
    void on_up_pitch_clicked();
    void on_up_roll_clicked();
    void on_up_yaw_clicked();
    void on_down_pitch_clicked();
    void on_down_roll_clicked();
    void on_down_yaw_clicked();
    void on_uav_name_currentIndexChanged(int index);

    void on_csscMediaControl_sigAddRate();
    void on_csscSliderTip_valueChanged(int value);
    void on_csscMediaControl_sigSubRate();
    void on_csscMediaControl_sigReplay();
    void on_csscMediaControl_sigFullScreen();
    void on_big_clicked();
    void on_small_clicked();
    void on_all_clicked();
    void on_left_clicked();
    void on_right_clicked();
    void on_csscMediaControl_sigPlay();
    void on_csscMediaControl_sigStop();
    void getduration(qint64 playtime);
    void on_csscSliderTip_clicked();
    void on_csscSliderTip_sliderMoved(int position);
    void on_csscSliderTip_sliderReleased();
    void onTimerOut();
    void onTimerOut1();


};

#endif // MAINWIDGET_H
