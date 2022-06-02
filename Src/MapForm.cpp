#include "Include/MapForm.h"
#include "ui_MapForm.h"
#include<complex>
#include <Include/FileThread.h>
#include <QThread>
#include <QObject>

MapForm::MapForm(QWidget *parent) :
    CSSCWidget(parent),
    ui(new Ui::MapForm)
{
    mapWidget = new MapWidget(this);
    sw = new SettingWidget(this);
    mapWidget->setGeometry(0, 30, 480, 263);
    mapWidget->setContentsMargins(3, 3, 3, 3);
    this->mapWidget->setAction(MapWidget::Large);
    ui->setupUi(this);
    this->setWindowMovable(false);
//    QImage image = QImage(":/Image/map.jpg");
//    QPixmap pix = pix.fromImage(image);
//    ui->map->setPixmap(mapLabel->pix);
//    ui->map->setGeometry(3,33,370,290);
    this->mapWidget->raise();
    ui->large->raise();
//    ui->map->installEventFilter(this);
    //ui->uav_text->setVisible(false);
    //ui->uav_text->setShowText("UAV1");
    ui->jingwei->setVisible(false);
    ui->jingwei_2->setVisible(false);
    ui->jingwei_3->setVisible(false);
    ui->jingwei_4->setVisible(false);
    ui->zhiNanZhen->setVisible(true);
    ui->shuiPingYi->setVisible(true);

    ui->big->setVisible(false);
    ui->small->setVisible(false);
    ui->orbit_1->setVisible(false);
    ui->orbit_2->setVisible(false);
    ui->orbit_3->setVisible(false);
    ui->orbit_4->setVisible(false);
    ui->orbit_1_2->setVisible(false);
    ui->orbit_3_4->setVisible(false);
    ui->orbit_1_2_3_4->setVisible(false);

    //启动定时器,间隔为1s
    startTimer(1000);
    ui->csscWarning->setVisible(false);

   // this->setMouseTracking(true);

    //开启定时器
    startTimer(1000);
    if(pointList1.size()>0){
        mapWidget->setPoint1(pointList1,find,first_find);
    }
    if(pointList2.size()>0){
         mapWidget->setPoint2(pointList2,find,first_find);
    }

}

MapForm::~MapForm()
{
    delete ui;
}
int finish4;
int hisVideo;
int uav_state;
int uav_index;
double his_sudu=1.0;
int restart = 0;
int stopThread = 0;
qint64 timelapse=0;
//bool MapForm::eventFilter(QObject *watched, QEvent *event)   //用过滤器eventFilter（）拦截QLabel中的QEvent::Paint事件
//{
//    if(watched ==ui->map && event->type() == QEvent::Paint){
//        //响应函数
//        showPaint(MapForm::f_points);
//    }
//    return QWidget::eventFilter(watched,event);
//}


//定义关于地图操作的几个槽函数
//地图放大
void MapForm::mapEnlarge()
{
    mapWidget->setAction(MapWidget::Amplification);
    if(pointList1.size()>0){
        mapWidget->setPoint1(pointList1,find,first_find);
    }
    if(pointList2.size()>0){
         mapWidget->setPoint2(pointList2,find,first_find);
    }
    mapWidget->update();
}

//地图缩小
void MapForm::mapDecrease()
{
    mapWidget->setAction(MapWidget::Shrink);
    if(pointList1.size()>0){
        mapWidget->setPoint1(pointList1,find,first_find);
    }
    if(pointList2.size()>0){
         mapWidget->setPoint2(pointList2,find,first_find);
    }
    mapWidget->update();
}

//地图左移
void MapForm::mapLeft(int moveX)
{
    qDebug()<<"左移";
    mapWidget->offset.setX(-moveX);
    mapWidget->oldMouse.setX(mapWidget->oldMouse.x() - moveX);
    mapWidget->setAction(MapWidget::Move);
    if(pointList1.size()>0){
        mapWidget->setPoint1(pointList1,find,first_find);
    }
    if(pointList2.size()>0){
         mapWidget->setPoint2(pointList2,find,first_find);
    }
    mapWidget->update();
}

