#include "include/Airthread.h"
#include <QFile>
#include <QJsonParseError>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QDateTime>
#include <map>
AirThread::~AirThread()
{

}
void AirThread::slot_recieveAirSimMsg()
{
    //qDebug()<<"Collecting AirSim Data From Python...";
//    QString ip = "192.168.0.40";
    QString ip = "10.198.166.129";
    extern int start;
    extern int finish1;
    extern int state;

    //qDebug()<<"服务器ip="<<ip;
    //消息循环
    GD d(ip.toStdString(),"6666");//初始化，连接服务器
   // qDebug()<<"服务器ip="<<ip<<"1";
    d.Get();
    auto ALLName = d.GetALLName();
    gds.resize(ALLName.size());
    /*
    for(size_t i=0;i<ALLName.size();++i)
    {
        gds[i].init(ip.toStdString(),d.GetPort(ALLName[i]));
        pr[ALLName[i]] = i;
    }*/
    gds[0].init(ip.toStdString(),d.GetPort(ALLName[0]));
    curr_name = ALLName[0];
    //GV gv(ip.toStdString(),"6667");
    auto AllName = d.GetALLName();
    QStringList list;
    for(auto i:AllName){
         list.append(QString::fromStdString(i));
    }

    if(idx==0)
        emit sentUAVName(list);
    while(true)
    {
        d.Get();//刷新数据
        auto AllData = d.GetALLData();//得到无人机名字和对应数据
//        QString AllData1 =  QString::fromStdString(d.AGet());//得到无人机名字和对应数据
        AllName = d.GetALLName();//得到所有无人机的名字
        QString name = cBoxs[idx]->currentText();
        if(curr_name!=name.toStdString()&& !name.isEmpty())
        {
            gds[0].release();
            //std::cout<<curr_name<<" "<<name.toStdString()<<" "<<d.GetPort(name.toStdString())<<std::endl;
            gds[0].init(ip.toStdString(),d.GetPort(name.toStdString()));
            curr_name = name.toStdString();
        }
        auto datas = d.GetData(name.toStdString());
        QJsonObject uav;
        //qDebug()<<"datas="<<datas;
        uav.insert("index", idx);
        uav.insert("uav_name", name);
        uav.insert("locate_x", datas[0]);uav.insert("locate_y", datas[1]);uav.insert("locate_z", datas[2]);
        uav.insert("sudu_x", datas[3]);uav.insert("sudu_y", datas[4]);uav.insert("sudu_z", datas[5]);
//        uav.insert("angle_x", datas[6]);uav.insert("angle_y", datas[7]);uav.insert("angle_z", datas[8]);

       // qDebug()<<"uav="<<uav;
        QPixmap a= gds[0].GetImg();
        extern int hisVideo;
        if(hisVideo==0||hisVideo==2){
//            qDebug() << "hisVideo3===" << hisVideo;
            if(idx==0)
            {
                emit sentData(uav);
                emit sentImg(a,name,idx);
            }
            else if(idx==1)
            {
                emit sentData1(uav);
                emit sentImg1(a,name,idx);
            }
            else if(idx==2)
            {
                emit sentData2(uav);
                emit sentImg2(a,name,idx);
            }
            else if(idx==3)
            {
                emit sentData3(uav);
                emit sentImg3(a,name,idx);
            }

        }

        //第三个界面的文件储存
        if(count3[idx]==0){
            removeFolderContent3("D:/UAVCS-update/history/3/"+QString::number(idx+1)+"/");
            QString dir_str3 ="D:/UAVCS-update/history/3/"+QString::number(idx+1)+"/";
            // 检查目录是否存在，若不存在则新建
            QDir dir3;
            if(!dir3.exists(dir_str3))
            {
                   dir3.mkpath(dir_str3);
            }
        }
        if(start>0&&finish1==0){
            QJsonObject obj1;
            // 使用jsonFinalObject添加值，并写入文件
            // 获取当前时间戳
            qint64 timestamp = QDateTime::currentDateTime().toMSecsSinceEpoch(); //毫秒级
            QString pixPath = "D:/UAVCS-update/history/3/"+QString::number(idx+1)+"/"+QString::number(state)+"_"+tr("%1").arg(timestamp)+".png";
            a.save(pixPath);
            uav.insert("pixPath",pixPath);
            count3[idx]++;
//            count31++;
            obj1.insert("time", tr("%1").arg(timestamp));
            obj1.insert("state", state);
            obj1.insert("uav", uav);
            switch (idx) {
                case 0:
                   objFinal31.insert(QString::number(count3[0]),obj1);
                   clearJsonObject3(obj1);
                break;
                case 1:
                   objFinal32.insert(QString::number(count3[1]),obj1);
                   clearJsonObject3(obj1);
                break;
                case 2:
                   objFinal33.insert(QString::number(count3[2]),obj1);
                   clearJsonObject3(obj1);
                break;
                case 3:
                   objFinal34.insert(QString::number(count3[3]),obj1);
                   clearJsonObject3(obj1);
                break;
            }
//            objFinal3.insert(QString::number(count31),obj1);
//            clearJsonObject3(obj1);
            qDebug() << "count3"+QString::number(idx+1)+"="<<count3[idx]<<",finish1="<<finish1;
//            qDebug() << "count31"<<count31<<",finish1="<<finish1;

        }
        if(finish1==1&&finish2[idx]==0){
            QString strs3 = "D:\\UAVCS-update\\3"+QString::number(idx+1)+".json";
            QFile file3(strs3);
            if(!file3.open(QIODevice::ReadWrite)) {
                qDebug() << "File3"+QString::number(idx+1)+" open error";
            } else {
                qDebug() <<"File3"+QString::number(idx+1)+" open!";
            }
            // 清空文件中的原有内容
            file3.resize(0);
            //将obj转化为QDocument，写入到file中
            QJsonDocument document3;
            switch (idx) {
                case 0:
                    document3.setObject(objFinal31);
                    clearJsonObject3(objFinal31);
                break;
                case 1:
                    document3.setObject(objFinal32);
                    clearJsonObject3(objFinal32);
                break;
                case 2:
                    document3.setObject(objFinal33);
                    clearJsonObject3(objFinal33);
                break;
                case 3:
                    document3.setObject(objFinal34);
                    clearJsonObject3(objFinal34);
                break;

                default:
                        qDebug() << "idx="<<idx;
                break;
            }
            qDebug() << "file3"+QString::number(idx+1)+" write_before";
            file3.write(document3.toJson());
            file3.close();
            qDebug() << "file3"+QString::number(idx+1)+" Write to file!";
            finish2[idx]=1;
        }
//        if(finish1==1&&finish3==0){
//            QString strs3 = "D:\\UAVCS-update\\3.json";
//            QFile file3(strs3);
//            if(!file3.open(QIODevice::ReadWrite)) {
//                qDebug() << "File3 open error";
//            } else {
//                qDebug() <<"File3 open!";
//            }
//            // 清空文件中的原有内容
//            file3.resize(0);
//            //将obj转化为QDocument，写入到file中
//            QJsonDocument document3;
//            document3.setObject(objFinal3);
//            clearJsonObject3(objFinal3);
//            qDebug() << "file3 write_before";
//            file3.write(document3.toJson());
//            file3.close();
//            qDebug() << "file3 Write to file!";
//            finish3=1;
//        }
    }

}

bool AirThread::removeFolderContent3(const QString &path)
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
                removeFolderContent3(file.absoluteFilePath());
            }
        }
        return dir.rmpath(dir.absolutePath()); // 这时候文件夹已经空了，再删除文件夹本身
}
void AirThread::clearJsonObject3(QJsonObject &object)
{
    QStringList strList = object.keys();

    for(int i = 0; i < strList.size(); ++i)
        object.remove(strList.at(i));
}

