#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include "CSSCWidget.h"
//#include "CSSC/CSSCWidget.h"
//播放视频
#include<QMediaPlayer>
#include<QVideoWidget>
#include<QMediaPlaylist>
#include<QUrl>
#include <QMouseEvent>

#include "MainWidget.h"
#include <QMainWindow>
#include "Include/GetData.h"
#include "Include/GetVedio.h"

extern int pointX;
extern int pointY;
extern QString uiID;
extern QString commandType;

namespace Ui {
class SettingWidget;
}

class SettingWidget : public QMainWindow
{
    Q_OBJECT

public:
    Ui::SettingWidget *ui;

    int curTime;

    explicit SettingWidget(QWidget *parent = 0);

    ~SettingWidget();

    //重写定时器事件
    void timerEvent(QTimerEvent *);

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    //设置视频
    void setVideo();

    //设置图片
    //void setImage(QPixmap pixmap,int index);
    void setImage();


public slots:

    void on_all1_clicked();

    void on_all2_clicked();

    void on_all3_clicked();

    void on_all4_clicked();

    void on_jia1_clicked();

    void on_jia2_clicked();

    void on_jia3_clicked();

    void on_jia4_clicked();

    void show_all(int index);

//    void on_csscRadioButton_clicked();

//    void on_csscRadioButton_2_clicked();

//    void on_csscToolButton_clicked();

//    void on_csscToolButton_clicked();

//    void on_csscToolButton_5_clicked();

//    void on_csscToolButton_2_clicked();

//    void on_csscToolButton_4_clicked();

//    void on_csscToolButton_3_clicked();

//    void on_csscToolButton_6_clicked();

    //判断无人机是放大还是全屏
    void enlargeOrFull(int airID);
    void recoverFour1(int airID);
//    void backPlay(int index);
//    void recoverPlay(int index);

    void recoverFour();
    //void setImage(QPixmap pixmap,int index);
    void setData(QJsonObject uav);
    void setData1(QJsonObject uav);
    void setData2(QJsonObject uav);
    void setData3(QJsonObject uav);
    void setImage(QPixmap pixmap,QString uav_name,int index);
    void setImage1(QPixmap pixmap,QString uav_name,int index);
    void setImage2(QPixmap pixmap,QString uav_name,int index);
    void setImage3(QPixmap pixmap,QString uav_name,int index);
    void setUAVName(QStringList list);
    void RefreshWindow(int num);

private slots:
  //  void on_csscComboBox_currentTextChanged(const QString &arg1);

//    void on_csscComboBox_2_currentTextChanged(const QString &arg1);

//    void on_csscComboBox_3_currentTextChanged(const QString &arg1);

//    void on_csscComboBox_4_currentTextChanged(const QString &arg1);


    void on_jian1_clicked();

    void on_jian2_clicked();

    void on_jian3_clicked();

    void on_jian4_clicked();

private:
//    QMediaPlayer *player1;
//    QVideoWidget *videoWidget1;
//    QMediaPlaylist *mediaList1;

//    QMediaPlayer *player2;
//    QVideoWidget *videoWidget2;
//    QMediaPlaylist *mediaList2;
//    QMediaPlayer *player3;
//    QVideoWidget *videoWidget3;
//    QMediaPlaylist *mediaList3;
//    QMediaPlayer *player4;
//    QVideoWidget *videoWidget4;
//    QMediaPlaylist *mediaList4;

    virtual void keyPressEvent(QKeyEvent *keyset);
};

#endif // SETTINGWIDGET_H