//地图右移
void MapForm::mapRight(int moveX)
{
    qDebug()<<"右移";
    mapWidget->offset.setX(moveX);
    mapWidget->oldMouse.setX(mapWidget->oldMouse.x() + moveX);
    mapWidget->setAction(MapWidget::Move);
    if(pointList1.size()>0){
        mapWidget->setPoint1(pointList1,find,first_find);
    }
    if(pointList2.size()>0){
         mapWidget->setPoint2(pointList2,find,first_find);
    }
    mapWidget->update();

}

//地图上移
void MapForm::mapUp(int moveY)
{
    mapWidget->offset.setY(-moveY);
    mapWidget->oldMouse.setY(mapWidget->oldMouse.y() - moveY);
    mapWidget->setAction(MapWidget::Move);
    if(pointList1.size()>0){
        mapWidget->setPoint1(pointList1,find,first_find);
    }
    if(pointList2.size()>0){
         mapWidget->setPoint2(pointList2,find,first_find);
    }
    mapWidget->update();
}

//地图下移
void MapForm::mapDown(int moveY)
{
    mapWidget->offset.setY(moveY);
    mapWidget->oldMouse.setY(mapWidget->oldMouse.y() + moveY);
    mapWidget->setAction(MapWidget::Move);
    if(pointList1.size()>0){
        mapWidget->setPoint1(pointList1,find,first_find);
    }
    if(pointList2.size()>0){
         mapWidget->setPoint2(pointList2,find,first_find);
    }
    mapWidget->update();
}


void MapForm::on_big_clicked()
{
    this->mapWidget->setAction(MapWidget::Amplification);
    if(pointList1.size()>0){
        mapWidget->setPoint1(pointList1,find,first_find);
    }
    if(pointList2.size()>0){
         mapWidget->setPoint2(pointList2,find,first_find);
    }
    mapWidget->update();
}

void MapForm::on_small_clicked()
{
    this->mapWidget->setAction(MapWidget::Shrink);
    if(pointList1.size()>0){
        mapWidget->setPoint1(pointList1,find,first_find);
    }
    if(pointList2.size()>0){
         mapWidget->setPoint2(pointList2,find,first_find);
    }
    mapWidget->update();
}

void MapForm::on_MapForm_sigMinButtonClicked()
{
    this->showMinimized();
}
void MapForm::on_MapForm_sigMaxButtonClicked()
{
    this->showMaximized();
}

void MapForm::timerEvent(QTimerEvent *)
{
    int id = 0;

    if(find == 0 && first_find == 0 && finish4 == 0){
        ui->csscWarning->addWarningMessage(QTime().currentTime(),id,1,"warning",1,"无人机开始巡逻!");
    }else if(find > 0 && first_find == 1 && finish4 == 0){
        mapWidget->maxRatio = 5;
        mapEnlarge();
        ui->csscWarning->addWarningMessage(QTime().currentTime(),id+1,2,"warning",2,"无人机搜寻到敌机，开始实施围捕!");
    }else if(find > 0 && first_find == 0 && finish4 == 0){
       mapWidget->maxRatio = 5;
       mapEnlarge();
       ui->csscWarning->addWarningMessage(QTime().currentTime(),id+2,3,"warning",3,"无人机围捕敌机中!");
    }
    if(pointList1.size()>0 && pointList2.size()>0 && finish4 == 0){
//        qDebug()<<"进来了"<<"pointlist1="<<pointList1<<",pointlist2="<<pointList2;
        double chax = pointList2.at(0).second.x()-pointList1.at(0).second.x();
        double chay = pointList2.at(0).second.y()-pointList1.at(0).second.y();
        double chax2 = pointList2.at(1).second.x()-pointList1.at(1).second.x();
        double chay2 = pointList2.at(1).second.y()-pointList1.at(1).second.y();
        double chax3 = pointList2.at(2).second.x()-pointList1.at(2).second.x();
        double chay3 = pointList2.at(2).second.y()-pointList1.at(2).second.y();
        double chax4 = pointList2.at(3).second.x()-pointList1.at(3).second.x();
        double chay4 = pointList2.at(3).second.y()-pointList1.at(3).second.y();
        double chax5 = pointList2.at(4).second.x()-pointList1.at(4).second.x();
        double chay5 = pointList2.at(4).second.y()-pointList1.at(4).second.y();
//        qDebug()<<"进来了"<<"chax="<<chax<<",chay="<<chay;
        if(find > 0 && (abs(chax)<=5&&abs(chay)<=5)&& (abs(chax2)<=5&&abs(chay2)<=5)&& (abs(chax3)<=5&&abs(chay3)<=5)&& (abs(chax4)<=5&&abs(chay4)<=5)&& (abs(chax5)<=5&&abs(chay5)<=5)){
               qDebug()<<"进来了"<<"find="<<find;
               ui->csscWarning->addWarningMessage(QTime().currentTime(),id+3,4,"warning",1,"围捕成功!");
               foreach(auto item,pointList2)
               {
                   pointList2.removeOne(item);
               }
               foreach(auto item,mapWidget->pointList4)
               {
                   mapWidget->pointList4.removeOne(item);
               }
               on_large_clicked();
               finish4 = 1;

        }
    }

}
void MapForm::history(int index,int state)
{
    qDebug()<<"回放指令已发出=============";
    extern QThread* thread10;
    if( (thread10->isRunning()) && (!thread10->isFinished()) ){
        restart = 1;
    }else{
        restart = 0;
    }
    qDebug()<<"restart============="<<restart<<",thread10->isRunning()="<<thread10->isRunning()<<",thread10->isFinished()="<<thread10->isFinished();
    if(order==0){
        timelapse=0;
    }
    hisVideo = 1;
    uav_index = index;
    uav_state = state;
    uav_index1 = index;
    uav_state1 = state;
    qDebug()<<"uav_index============="<<uav_index<<",uav_index1="<<uav_index1<<",uav_state="<<uav_state<<",uav_state1="<<uav_state1;
    if(restart == 0){
        if(order==1){
            order=0;
        }
        his_sudu=1.0;
        find = 0;
        first_find = 0;
        finish4 = 0;
        stopThread = 0;
        foreach(auto item,pointList1)
        {
            pointList1.removeOne(item);
        }
        foreach(auto item,pointList2)
        {
            pointList2.removeOne(item);
        }
        foreach(auto item,mapWidget->pointList3)
        {
            mapWidget->pointList3.removeOne(item);
        }
        foreach(auto item,mapWidget->pointList4)
        {
            mapWidget->pointList4.removeOne(item);
        }
        mapWidget->setAction(MapWidget::His);

        // 启动线程
        thread10->start();
    }
}

