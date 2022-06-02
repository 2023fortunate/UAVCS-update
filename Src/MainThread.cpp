#include "include/Mainthread.h"
#include<QFile>
#include<QJsonParseError>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QDateTime>
#include<map>
MainThread::~MainThread()
{

}
void MainThread::slot_recieveMainMsg()
{
    qDebug()<<"Collecting MainWidget Data From Python...";
    QString ip = "10.198.166.129";
    //消息循环
    GD d;//初始化，连接服务器
    d.initA(ip.toStdString());
    extern int start;
    extern int finish1;
    extern int state;

    while(true)
    {
       QString AllData =  QString::fromStdString(d.AGet());//得到无人机名字和对应数据
     //  qDebug()<<"AllData"<<AllData;
      //  QString AllData = "{\"EnvironmentState\": {\"air_density\": 1.2107958793640137, \"air_pressure\": 99876.09375, \"geo_point\": {\"altitude\": 121.31859588623047, \"latitude\": 47.64148596630509, \"longitude\": -122.140165}, \"gravity\": {\"x_val\": 0, \"y_val\": 0, \"z_val\": 0}, \"position\": {\"x_val\": 0, \"y_val\": 0, \"z_val\": 0}, \"temperature\": 287.3614501953125}, \"UAV\": [{\"name\": \"UAV0\", \"collision\": {\"has_collided\": false, \"impact_point\": {\"x_val\": 0.0, \"y_val\": 0.0, \"z_val\": 0.6814025044441223}, \"normal\": {\"x_val\": 0.0, \"y_val\": 0.0, \"z_val\": 0.6814025044441223}, \"object_id\": -1, \"object_name\": \"\", \"penetration_depth\": 0.0, \"position\": {\"x_val\": 0.0, \"y_val\": 0.0, \"z_val\": 0.6814025044441223}, \"time_stamp\": 0}, \"gps_location\": {\"altitude\": 121.31859588623047, \"latitude\": 47.64148596630509, \"longitude\": -122.140165}, \"kinematics_estimated\": {\"angular_acceleration\": {\"x_val\": 0.0, \"y_val\": 0.0, \"z_val\": 0.6814025044441223}, \"angular_velocity\": {\"x_val\": 0.0, \"y_val\": 0.0, \"z_val\": 0.6814025044441223}, \"linear_acceleration\": {\"x_val\": 0.0, \"y_val\": 0.0, \"z_val\": 0.6814025044441223}, \"linear_velocity\": {\"x_val\": 0.0, \"y_val\": 0.0, \"z_val\": 0.6814025044441223}, \"orientation\": {\"w_val\": 0.9999998807907104, \"x_val\": 0.0, \"y_val\": 0.0, \"z_val\": 0.0}, \"position\": {\"x_val\": 0.0, \"y_val\": 0.0, \"z_val\": 0.6814025044441223}}, \"landed_state\": 0, \"rc_data\": {\"is_initialized\": false, \"is_valid\": false, \"left_z\": 0.0, \"pitch\": 0.0, \"right_z\": 0.0, \"roll\": 0.0, \"switches\": 0, \"throttle\": 0.0, \"timestamp\": 0, \"vendor_id\": \"\", \"yaw\": 0.0}, \"timestamp\": 1635556032782801152}, {\"name\": \"UAV1\", \"collision\": {\"has_collided\": false, \"impact_point\": {\"x_val\": 0.0, \"y_val\": 0.0, \"z_val\": 0.6814025044441223}, \"normal\": {\"x_val\": 0.0, \"y_val\": 0.0, \"z_val\": 0.6814025044441223}, \"object_id\": -1, \"object_name\": \"\", \"penetration_depth\": 0.0, \"position\": {\"x_val\": 0.0, \"y_val\": 0.0, \"z_val\": 0.6814025044441223}, \"time_stamp\": 0}, \"gps_location\": {\"altitude\": 121.31859588623047, \"latitude\": 47.64148596630509, \"longitude\": -122.140165}, \"kinematics_estimated\": {\"angular_acceleration\": {\"x_val\": 0.0, \"y_val\": 0.0, \"z_val\": 0.6814025044441223}, \"angular_velocity\": {\"x_val\": 0.0, \"y_val\": 0.0, \"z_val\": 0.6814025044441223}, \"linear_acceleration\": {\"x_val\": 0.0, \"y_val\": 0.0, \"z_val\": 0.6814025044441223}, \"linear_velocity\": {\"x_val\": 0.0, \"y_val\": 0.0, \"z_val\": 0.6814025044441223}, \"orientation\": {\"w_val\": 0.9999998807907104, \"x_val\": 0.0, \"y_val\": 0.0, \"z_val\": 0.0}, \"position\": {\"x_val\": 0.0, \"y_val\": 0.0, \"z_val\": 0.6814025044441223}}, \"landed_state\": 0, \"rc_data\": {\"is_initialized\": false, \"is_valid\": false, \"left_z\": 0.0, \"pitch\": 0.0, \"right_z\": 0.0, \"roll\": 0.0, \"switches\": 0, \"throttle\": 0.0, \"timestamp\": 0, \"vendor_id\": \"\", \"yaw\": 0.0}, \"timestamp\": 1635556032782801152}, {\"name\": \"UAV2\", \"collision\": {\"has_collided\": false, \"impact_point\": {\"x_val\": 0.0, \"y_val\": 0.0, \"z_val\": 0.6814025044441223}, \"normal\": {\"x_val\": 0.0, \"y_val\": 0.0, \"z_val\": 0.6814025044441223}, \"object_id\": -1, \"object_name\": \"\", \"penetration_depth\": 0.0, \"position\": {\"x_val\": 0.0, \"y_val\": 0.0, \"z_val\": 0.6814025044441223}, \"time_stamp\": 0}, \"gps_location\": {\"altitude\": 121.31859588623047, \"latitude\": 47.64148596630509, \"longitude\": -122.140165}, \"kinematics_estimated\": {\"angular_acceleration\": {\"x_val\": 0.0, \"y_val\": 0.0, \"z_val\": 0.6814025044441223}, \"angular_velocity\": {\"x_val\": 0.0, \"y_val\": 0.0, \"z_val\": 0.6814025044441223}, \"linear_acceleration\": {\"x_val\": 0.0, \"y_val\": 0.0, \"z_val\": 0.6814025044441223}, \"linear_velocity\": {\"x_val\": 0.0, \"y_val\": 0.0, \"z_val\": 0.6814025044441223}, \"orientation\": {\"w_val\": 0.9999998807907104, \"x_val\": 0.0, \"y_val\": 0.0, \"z_val\": 0.0}, \"position\": {\"x_val\": 0.0, \"y_val\": 0.0, \"z_val\": 0.6814025044441223}}, \"landed_state\": 0, \"rc_data\": {\"is_initialized\": false, \"is_valid\": false, \"left_z\": 0.0, \"pitch\": 0.0, \"right_z\": 0.0, \"roll\": 0.0, \"switches\": 0, \"throttle\": 0.0, \"timestamp\": 0, \"vendor_id\": \"\", \"yaw\": 0.0}, \"timestamp\": 1635556032782801152}, {\"name\": \"UAV3\", \"collision\": {\"has_collided\": false, \"impact_point\": {\"x_val\": 0.0, \"y_val\": 0.0, \"z_val\": 0.6814025044441223}, \"normal\": {\"x_val\": 0.0, \"y_val\": 0.0, \"z_val\": 0.6814025044441223}, \"object_id\": -1, \"object_name\": \"\", \"penetration_depth\": 0.0, \"position\": {\"x_val\": 0.0, \"y_val\": 0.0, \"z_val\": 0.6814025044441223}, \"time_stamp\": 0}, \"gps_location\": {\"altitude\": 121.31859588623047, \"latitude\": 47.64148596630509, \"longitude\": -122.140165}, \"kinematics_estimated\": {\"angular_acceleration\": {\"x_val\": 0.0, \"y_val\": 0.0, \"z_val\": 0.6814025044441223}, \"angular_velocity\": {\"x_val\": 0.0, \"y_val\": 0.0, \"z_val\": 0.6814025044441223}, \"linear_acceleration\": {\"x_val\": 0.0, \"y_val\": 0.0, \"z_val\": 0.6814025044441223}, \"linear_velocity\": {\"x_val\": 0.0, \"y_val\": 0.0, \"z_val\": 0.6814025044441223}, \"orientation\": {\"w_val\": 0.9999998807907104, \"x_val\": 0.0, \"y_val\": 0.0, \"z_val\": 0.0}, \"position\": {\"x_val\": 0.0, \"y_val\": 0.0, \"z_val\": 0.6814025044441223}}, \"landed_state\": 0, \"rc_data\": {\"is_initialized\": false, \"is_valid\": false, \"left_z\": 0.0, \"pitch\": 0.0, \"right_z\": 0.0, \"roll\": 0.0, \"switches\": 0, \"throttle\": 0.0, \"timestamp\": 0, \"vendor_id\": \"\", \"yaw\": 0.0}, \"timestamp\": 1635556032782801152}]}";
        QJsonDocument jsonDocument = QJsonDocument::fromJson(AllData.toLocal8Bit().data());
//            if( jsonDocument.isNull() ){
//                qDebug()<< "===> please check the string "<< AllData.toLocal8Bit().data();
//            }
        QJsonObject jsonObject = jsonDocument.object();
        extern int hisVideo;
        if(hisVideo==0||hisVideo==2){
//            qDebug() << "hisVideo1===" << hisVideo;
            emit sentUAVMainData(jsonObject);
        }

//        cv::waitKey(100);

        //第1个界面的文件储存
        if(start>0&&finish1==0){

//            QJsonObject obj;
            QJsonObject obj1;

            // 使用jsonFinalObject添加值，并写入文件
            // 获取当前时间戳
            qint64 timestamp = QDateTime::currentDateTime().toMSecsSinceEpoch(); //毫秒级
            count1++;
            obj1.insert("time", tr("%1").arg(timestamp));
            obj1.insert("state", state);
            obj1.insert("jsonObject", jsonObject);
            objFinal1.insert(QString::number(count1),obj1);
            clearJsonObject1(obj1);
            qDebug() << "count1="<<count1<<",finish1="<<finish1;
        }
        if(finish1==1&&finish2==0){
            QString strs1 = QString::fromStdString("D:\\UAVCS-update\\11.json");
            QFile file1(strs1);
            if(!file1.open(QIODevice::ReadWrite)) {
                qDebug() << "File1 open error";
            } else {
                qDebug() <<"File1 open!";
            }

    //        qDebug() <<"find1="+QString::number(find)+",finish1="+QString::number(finish1);
            // 清空文件中的原有内容
//            if(count1==0){
                file1.resize(0);
//            }
            //将obj转化为QDocument，写入到file1中
            QJsonDocument document1;
            document1.setObject(objFinal1);
            clearJsonObject1(objFinal1);
            qDebug() << "file1 write_before";
            file1.write(document1.toJson());
            file1.close();
            qDebug() << "file1 Write to file!";
            finish2=1;;
        }
    }
}

bool MainThread::removeFolderContent1(const QString &path)
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
void MainThread::clearJsonObject1(QJsonObject &object)
{
    QStringList strList = object.keys();

    for(int i = 0; i < strList.size(); ++i)
        object.remove(strList.at(i));
}

