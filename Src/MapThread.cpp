#include "include/Mapthread.h"
#include<QFile>
#include<QJsonParseError>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QDateTime>
#include <map>

MapThread::~MapThread()
{

}
void MapThread::slot_recieveMapMsg()
{
    qDebug()<<"Collecting Map Image From Python...";
    QString ip = "10.198.166.129";
    extern int start;
    extern int finish1;
    extern int state;

//    //测试代码
//    QJsonArray uav;
//    QJsonObject uav1;
//    uav1.insert("uav_name","测试uav1");//无人机名字
//    uav1.insert("longitude", 100.0);//无人机经度
//    uav1.insert("latitude", 200.0);//无人机纬度
//    uav1.insert("pitch", 3.0);//水平姿态仪pitch
//    uav1.insert("roll", 4.0);//水平姿态仪roll
//    uav1.insert("yaw", 5.0);//指南针yaw
//    uav1.insert("x", 1);//位置x
//    uav1.insert("y", 2);//位置y
//    uav1.insert("x1", 3);//位置x
//    uav1.insert("y1", 4);//位置y
//    uav.append(uav1);

//    QJsonObject uav2;
//    uav2.insert("uav_name","测试uav2");//无人机名字
//    uav2.insert("longitude", 200.0);//无人机经度
//    uav2.insert("latitude", 300.0);//无人机纬度
//    uav2.insert("pitch", 4.0);//水平姿态仪pitch
//    uav2.insert("roll", 5.0);//水平姿态仪roll
//    uav2.insert("yaw", 6.0);//指南针yaw
//    uav2.insert("x", 7);//位置x
//    uav2.insert("y", 8);//位置y
//    uav2.insert("x1", 5);//位置x
//    uav2.insert("y1", 6);//位置y
//    uav.append(uav2);

//    QJsonObject uav3;
//    uav3.insert("uav_name","测试uav3");//无人机名字
//    uav3.insert("longitude", 300.0);//无人机经度
//    uav3.insert("latitude", 400.0);//无人机纬度
//    uav3.insert("pitch", 5.0);//水平姿态仪pitch
//    uav3.insert("roll", 6.0);//水平姿态仪roll
//    uav3.insert("yaw", 7.0);//指南针yaw
//    uav3.insert("x", 8);//位置x
//    uav3.insert("y", 7);//位置y
//    uav3.insert("x1", 2);//位置x
//    uav3.insert("y1", 3);//位置y
//    uav.append(uav3);

//    QJsonObject uav4;
//    uav4.insert("uav_name","测试uav4");//无人机名字
//    uav4.insert("longitude", 400.0);//无人机经度
//    uav4.insert("latitude", 500.0);//无人机纬度
//    uav4.insert("pitch", 6.0);//水平姿态仪pitch
//    uav4.insert("roll", 7.0);//水平姿态仪roll
//    uav4.insert("yaw", 8.0);//指南针yaw
//    uav4.insert("x", 9);//位置x
//    uav4.insert("y", 3);//位置y
//    uav4.insert("x1", 4);//位置x
//    uav4.insert("y1", 5);//位置y
//    uav.append(uav4);
//    emit sentUAVData(uav);


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

    gds[0].init(ip.toStdString(),"7777");
    curr_name = ALLName[0];
    //GV gv(ip.toStdString(),"6667");
    while(true)
    {
       // d.Get();//刷新数据
//        auto AllData = d.GetALLData();//得到无人机名字和对应数据
     //   AllName = d.GetALLName();//得到所有无人机的名字
     //   QString name = cBoxs[idx]->currentText();
//        if(curr_name!=name.toStdString()&& !name.isEmpty())
//        {
//            gds[0].release();
//            //std::cout<<curr_name<<" "<<name.toStdString()<<" "<<d.GetPort(name.toStdString())<<std::endl;
//            gds[0].init(ip.toStdString(),d.GetPort(name.toStdString()));
//            curr_name = name.toStdString();
//        }
      //  auto datas = d.GetData(name.toStdString());
// //        QString AllData =  QString::fromStdString(d.AGet());//得到无人机名字和对应数据
        //qDebug()<<AllData;
// //        QJsonDocument jsonDocument = QJsonDocument::fromJson(AllData.toLocal8Bit().data());
//        if( jsonDocument.isNull() ){
//            qDebug()<< "===> please check the string "<< AllData.toLocal8Bit().data();
//        }
      //  qDebug()<<"  AllData.toLocal8Bit().data()="<<AllData.toLocal8Bit().data();
      //  qDebug()<<"  jsonDocument="<<jsonDocument;
// //        QJsonObject jsonObject = jsonDocument.object();

// //        QJsonArray array = jsonObject.value("UAV").toArray();

//        QJsonArray uav;
//        for(int i=0;i<array.size();i++){
//            QJsonObject gps_location = array[i].toObject().value("gps_location").toObject();
//            QJsonObject yawangle = array[i].toObject().value("yawangle").toObject();
//            QJsonObject position = array[i].toObject().value("kinematics_estimated").toObject().value("position").toObject();
//            QJsonObject uav1;
//            uav1.insert("uav_name",array[i].toObject().value("name") );//无人机名字
//            uav1.insert("longitude", gps_location.value("longitude"));//无人机经度
//            uav1.insert("latitude", gps_location.value("latitude"));//无人机纬度
//            uav1.insert("pitch", yawangle.value("pitch"));//水平姿态仪pitch
//            uav1.insert("roll", yawangle.value("roll"));//水平姿态仪roll
//            uav1.insert("yaw", yawangle.value("yaw"));//指南针yaw
//            uav1.insert("x", position.value("x_val"));//位置x
//            uav1.insert("y", position.value("y_val"));//位置y
//            uav1.insert("x1", 0);//位置x
//            uav1.insert("y1", 0);//位置y
// //            uav1.insert("z", position.value("z_val"));//位置z
//     //       uav1.insert("z", obj.value("z_val"));
//            uav.append(uav1);
//        }
       // qDebug()<<"uav="<<uav;
        //QPixmap a= gds[pr[name.toStdString()]].GetImg();//获得图片
        QPixmap a= gds[0].GetImg();
        //qDebug()<<"uav="<<array;
//        emit sentUAVData(uav);//触发地图界面所有无人机经纬度的数据传送
        extern int hisVideo;
        if(hisVideo==0||hisVideo==2){
//            qDebug() << "hisVideo22===" << hisVideo;
            emit sentUAVImg(a);  //触发地图界面全局视图的无人机图像传送
        }

        //第二个界面的文件储存
        if(count2==0){
            removeFolderContent1("D:/UAVCS-update/history/2/");
            QString dir_str2 ="D:/UAVCS-update/history/2/";
            // 检查目录是否存在，若不存在则新建
            QDir dir2;
            if(!dir2.exists(dir_str2))
            {
                   dir2.mkpath(dir_str2);
            }
        }
        if(start>0&&finish1==0){
//            QJsonObject obj;
            QJsonObject obj1;

            // 使用jsonFinalObject添加值，并写入文件
            // 获取当前时间戳
            qint64 timestamp = QDateTime::currentDateTime().toMSecsSinceEpoch(); //毫秒级
            count2++;
            QString pixPath = "D:/UAVCS-update/history/2/"+QString::number(state)+"_"+tr("%1").arg(timestamp)+".png";
            a.save(pixPath);
            obj1.insert("time", tr("%1").arg(timestamp));
            obj1.insert("state", state);
            obj1.insert("pixPath", pixPath);
            objFinal2.insert(QString::number(count2),obj1);
            clearJsonObject1(obj1);
        }

        if(finish1==1&&finish2==0){
            QString strs2 = QString::fromStdString("D:\\UAVCS-update\\2.json");
            QFile file2(strs2);
            if(!file2.open(QIODevice::ReadWrite)) {
                qDebug() << "File21 open error";
            } else {
                qDebug() <<"File21 open!";
            }
//            qDebug() <<"find2="+QString::number(find)+",finish1="+QString::number(finish1);
            // 清空文件中的原有内容
            file2.resize(0);

            //将obj转化为QDocument，写入到file中
            QJsonDocument document2;
            document2.setObject(objFinal2);
            clearJsonObject1(objFinal2);
            qDebug() << "file21 write_before";
            file2.write(document2.toJson());
            file2.close();
            qDebug() << "file21 Write to file!";
            finish2=1;
        }

    }
}

bool MapThread::removeFolderContent1(const QString &path)
{
    if (path.isEmpty())
        {
              return false;
        }
        QDir dir(path);
        if(!dir.exists())
        {
            return true;
        }
        dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot); //设置过滤
        QFileInfoList fileList = dir.entryInfoList(); // 获取所有的文件信息
        foreach (QFileInfo file, fileList)
        { //遍历文件信息
            if (file.isFile())
            { // 是文件，删除
                file.dir().remove(file.fileName());
            }else
            { // 递归调用函数，删除子文件夹
                removeFolderContent1(file.absoluteFilePath());
            }
        }
        return dir.rmpath(dir.absolutePath()); // 这时候文件夹已经空了，再删除文件夹本身
}
void MapThread::clearJsonObject1(QJsonObject &object)
{
    QStringList strList = object.keys();

    for(int i = 0; i < strList.size(); ++i)
        object.remove(strList.at(i));
}