void MapForm::sudu(int index)
{
    qDebug() << "emit===index==="<<index ;
    if(index==1){
        his_sudu = his_sudu+1.0;
    }
    if(index==2&&his_sudu>2){
        his_sudu = his_sudu-1.0;
    }
    if(index==2&&his_sudu>0.5){
        his_sudu = his_sudu-0.5;
    }
    qDebug() << "emit===his_sudu==="<<his_sudu ;
}

void MapForm::shiftTime(int index)
{
    qDebug() << "emit==time===index==="<<index ;

    if(index==1){
        timelapse = 30000;
    }else if(index==2){
        timelapse = 60000;
    }else if(index==3){
        timelapse = 108139;
    }else{
        timelapse = 0;
    }
    order=1;
    qDebug() << "emit===timelapse==="<<timelapse ;
    MapForm::history(uav_index1,uav_state1);
}

void MapForm::handleResults()
{
    //文件处理完毕
    stopThread = 1;
    hisVideo = 2;
    uav_state = 3;
    his_sudu = 1.0;
    uav_index = 0;
    finish4 = 0;
    qDebug() << "回放线程结束===============" << hisVideo;
//    thread10->quit();
    thread10->terminate();
    thread10->wait();
    if(restart == 1){
        MapForm::history(uav_index1,uav_state1);
    }
    // 该线程结束时销毁
//    connect(workerThread, &QThread::finished, fileThread, &QObject::deleteLater);
}
void MapForm::setUAVData(QJsonArray uav){


        find = uav[0].toObject().value("find").toInt();
//        for(int i=0;i<6;i++){
//            qDebug()<<"uav["<<i<<"]="<<uav[i];
//        }

        first_find = uav[0].toObject().value("first_find").toInt();
        if(uav.size()!=0){
                ui->jingwei->setValue(uav[0].toObject().value("longitude").toDouble(),uav[0].toObject().value("latitude").toDouble());
                ui->jingwei_2->setValue(uav[1].toObject().value("longitude").toDouble(),uav[1].toObject().value("latitude").toDouble());
                ui->jingwei_3->setValue(uav[2].toObject().value("longitude").toDouble(),uav[2].toObject().value("latitude").toDouble());
                ui->jingwei_4->setValue(uav[3].toObject().value("longitude").toDouble(),uav[3].toObject().value("latitude").toDouble());
                int pitch = static_cast<int>(ceil(uav[0].toObject().value("pitch").toDouble()));
                int roll = static_cast<int>(ceil(uav[0].toObject().value("roll").toDouble()));
                ui->shuiPingYi->setDegValue(abs(pitch)); //设置旋转角度值pitch
                ui->shuiPingYi->setRollValue(abs(roll)); //设置前进旋转值roll
                double yaw = uav[0].toObject().value("yaw").toDouble();
                ui->zhiNanZhen->setValue(abs(yaw)); //yaw

                double x[5];
                double y[5];
                double x1[5];
                double y1[5];
                double aa = 960.0;
                double bb = 555.0;
//                for(int i=0;i<5;i++){
//                    qDebug()<<"x["<<i<<"]="<<uav[i].toObject().value("x").toDouble()<<".y"<<i<<"]="<<uav[i].toObject().value("y").toDouble();
//                    qDebug()<<"x1["<<i<<"]="<<uav[i].toObject().value("x1").toDouble()<<".y1"<<i<<"]="<<uav[i].toObject().value("y1").toDouble();
//                }

                if(find>0){
                    x[0] = aa + uav[0].toObject().value("y").toDouble()+30;
                    y[1] = bb - uav[1].toObject().value("x").toDouble()+30;
                    y[2] = bb - uav[2].toObject().value("x").toDouble()-30;
                    x[3] = aa + uav[3].toObject().value("y").toDouble()-30;
                }else{
                    x[0] = aa + uav[0].toObject().value("y").toDouble();
                    y[1] = bb - uav[1].toObject().value("x").toDouble();
                    y[2] = bb - uav[2].toObject().value("x").toDouble();
                    x[3] = aa + uav[3].toObject().value("y").toDouble();
                }
                y[0] = bb - uav[0].toObject().value("x").toDouble();
                x[1] = aa + uav[1].toObject().value("y").toDouble();
                x[2] = aa + uav[2].toObject().value("y").toDouble();
                y[3] = bb - uav[3].toObject().value("x").toDouble();
                x[4] = aa + uav[4].toObject().value("y").toDouble();
                y[4] = bb - uav[4].toObject().value("x").toDouble();


                x1[0] = aa + uav[0].toObject().value("y1").toDouble()+30;
                y1[0] = bb - uav[0].toObject().value("x1").toDouble();
                x1[1] = aa + uav[1].toObject().value("y1").toDouble();
                y1[1] = bb - uav[1].toObject().value("x1").toDouble()+30;
                x1[2] = aa + uav[2].toObject().value("y1").toDouble();
                y1[2] = bb - uav[2].toObject().value("x1").toDouble()-30;
                x1[3] = aa + uav[3].toObject().value("y1").toDouble()-30;
                y1[3] = bb - uav[3].toObject().value("x1").toDouble();
                x1[4] = aa + uav[5].toObject().value("y").toDouble()-60;
                y1[4] = bb - uav[5].toObject().value("x").toDouble();

//                for(int i=0;i<5;i++){
//                    qDebug()<<"处理完：x["<<i<<"]="<<uav[i].toObject().value("x").toDouble()<<".y"<<i<<"]="<<uav[i].toObject().value("y").toDouble();
//                    qDebug()<<"处理完：x1["<<i<<"]="<<uav[i].toObject().value("x1").toDouble()<<".y1"<<i<<"]="<<uav[i].toObject().value("y1").toDouble();
//                }

                //先把之前的缓存清掉
                foreach(auto item,pointList1)
                {
                    pointList1.removeOne(item);
                }
                foreach(auto item,pointList2)
                {
                    pointList2.removeOne(item);
                }
                //然后更新数据到pointList中
                for (int i=0;i<5;i++) {
                    pointList1.append(qMakePair(uav[i].toObject().value("uav_name").toString(), QPoint(x[i],y[i])));
                }
                for (int i=0;i<5;i++) {
                    QString name;
                    if(i<4){
                        name = uav[i].toObject().value("uav_name").toString();
                    }else if(i==4){
                        name = uav[5].toObject().value("uav_name").toString();
                    }
                    pointList2.append(qMakePair(name, QPoint(x1[i],y1[i])));
                }
//                qDebug() << "pointList1="<<pointList1;
//                qDebug() << "pointList2="<<pointList2;
//                qDebug() << "==============find="<<find;
                if(uav_index!=0){
//                    if(mapWidget->width()==480){
//                        on_large_clicked();
//                    }
                    showOrbit(uav_index);
                }else{
                    mapWidget->setPoint1(pointList1,find,first_find);
                    mapWidget->setPoint2(pointList2,find,uav_state);
                }
                mapWidget->update();
         }
}

