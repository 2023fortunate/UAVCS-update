#include "include/MapDatathread.h"
#include<QFile>
#include<QJsonParseError>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QDateTime>
#include <map>

MapDataThread::~MapDataThread()
{

}
int start;
int finish1;
int state;
void MapDataThread::slot_recieveMapDataMsg()
{
    qDebug()<<"Collecting Map Data From Python...";
    QString ip = "10.198.166.129";

    //消息循环
    GD d(ip.toStdString(),"6666");//初始化，连接服务器
//    GD d;//初始化，连接服务器
    d.initA(ip.toStdString());
    d.Get();
    auto ALLName = d.GetALLName();
    gds.resize(ALLName.size());
    /*
    for(size_t i=0;i<ALLName.size();++i)
    {
        gds[i].init(ip.toStdString(),d.GetPort(ALLName[i]));
        pr[ALLName[i]] = i;
    }*/

//    gds[0].init(ip.toStdString(),"7777");


    curr_name = ALLName[0];
//    GV gv(ip.toStdString(),"6667");
    while(true)
    {

        d.Get();//刷新数据
//        auto AllData = d.GetALLData();//得到无人机名字和对应数据
//        AllName = d.GetALLName();//得到所有无人机的名字
     //   QString name = cBoxs[idx]->currentText();
//        if(curr_name!=name.toStdString()&& !name.isEmpty())
//        {
//            gds[0].release();
//            //std::cout<<curr_name<<" "<<name.toStdString()<<" "<<d.GetPort(name.toStdString())<<std::endl;
//            gds[0].init(ip.toStdString(),d.GetPort(name.toStdString()));
//            curr_name = name.toStdString();
//        }
      //  auto datas = d.GetData(name.toStdString());
        QString AllData2 =  QString::fromStdString(d.AGet());//得到无人机名字和对应数据
//        qDebug()<<"AllData2="<<AllData2;
        QJsonDocument jsonDocument2 = QJsonDocument::fromJson(AllData2.toLocal8Bit().data());
//        if( jsonDocument.isNull() ){
//            qDebug()<< "===> please check the string "<< AllData.toLocal8Bit().data();
//        }
      //  qDebug()<<"  AllData.toLocal8Bit().data()="<<AllData.toLocal8Bit().data();
//        qDebug()<<"  jsonDocument="<<jsonDocument2;
        QJsonObject jsonObject2 = jsonDocument2.object();

        QJsonArray array2 = jsonObject2.value("UAV").toArray();
        QJsonObject drone1 = jsonObject2.value("Drone").toObject();//这儿不对。json里找不到Drone
        QJsonArray findmsg = jsonObject2.value("pointmeg").toArray();
        int find = findmsg.size();

        QJsonArray uav2;
        if(find == 0){
            first_find = 0;
        }
        if(record[0] == 0 && record[1] == 1 && find > 0){
            first_find = 1;
        }else{
            first_find = 0;
        }
        QJsonObject drone;
        drone.insert("uav_name","Drone");
        drone.insert("x",drone1.value("x_val"));
        drone.insert("y",drone1.value("y_val"));
        drone.insert("find", find);//发现无人机的数目
        drone.insert("first_find", first_find);//是否是初次发现，初次发现置1，否则置0

        for(int i=0;i<array2.size();i++){
            QJsonObject gps_location = array2[i].toObject().value("gps_location").toObject();
            QJsonObject yawangle = array2[i].toObject().value("yawangle").toObject();
            QJsonObject position = array2[i].toObject().value("kinematics_estimated").toObject().value("position").toObject();
            QJsonObject uav1;            
            QJsonObject find_point = findmsg[i].toObject();

            uav1.insert("uav_name",array2[i].toObject().value("name") );//无人机名字
            uav1.insert("longitude", gps_location.value("longitude"));//无人机经度
            uav1.insert("latitude", gps_location.value("latitude"));//无人机纬度
            uav1.insert("pitch", yawangle.value("pitch"));//水平姿态仪pitch
            uav1.insert("roll", yawangle.value("roll"));//水平姿态仪roll
            uav1.insert("yaw", yawangle.value("yaw"));//指南针yaw
            uav1.insert("x", position.value("x_val"));//无人机位置x
            uav1.insert("y", position.value("y_val"));//无人机位置y
            uav1.insert("find", find);//发现无人机的数目
            uav1.insert("first_find", first_find);//是否是初次发现，初次发现置1，否则置0
            if(find == 0 || i > 4){
                uav1.insert("x1", 0);//未发现敌机时，围捕点位置x1置0
                uav1.insert("y1", 0);//未发现敌机时，围捕点位置y2置0
            }else{
                uav1.insert("x1", find_point.value("x_val"));//发现敌机后，围捕点位置x1置正常数值
                uav1.insert("y1", find_point.value("y_val"));//发现敌机后，围捕点位置y1置正常数值
            }
//            uav1.insert("z", position.value("z_val"));//位置z
     //       uav1.insert("z", obj.value("z_val"));
            if(start==0){
                QVector<double> z={
                    0.0,
                    0.0
                };
                if(i==0){
                    z[1]=z[0];
                    z[0] = position.value("z_val").toDouble();
                    if(z[0]-z[1]!=0.0){
                        start = 1;
                    }
                }
            }
            uav2.append(uav1);
        }
        uav2.append(drone);
//        qDebug()<<"uav="<<uav2;
        record[0] = record[1];
        if(find>0){
            record[1] = 1;
        }else if(find==0){
            record[1] = 0;
        }

        //QPixmap a= gds[pr[name.toStdString()]].GetImg();//获得图片
//        QPixmap a= gds[0].GetImg();
        //qDebug()<<"uav="<<array;
        extern int hisVideo;
        if(hisVideo==0||hisVideo==2){
             QJsonArray CanSee = jsonObject2.value("CanSee").toArray();
             //围捕成功后，使四窗格放大到1大3小
             for (int i=0;i<CanSee.size();i++) {
                 QJsonArray CanSeeUAV = CanSee[i].toObject().value("UAV").toArray();
 //                QString firstName = CanSee[i].toObject().value("name").toString();
                 if(CanSeeUAV.size()>0&&find>0){
                     for (int i=0;i<CanSeeUAV.size();i++) {
                         if(CanSeeUAV[i].toObject().value("name").toString()=="Drone"){
                             if(first_find==1){
                                 qDebug()<<"发现敌机，i="<<i;
                                 finish3 = 1;
                                 emit RefreshUAV(i);
                             }
                         }
                     }
                 }
             }
//            qDebug() << "hisVideo21===" << hisVideo;            
             emit sentUAVData(uav2);//触发地图界面所有无人机经纬度的数据传送
    //        emit sentUAVImg(a);  //触发地图界面全局视图的无人机图像传送          
        }
        extern int finish4;
//        qDebug() << "finish4="<<finish4;
        finish1 = finish4;
        if(start==0){
            state = 0;//未巡航
        }else if(first_find==0&&finish3==0){
            state = 1;//巡航
        }
        if(find>0&&finish3==1&&finish1==0){
            state = 2;//围捕
        }
        if(finish3==1&&finish1==1){
            state = 3;//结束围捕
        }

        //第二个界面的文件储存
        if(start>0&&finish1==0){
            QJsonObject obj1;
            // 使用jsonFinalObject添加值，并写入文件
            // 获取当前时间戳
            qint64 timestamp = QDateTime::currentDateTime().toMSecsSinceEpoch(); //毫秒级
            count2++;
            obj1.insert("time", tr("%1").arg(timestamp));
            obj1.insert("state", state);
            obj1.insert("uav", uav2);
            objFinal2.insert(QString::number(count2),obj1);
            clearJsonObject(obj1);
            qDebug() << "count2="<<count2<<",finish1="<<finish1;
            for (int i=0;i<4;i++) {
                qDebug()<<"x="<<uav2[i].toObject().value("x").toDouble()<<",x1="<<uav2[i].toObject().value("x1").toDouble()<<",y="<<uav2[i].toObject().value("y").toDouble()<<",y1="<<uav2[i].toObject().value("y1").toDouble();
            }
        }

        if(finish1==1&&finish2==0){
            QString strs2 = QString::fromStdString("D:\\UAVCS-update\\12.json");
            QFile file2(strs2);
            if(!file2.open(QIODevice::ReadWrite)) {
                qDebug() << "File2 open error";
            } else {
                qDebug() <<"File2 open!";
            }
//            qDebug() <<"find2="+QString::number(find)+",finish1="+QString::number(finish1);
            // 清空文件中的原有内容
//            if(count2==0){
                file2.resize(0);
//            }
            //将obj转化为QDocument，写入到file中
            QJsonDocument document2;
            document2.setObject(objFinal2);
            clearJsonObject(objFinal2);
            qDebug() << "file2 write_before";
            file2.write(document2.toJson());
            file2.close();
            qDebug() << "file2 Write to file!";
            finish2=1;
        }
    }
}

void MapDataThread::clearJsonObject(QJsonObject &object)
{
    QStringList strList = object.keys();

    for(int i = 0; i < strList.size(); ++i)
        object.remove(strList.at(i));
}
