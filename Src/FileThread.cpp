#include "Include/FileThread.h"
#include <QFile>
#include <QJsonParseError>
#include <QDateTime>
#include <map>

FileThread::~FileThread()
{

}
void FileThread::doWork()
{
    extern int hisVideo;
    extern int uav_state;
    extern double his_sudu;
    extern int uav_index;
    extern int restart;
    extern int stopThread;
    extern qint64 timelapse;
    QStringList name_list;
    qDebug() << "hisVideo file Start===" << hisVideo;
    qDebug() << "Writing Data To File...";
    qDebug() << "uav_state===="<<uav_state;
    qDebug() << "restart===="<<restart;

    count1 = 0;
    count21 = 0;
    count22 = 0;
    count31 = 0;
    count32 = 0;
    count33 = 0;
    count34 = 0;

    rootSize1 = 0;
    rootSize21 = 0;
    rootSize22 = 0;
    rootSize31 = 0;
    rootSize32 = 0;
    rootSize33 = 0;
    rootSize34 = 0;

    minTime={0,0};
    sigTime={0,0,0,0,0,0,0};

    if(hisVideo==1&&restart==0){
        //读json文件,并输出提示信息
        QFile loadFile1("D:\\UAVCS-update\\11.json");
        if(!loadFile1.open(QIODevice::ReadOnly))
        {
            qDebug() << "coundn't open projects json11!";
        }
        QByteArray allData1 = loadFile1.readAll();
        loadFile1.close();
        //报告json解析期间出现的错误
        QJsonParseError jsonError1;
        QJsonDocument jsonDoc1(QJsonDocument::fromJson(allData1, &jsonError1));
        if(jsonError1.error != QJsonParseError::NoError)
        {
            qDebug() << "json11 error!" << jsonError1.errorString();
        }
        QJsonObject rootObj1;
        QJsonObject rootObj11 = jsonDoc1.object();
        if(uav_state==2){
            int j=0;
            for (int i=0;i<rootObj11.size();i++) {
                int state = rootObj11.value(QString::number(i+1)).toObject().value("state").toInt();
                if(state==2){
                    j++;
                    rootObj1.insert(QString::number(j),rootObj11.value(QString::number(i+1)).toObject());
                }
            }
        }else{
            rootObj1 = rootObj11;
        }
//        qDebug() << "rootObj1" << rootObj1;
        rootSize1 = rootObj1.size();
        count1++;
        time1 = rootObj1.value(QString::number(count1)).toObject().toVariantMap().value("time").toLongLong();
        maxtime1 = rootObj1.value(QString::number(rootSize1)).toObject().toVariantMap().value("time").toLongLong();

        //读json文件,并输出提示信息
        QFile loadFile21("D:\\UAVCS-update\\12.json");
        if(!loadFile21.open(QIODevice::ReadOnly))
        {
            qDebug() << "coundn't open projects json12!";
        }
        QByteArray allData21 = loadFile21.readAll();
        loadFile21.close();

        //报告json解析期间出现的错误
        QJsonParseError jsonError21;
        QJsonDocument jsonDoc21(QJsonDocument::fromJson(allData21, &jsonError21));
        if(jsonError21.error != QJsonParseError::NoError)
        {
            qDebug() << "json12 error!" << jsonError21.errorString();
        }

        QJsonObject rootObj21;
        QJsonObject rootObj211 = jsonDoc21.object();
        if(uav_state==2){
            int j=0;
            for (int i=0;i<rootObj211.size();i++) {
                int state = rootObj211.value(QString::number(i+1)).toObject().value("state").toInt();
                if(state==2){
                    j++;
                    rootObj21.insert(QString::number(j),rootObj211.value(QString::number(i+1)).toObject());
                }
            }
        }else{
            rootObj21 = rootObj211;
        }

        rootSize21 = rootObj21.size();
        count21++;
        time21 = rootObj21.value(QString::number(count21)).toObject().toVariantMap().value("time").toLongLong();
        maxtime21 = rootObj21.value(QString::number(rootSize21)).toObject().toVariantMap().value("time").toLongLong();

        //读json文件,并输出提示信息
        QFile loadFile22("D:\\UAVCS-update\\2.json");
        if(!loadFile22.open(QIODevice::ReadOnly))
        {
            qDebug() << "coundn't open projects json2!";
        }
        QByteArray allData22 = loadFile22.readAll();
        loadFile22.close();

        //报告json解析期间出现的错误
        QJsonParseError jsonError22;
        QJsonDocument jsonDoc22(QJsonDocument::fromJson(allData22, &jsonError22));
        if(jsonError22.error != QJsonParseError::NoError)
        {
            qDebug() << "json22 error!" << jsonError22.errorString();
        }

        QJsonObject rootObj22;
        QJsonObject rootObj212 = jsonDoc22.object();
        if(uav_state==2){
            int j=0;
            for (int i=0;i<rootObj212.size();i++) {
                int state = rootObj212.value(QString::number(i+1)).toObject().value("state").toInt();
                if(state==2){
                    j++;
                    rootObj22.insert(QString::number(j),rootObj212.value(QString::number(i+1)).toObject());
                }
            }
        }else{
            rootObj22 = rootObj212;
        }

        rootSize22 = rootObj22.size();
        count22++;
        time22 = rootObj22.value(QString::number(count22)).toObject().toVariantMap().value("time").toLongLong();
        maxtime22 = rootObj22.value(QString::number(rootSize22)).toObject().toVariantMap().value("time").toLongLong();

        QFile loadFile31("D:\\UAVCS-update\\31.json");
        if(!loadFile31.open(QIODevice::ReadOnly))
        {
            qDebug() << "coundn't open projects json31!";
        }
        QByteArray allData31 = loadFile31.readAll();
        loadFile31.close();
        //报告json解析期间出现的错误
        QJsonParseError jsonError31;
        QJsonDocument jsonDoc31(QJsonDocument::fromJson(allData31, &jsonError31));
        if(jsonError31.error != QJsonParseError::NoError)
        {
            qDebug() << "json31 error!" << jsonError31.errorString();
        }

        QJsonObject rootObj31;
        QJsonObject rootObj311 = jsonDoc31.object();
        if(uav_state==2){
            int j=0;
            for (int i=0;i<rootObj311.size();i++) {
                int state = rootObj311.value(QString::number(i+1)).toObject().value("state").toInt();
                if(state==2){
                    j++;
                    rootObj31.insert(QString::number(j),rootObj311.value(QString::number(i+1)).toObject());
                }
            }
        }else{
            rootObj31 = rootObj311;
        }

        rootSize31 = rootObj31.size();
        count31++;
        time31 = rootObj31.value(QString::number(count31)).toObject().toVariantMap().value("time").toLongLong();
        maxtime31 = rootObj31.value(QString::number(rootSize31)).toObject().toVariantMap().value("time").toLongLong();
        QString uav_name1 = rootObj31.value("1").toObject().value("uav").toObject().value("uav_name").toString();
        name_list.append(uav_name1);

        QFile loadFile32("D:\\UAVCS-update\\32.json");
        if(!loadFile32.open(QIODevice::ReadOnly))
        {
            qDebug() << "coundn't open projects json32!";
        }
        QByteArray allData32 = loadFile32.readAll();
        loadFile32.close();
        //报告json解析期间出现的错误
        QJsonParseError jsonError32;
        QJsonDocument jsonDoc32(QJsonDocument::fromJson(allData32, &jsonError32));
        if(jsonError32.error != QJsonParseError::NoError)
        {
            qDebug() << "json32 error!" << jsonError32.errorString();
        }

        QJsonObject rootObj32;
        QJsonObject rootObj312 = jsonDoc32.object();
        if(uav_state==2){
            int j=0;
            for (int i=0;i<rootObj312.size();i++) {
                int state = rootObj312.value(QString::number(i+1)).toObject().value("state").toInt();
                if(state==2){
                    j++;
                    rootObj32.insert(QString::number(j),rootObj312.value(QString::number(i+1)).toObject());
                }
            }
        }else{
            rootObj32 = rootObj312;
        }

        rootSize32 = rootObj32.size();
        count32++;
        time32 = rootObj32.value(QString::number(count32)).toObject().toVariantMap().value("time").toLongLong();
        maxtime32 = rootObj32.value(QString::number(rootSize32)).toObject().toVariantMap().value("time").toLongLong();
        QString uav_name2 = rootObj32.value("1").toObject().value("uav").toObject().value("uav_name").toString();
        name_list.append(uav_name2);

        QFile loadFile33("D:\\UAVCS-update\\33.json");
        if(!loadFile33.open(QIODevice::ReadOnly))
        {
            qDebug() << "coundn't open projects json33!";
        }
        QByteArray allData33 = loadFile33.readAll();
        loadFile33.close();
        //报告json解析期间出现的错误
        QJsonParseError jsonError33;
        QJsonDocument jsonDoc33(QJsonDocument::fromJson(allData33, &jsonError33));
        if(jsonError33.error != QJsonParseError::NoError)
        {
            qDebug() << "json33 error!" << jsonError33.errorString();
        }
        QJsonObject rootObj33;
        QJsonObject rootObj313 = jsonDoc33.object();
        if(uav_state==2){
            int j=0;
            for (int i=0;i<rootObj313.size();i++) {
                int state = rootObj313.value(QString::number(i+1)).toObject().value("state").toInt();
                if(state==2){
                    j++;
                    rootObj33.insert(QString::number(j),rootObj313.value(QString::number(i+1)).toObject());
                }
            }
        }else{
            rootObj33 = rootObj313;
        }

        rootSize33 = rootObj33.size();
        count33++;
        time33 = rootObj33.value(QString::number(count33)).toObject().toVariantMap().value("time").toLongLong();
        maxtime33 = rootObj32.value(QString::number(rootSize33)).toObject().toVariantMap().value("time").toLongLong();
        QString uav_name3 = rootObj33.value("1").toObject().value("uav").toObject().value("uav_name").toString();
        name_list.append(uav_name3);

        QFile loadFile34("D:\\UAVCS-update\\34.json");
        if(!loadFile34.open(QIODevice::ReadOnly))
        {
            qDebug() << "coundn't open projects json34!";
        }
        QByteArray allData34 = loadFile34.readAll();
        loadFile34.close();
        //报告json解析期间出现的错误
        QJsonParseError jsonError34;
        QJsonDocument jsonDoc34(QJsonDocument::fromJson(allData34, &jsonError34));
        if(jsonError34.error != QJsonParseError::NoError)
        {
            qDebug() << "json34 error!" << jsonError34.errorString();
        }

        QJsonObject rootObj34;
        QJsonObject rootObj314 = jsonDoc34.object();
        if(uav_state==2){
            int j=0;
            for (int i=0;i<rootObj314.size();i++) {
                int state = rootObj314.value(QString::number(i+1)).toObject().value("state").toInt();
                if(state==2){
                    j++;
                    rootObj34.insert(QString::number(j),rootObj314.value(QString::number(i+1)).toObject());
                }
            }
        }else{
            rootObj34 = rootObj314;
        }

        rootSize34 = rootObj34.size();
        count34++;
        time34 = rootObj34.value(QString::number(count34)).toObject().toVariantMap().value("time").toLongLong();
        maxtime34 = rootObj32.value(QString::number(rootSize34)).toObject().toVariantMap().value("time").toLongLong();
        QString uav_name4 = rootObj34.value("1").toObject().value("uav").toObject().value("uav_name").toString();
        name_list.append(uav_name4);

        int sumRoot = sumOfCount(rootSize1,rootSize21,rootSize22,rootSize31,rootSize32,rootSize33,rootSize34);
        minTime[0] = findMin(time1,time21,time22,time31,time32,time33,time34);
        minTime1 = minTime[0];
        maxTime = findMax(maxtime1,maxtime21,maxtime22,maxtime31,maxtime32,maxtime33,maxtime34);
        timeLength = maxTime-minTime1;


        if(count1<rootSize1&&count21<rootSize21&&count22<rootSize22&&count31<rootSize31&&count32<rootSize32&&count33<rootSize33&&count34<rootSize34){

            emit sentUAVName(name_list);
            qDebug() << "count1=" << count1<<",count21"<<count21<<",count22"<<count22<<",count31"<<count31<<",count32"<<count32<<",count33"<<count33<<",count34"<<count34;
            qDebug() << "rootSize1=" << rootSize1<<",rootSize21"<<rootSize21<<",rootSize22"<<rootSize22<<",rootSize31"<<rootSize31<<",rootSize32"<<rootSize32<<",rootSize33"<<rootSize33<<",rootSize34"<<rootSize34;
            qDebug() << "time1=" << time1<<",time21"<<time21<<",time22"<<time22<<",time31"<<time31<<",time32"<<time32<<",time33"<<time33<<",time34"<<time34;
            qDebug() << "minTime=" << minTime;
            qDebug() << "sigTime=" << sigTime;
            for (int i=0;i<sumRoot;i++) {
                if(restart==1||stopThread==1){
                    break;
                }else{
                    if(time1==minTime[0]&&sigTime[0]==0){
                        QJsonObject uavJson1 = rootObj1.value(QString::number(count1)).toObject().value("jsonObject").toObject();
                        emit sentUAVMainData(uavJson1);
                        if(count1>0&&count1<rootSize1){
                            count1++;
                            time1 = rootObj1.value(QString::number(count1)).toObject().toVariantMap().value("time").toLongLong();
                        }else{
                            sigTime[0]=1;
                        }
                    }
                    if(time21==minTime[0]&&sigTime[1]==0){
                        QJsonArray uav21 = rootObj21.value(QString::number(count21)).toObject().value("uav").toArray();
                        emit sentUAVData(uav21);//触发地图界面所有无人机经纬度的数据传送
                        if(count21>0&&count21<rootSize21){
                            count21++;
                            time21 = rootObj21.value(QString::number(count21)).toObject().toVariantMap().value("time").toLongLong();
                        }else{
                            sigTime[1]=1;
                        }
                    }
                    if(time22==minTime[0]&&sigTime[2]==0){
                        QString pixPath22 = rootObj22.value(QString::number(count22)).toObject().value("pixPath").toString();
                        QPixmap pixmap22;
                        pixmap22.load(pixPath22);
                        emit sentUAVImg(pixmap22);  //触发地图界面全局视图的无人机图像传送
                        if(count22>0&&count22<rootSize22){
                            count22++;
                            time22 = rootObj22.value(QString::number(count22)).toObject().toVariantMap().value("time").toLongLong();
                        }else{
                            sigTime[2]=1;
                        }
                    }
                    if(time31==minTime[0]&&sigTime[3]==0){
                        QJsonObject uav31 = rootObj31.value(QString::number(count31)).toObject().value("uav").toObject();
                        QString name31 = uav31.value("uav_name").toString();
                        int idx31 = uav31.value("index").toInt();
                        QString pixPath31 = uav31.value("pixPath").toString();
                        QPixmap pixmap31;
                        pixmap31.load(pixPath31);
                        emit sentData(uav31);
                        emit sentImg(pixmap31,name31,idx31);
                        if(count31>0&&count31<rootSize31){
                            count31++;
                            time31 = rootObj31.value(QString::number(count31)).toObject().toVariantMap().value("time").toLongLong();
                        }else{
                            sigTime[3]=1;
                        }
                    }
                    if(time32==minTime[0]&&sigTime[4]==0){
                        QJsonObject uav32 = rootObj32.value(QString::number(count32)).toObject().value("uav").toObject();
                        QString name32 = uav32.value("uav_name").toString();
                        int idx32 = uav32.value("index").toInt();
                        QString pixPath32 = uav32.value("pixPath").toString();
                        QPixmap pixmap32;
                        pixmap32.load(pixPath32);
                        emit sentData1(uav32);
                        emit sentImg1(pixmap32,name32,idx32);
                        if(count32>0&&count32<rootSize32){
                            count32++;
                            time32 = rootObj32.value(QString::number(count32)).toObject().toVariantMap().value("time").toLongLong();
                        }else{
                            sigTime[4]=1;
                        }
                    }
                    if(time33==minTime[0]&&sigTime[5]==0){
                        QJsonObject uav33 = rootObj33.value(QString::number(count33)).toObject().value("uav").toObject();
                        QString name33 = uav33.value("uav_name").toString();
                        int idx33 = uav33.value("index").toInt();
                        QString pixPath33 = uav33.value("pixPath").toString();
                        QPixmap pixmap33;
                        pixmap33.load(pixPath33);
                        emit sentData2(uav33);
                        emit sentImg2(pixmap33,name33,idx33);
                        if(count33>0&&count33<rootSize33){
                            count33++;
                            time33 = rootObj33.value(QString::number(count33)).toObject().toVariantMap().value("time").toLongLong();
                        }else{
                            sigTime[5]=1;
                        }
                    }
                    if(time34==minTime[0]&&sigTime[6]==0){
                        QJsonObject uav34 = rootObj34.value(QString::number(count34)).toObject().value("uav").toObject();
                        QString name34 = uav34.value("uav_name").toString();
                        int idx34 = uav34.value("index").toInt();
                        QString pixPath34 = uav34.value("pixPath").toString();
                        QPixmap pixmap34;
                        pixmap34.load(pixPath34);
                        emit sentData3(uav34);
                        emit sentImg3(pixmap34,name34,idx34);
                        if(count34>0&&count34<rootSize34){
                            count34++;
                            time34 = rootObj34.value(QString::number(count34)).toObject().toVariantMap().value("time").toLongLong();
                        }else{
                            sigTime[6]=1;
                        }
                    }

                    minTime[1] = minTime[0];
                    minTime[0] = findMin(time1,time21,time22,time31,time32,time33,time34);
    //                qDebug() << "his_sudu==="<<his_sudu ;

//                    if(timelapse==90000){
//                        timelapse1=timeLength/2;
//                    }else if(timelapse==30000||timelapse==60000){
//                        timelapse1 = timelapse;
//                    }
//                   qDebug() <<",timelapse1==="<<timelapse1<<",timelapse==="<<timelapse;
                   if(minTime[0]!=9999999999999){
                       if(minTime[0]>minTime1+timelapse){
//                           qDebug() <<"timelapse到了=============222222222";
                           Sleep((minTime[0]-minTime[1])/his_sudu);
                       }else{
//                           qDebug() <<"timelapse没到=============111111111";
                           Sleep(1);
                       }

                    }
                }

            }
                emit resultReady();
        }


    }
}


qint64 FileThread::findMin(qint64 t1,qint64 t2,qint64 t3,qint64 t4,qint64 t5,qint64 t6,qint64 t7){
    QVector<qint64> data {t1, t2, t3, t4, t5, t6, t7};
    for (int i=0;i<7;i++) {
        if(sigTime[i]==1){
            data[i]=9999999999999;
        }
    }
    qint64 minimum = *std::min_element(std::begin(data), std::end(data));
    return minimum;

}
qint64 FileThread::findMax(qint64 t1,qint64 t2,qint64 t3,qint64 t4,qint64 t5,qint64 t6,qint64 t7){
    QVector<qint64> data {t1, t2, t3, t4, t5, t6, t7};
    qint64 maxmum = *std::max_element(std::begin(data), std::end(data));
    return maxmum;
}

int FileThread::sumOfCount(int t1,int t2,int t3,int t4,int t5,int t6,int t7){
    int maxmum = t1+t2+t3+t4+t5+t6+t7;
    return maxmum;
}