void MapForm::setUAVImg(QPixmap pixmap){

//    pixmap.scaled(1800,1250);
    ui->video->setScaledContents(true);
    ui->video->setPixmap(pixmap);

}


void MapForm::showOrbit(int index)
{
//    qDebug() << "show all orbit index" << index;
    uav_index = index;
    switch (index)
    {
    case 1:
        on_orbit_1_clicked();
        break;
    case 2:
        on_orbit_2_clicked();
        break;
    case 3:
        on_orbit_3_clicked();
        break;
    case 4:
        on_orbit_4_clicked();
        break;
    case 5:
        on_orbit_1_2_clicked();
        break;
    case 6:
        on_orbit_3_4_clicked();
        break;
    case 7:
        on_orbit_1_2_3_4_clicked();
        break;
    }
}


void MapForm::on_orbit_1_clicked()
{
//    qDebug()<<"pointList1="<<pointList1;
//    qDebug()<<"pointList2="<<pointList2;
    mapWidget->setAction(MapWidget::first_air);
    if(pointList1.size()>0){
        mapWidget->setPoint1(pointList1,find,first_find);
    }
    if(pointList2.size()>0){
         mapWidget->setPoint2(pointList2,find,first_find);
    }
    ui->jingwei->setVisible(true);
    ui->jingwei_2->setVisible(false);
    ui->jingwei_3->setVisible(false);
    ui->jingwei_4->setVisible(false);
}

