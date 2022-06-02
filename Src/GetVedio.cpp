#include "Include/GetVedio.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cstring>
#include <QTime>
#include <QTimer>
#include <qdatetime.h>
GV::GV(){}
GV::~GV()
{

    zmq_disconnect(sub,a.data());
    zmq_close(sub);
    zmq_close(context);
    delete [] buf;

}
void GV::release()
{
    zmq_disconnect(sub,a.data());
    zmq_close(sub);
    zmq_close(context);
    delete [] buf;
}
//初始化
/*ip:服务器ip  port：服务器数据端口（5555）*/
GV::GV(std::string ip, std::string port)
{
    //std::cout<<"hello\n";
    int rc;
    context = zmq_ctx_new();

    sub = zmq_socket(context, ZMQ_SUB);
    int trueValue = 1;
    rc = zmq_setsockopt(sub,ZMQ_CONFLATE,&trueValue,sizeof(trueValue));
    //qDebug()<<"rc: "<<rc<<"\n";
    int zs = 10;
    rc = zmq_setsockopt(sub,ZMQ_RCVHWM,&zs,sizeof (int));
    //qDebug()<<"hwm rc: "<<rc<<"\n";
    a = "tcp://" + ip + ":" + port;
    //std::cout<<a<<std::endl;
    rc = zmq_connect(sub, a.data());
    qDebug()<<"succaess\n";
    zmq_setsockopt(sub, ZMQ_SUBSCRIBE, "", 0);


    assert(rc == 0);

    buf = new char[2054097];
}

void GV::init(std::string ip, std::string port)
{
    int rc;
    context = zmq_ctx_new();

    sub = zmq_socket(context, ZMQ_SUB);
    int trueValue = 1;
    rc = zmq_setsockopt(sub,ZMQ_CONFLATE,&trueValue,sizeof(trueValue));
//    qDebug()<<"rc: "<<rc<<"\n";
    int zs = 10;
    rc = zmq_setsockopt(sub,ZMQ_RCVHWM,&zs,sizeof (int));
//    qDebug()<<"hwm rc: "<<rc<<"\n";
    a = "tcp://" + ip + ":" + port;
    qDebug()<<"a.data()=="<<a.data();
    rc = zmq_connect(sub, a.data());

    zmq_setsockopt(sub, ZMQ_SUBSCRIBE, "", 0);


    assert(rc == 0);

    buf = new char[2054097];
}

std::pair<int,char*> GV::GetVedio()
{
    //std::cout<<"123123132123 " <<sizeof(buf) - 1<<std::endl;
//    QDateTime dateTime = QDateTime::currentDateTime();
//    QString timestamp1 = dateTime.toString("ss.zzz");
      int num = zmq_recv(sub, buf, 2054096, 0);
//    dateTime = QDateTime::currentDateTime();
//    QString timestamp2 = dateTime.toString("ss.zzz");
//    qDebug()<<timestamp1<<" "<<timestamp2<<"\n";
    //std::cout<<num<<std::endl;
    buf[num] = '\0';
    return std::make_pair(num,buf);
}

//获得图片
QPixmap GV::GetImg()
{
    //std::cout<<"times:"<<"\n";
   // std::cout<<timestap1.toStdString()<<"\n";
    QImage image;
    auto ab = GetVedio();
    //std::cout<<ab.first<<std::endl;
    cv::Mat img_decode;
    std::vector<uchar> data_replay;
    data_replay.resize(ab.first+1);
    std::memcpy(data_replay.data(),ab.second,ab.first);
    img_decode = cv::imdecode(data_replay,cv::IMREAD_UNCHANGED);
    cv::Mat ret_img;
    cv::cvtColor(img_decode,ret_img,cv::COLOR_BGR2RGB);
    data_replay.clear();
   // cv::imshow("123",img_decode);

    //std::cout<<"fucking channel is "<<img_decode.depth()<<std::endl;
    QImage img = QImage((const unsigned char*)(ret_img.data),
                        ret_img.cols,ret_img.rows,QImage::Format_RGB888);
    //cv::Mat mt =cv::imdecode(un,CV_LOAD_IMAGE_COLOR);
    //QByteArray byteArray(ab.second,ab.first);

   // img.loadFromData(byteArray,"png");
    QPixmap ret = QPixmap::fromImage(img);
    //std::cout<<timestap1.toStdString()<<" "<<timestap2.toStdString()<<" "<<timestap3.toStdString()<<" "<<timestap4.toStdString()<<"\n";
    return ret;
}

//这个示例是在一个label上播放第一个无人机的视频
//void T(QLabel *label)
//{
//    QString ip = "192.168.1.106";
//    GD gd(ip,"6666");//连接数据端
//    gd.Get();//刷新数据
//    QString name = gd.GetALLName()[0];//获得第一个无人机的名字
//    QString port = gd.GetPort(name);//获得无人机name的端口
//    GV gv(ip,port);//连接无人机端口
//    label->resize(256,140);
//    while(1)
//    {
//        QPixmap a= gv.GetImg();//获得图片
//        label->setPixmap(a);//显示图片
//    }
//}