void MapForm::on_orbit_2_clicked()
{
    mapWidget->setAction(MapWidget::second_air);
    if(pointList1.size()>0){
        mapWidget->setPoint1(pointList1,find,first_find);
    }
    if(pointList2.size()>0){
         mapWidget->setPoint2(pointList2,find,first_find);
    }
    ui->jingwei->setVisible(false);
    ui->jingwei_2->setVisible(true);
    ui->jingwei_3->setVisible(false);
    ui->jingwei_4->setVisible(false);
}

void MapForm::on_orbit_3_clicked()
{
    mapWidget->setAction(MapWidget::third_air);
    if(pointList1.size()>0){
        mapWidget->setPoint1(pointList1,find,first_find);
    }
    if(pointList2.size()>0){
         mapWidget->setPoint2(pointList2,find,first_find);
    }
    ui->jingwei->setVisible(false);
    ui->jingwei_2->setVisible(false);
    ui->jingwei_3->setVisible(true);
    ui->jingwei_4->setVisible(false);

}

void MapForm::on_orbit_4_clicked()
{
    mapWidget->setAction(MapWidget::fourth_air);
    if(pointList1.size()>0){
        mapWidget->setPoint1(pointList1,find,first_find);
    }
    if(pointList2.size()>0){
         mapWidget->setPoint2(pointList2,find,first_find);
    }
    ui->jingwei->setVisible(false);
    ui->jingwei_2->setVisible(false);
    ui->jingwei_3->setVisible(false);
    ui->jingwei_4->setVisible(true);
}


void MapForm::on_orbit_1_2_clicked()
{
    //显示无人机1,2的轨迹
    mapWidget->setAction(MapWidget::fir_sec_air);
    if(pointList1.size()>0){
        mapWidget->setPoint1(pointList1,find,first_find);
    }
    if(pointList2.size()>0){
         mapWidget->setPoint2(pointList2,find,first_find);
    }
    ui->jingwei->setVisible(true);
    ui->jingwei_2->setVisible(true);
    ui->jingwei_3->setVisible(false);
    ui->jingwei_4->setVisible(false);
}

void MapForm::on_orbit_3_4_clicked()
{
    //显示无人机3,4的轨迹
    mapWidget->setAction(MapWidget::thi_fou_air);
    if(pointList1.size()>0){
        mapWidget->setPoint1(pointList1,find,first_find);
    }
    if(pointList2.size()>0){
         mapWidget->setPoint2(pointList2,find,first_find);
    }
    ui->jingwei->setVisible(false);
    ui->jingwei_2->setVisible(false);
    ui->jingwei_3->setVisible(true);
    ui->jingwei_4->setVisible(true);

}

void MapForm::on_orbit_1_2_3_4_clicked()
{
    //显示无人机1,2,3,4的轨迹
    mapWidget->setAction(MapWidget::all_air);
    if(pointList1.size()>0){
        mapWidget->setPoint1(pointList1,find,first_find);
    }
    if(pointList2.size()>0){
         mapWidget->setPoint2(pointList2,find,first_find);
    }
    ui->jingwei->setVisible(true);
    ui->jingwei_2->setVisible(true);
    ui->jingwei_3->setVisible(true);
    ui->jingwei_4->setVisible(true);
}

void MapForm::on_large_clicked()
{
    if(mapWidget->width()==480){
        this->mapWidget->setAction(MapWidget::all_air);
        mapWidget->setGeometry(0,30,1920,1050);
        ui->video->setGeometry(3,33,480,263);
        mapWidget->show();
        ui->video->raise();
        ui->large->raise();
      //  ui->uav_text->raise();
        ui->jingwei->raise();
        ui->jingwei_2->raise();
        ui->jingwei_3->raise();
        ui->jingwei_4->raise();
       // ui->uav_text->setVisible(false);
        //ui->uav_text->setShowText("无人机型号");
        ui->jingwei->setVisible(true);
        ui->jingwei_2->setVisible(true);
        ui->jingwei_3->setVisible(true);
        ui->jingwei_4->setVisible(true);
        ui->zhiNanZhen->setVisible(false);
        ui->shuiPingYi->setVisible(false);
        ui->big->raise();
        ui->small->raise();
        ui->orbit_1->raise();
        ui->orbit_2->raise();
        ui->orbit_3->raise();
        ui->orbit_4->raise();
        ui->orbit_1_2->raise();
        ui->orbit_3_4->raise();
        ui->orbit_1_2_3_4->raise();
        ui->csscWarning->raise();
        ui->big->setVisible(true);
        ui->small->setVisible(true);
        ui->orbit_1->setVisible(true);
        ui->orbit_2->setVisible(true);
        ui->orbit_3->setVisible(true);
        ui->orbit_4->setVisible(true);
        ui->orbit_1_2->setVisible(true);
        ui->orbit_3_4->setVisible(true);
        ui->orbit_1_2_3_4->setVisible(true);
        ui->csscWarning->setVisible(true);
        if(pointList1.size()>0){
            mapWidget->setPoint1(pointList1,find,first_find);
        }
        if(pointList2.size()>0){
             mapWidget->setPoint2(pointList2,find,first_find);
        }
        mapWidget->update();
//        ui->video->raise();
    }else if(ui->video->width()==480){
        this->mapWidget->setAction(MapWidget::Large);
        ui->video->setGeometry(0,30,1920,1050);
        mapWidget->setGeometry(0,30,480,263);
        ui->video->show();
        mapWidget->raise();
        ui->large->raise();
    //    ui->uav_text->raise();
        ui->zhiNanZhen->raise();
        ui->shuiPingYi->raise();
    //    ui->uav_text->setVisible(false);
        //ui->uav_text->setShowText("UAV1");
        ui->jingwei->setVisible(false);
        ui->jingwei_2->setVisible(false);
        ui->jingwei_3->setVisible(false);
        ui->jingwei_4->setVisible(false);
        ui->zhiNanZhen->setVisible(true);
        ui->shuiPingYi->setVisible(true);
        ui->big->setVisible(false);
        ui->small->setVisible(false);
        ui->orbit_1->setVisible(false);
        ui->orbit_2->setVisible(false);
        ui->orbit_3->setVisible(false);
        ui->orbit_4->setVisible(false);
        ui->orbit_1_2->setVisible(false);
        ui->orbit_3_4->setVisible(false);
        ui->orbit_1_2_3_4->setVisible(false);
        ui->csscWarning->setVisible(false);
        if(pointList1.size()>0){
            mapWidget->setPoint1(pointList1,find,first_find);
        }
        if(pointList2.size()>0){
             mapWidget->setPoint2(pointList2,find,first_find);
        }
        mapWidget->update();
//        ui->video->lower();
//        ui->map->raise();
    }
}

