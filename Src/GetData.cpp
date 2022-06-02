#include"Include/GetData.h"
#include<QDateTime>
GD::GD()
{
}
GD::~GD()
{
    zmq_close(sub);
    zmq_close(context_data);
}



/*
初始化：
ip:服务器ip
port：服务器数据端口（5555）
*/
GD::GD(std::string ip, std::string port)
{
    //std::cout<<"12123\n";
    context_data = zmq_ctx_new();
    sub = zmq_socket(context_data, ZMQ_SUB);
    int trueValue = 1;
    zmq_setsockopt(sub,ZMQ_CONFLATE,&trueValue,sizeof(trueValue));
    std::string a = "tcp://" + ip + ":" + port;
    tar_ip = ip;
    int rc = zmq_connect(sub, a.data());
    //std::cout<<"121231\n";
    assert(rc == 0);
    rc = zmq_setsockopt(sub, ZMQ_SUBSCRIBE, "", 0);
    context_REP = zmq_ctx_new();
    sub_REP = zmq_socket(context_REP, ZMQ_REQ);
    std::string ipaddr = "tcp://"+ip+":5555";
    zmq_connect(sub_REP, ipaddr.data());

    char send_buf[] = "start";
    char* sendBuf =  send_buf;
    char recvBuf[1000] = { 0 };
    int bytes = zmq_send(sub_REP, sendBuf, strlen(sendBuf) + 1, 0);
    zmq_recv(sub_REP, buf, sizeof(buf) - 1, 0);
    Json::Reader reader;
    Json::Value root;
   // std::cout <<"1: "<< buf << std::endl;

    if (reader.parse(buf, root))
    {
        std::string ac = root.asString();
        //std::cout << ac << std::endl;
        int cnt = 0;
        reader.parse(ac, root);
        //std::cout << root["UAVedio"].size() << std::endl;
        for (auto i : root["UAVedio"])
        {
            //std::cout << i << std::endl;
            cnt++;
            //Json::Value ye;
            //reader.parse(i.asString(), ye);
            uav[cnt].name = i["name"].asString();
            uav[cnt].port = i["port"].asString();
           // std::cout << "ok" << std::endl;
            //std::cout << uav[cnt].name << " " << uav[cnt].port << std::endl;
            mp[uav[cnt].name] = uav[cnt].port;
            mp1[uav[cnt].name] = cnt;
        }
        num = cnt;
    }
    else {
        std::cout << "2" << std::endl;
    }

}

void GD::initA(std::string ipdz)
{
    all_data = zmq_ctx_new();
    int trueValue = 1;
    zmq_setsockopt(sub_ALL,ZMQ_CONFLATE,&trueValue,sizeof(trueValue));
    //zmq_setsockopt(sub_ALL,ZMQ_VMCI_BUFFER_SIZE,&trueValue,sizeof(trueValue));
    sub_ALL = zmq_socket(all_data,ZMQ_SUB);
    std::string a_ip = "tcp://"+ipdz+":6664";
    int sb = zmq_connect(sub_ALL,a_ip.data());
    assert(sb==0);
    zmq_setsockopt(sub_ALL,ZMQ_SUBSCRIBE,"",0);
}
std::string GD::AGet()
{
    int num = zmq_recv(sub_ALL, buf, sizeof(buf) - 1, 0);
    //std::cout<<"\n\n\n\n"<<num<<std::endl;
    std::string ret(buf,num);
    return ret;

}
//获得、刷新数据
//每一段时间都要使用这个函数来刷新数据
void GD::Get()
{
        int num = zmq_recv(sub, buf, sizeof(buf) - 1, 0);


       //std::cout << buf << std::endl;
       Json::Reader reader;
       Json::Value root;
       if (reader.parse(buf, root))
          {
              int i = 0;
              for (auto j:root)
              {
                  Json::Value ye;
                  std::string name = j.asString();
                  reader.parse(name, ye);
                  i = mp1[ye["name"].asString()];
                  uav[i].pos.x = ye["posx"].asDouble();
                  uav[i].pos.y = ye["posy"].asDouble();
                  uav[i].pos.z = ye["posz"].asDouble();
                  uav[i].vel.x = ye["velx"].asDouble();
                  uav[i].vel.y = ye["vely"].asDouble();
                  uav[i].vel.z = ye["velz"].asDouble();
                  uav[i].yaw.x = ye["yawx"].asDouble();
                  uav[i].yaw.y = ye["yawy"].asDouble();
                  uav[i].yaw.z = ye["yawz"].asDouble();
              }
          }
}

//获得无人机数量
int GD::GetNum()
{
    return num;
}


//获得所有无人机的名称
std::vector<std::string> GD::GetALLName()
{
    std::vector<std::string> ret;
    for (int i = 1; i <= num; ++i)
    {
        ret.push_back(uav[i].name);
    }
    return ret;
}


/*
获得某个无人机的端口
通过输入无人机的名称获得其对应端口
*/
std::string GD::GetPort(std::string name)

{
    return mp[name];
}


/*
获得所有无人机端口
每一个pair第一个存无人机名称，第二个为对应的端口
*/
std::vector<std::pair<std::string, std::string>> GD::GetALLPort()
{
    std::vector<std::pair<std::string, std::string>> ret;
    for (int i = 1; i <= num; ++i)
    {
        ret.push_back(std::make_pair(uav[i].name, uav[i].port));
    }
    return ret;
}


//获得某个无人机的数据
/*
获得名字为name的无人机的数据
返回值为一个长度为9的向量
其中前三个为位置的xyz数值
中间三个为线速度的xyz值
后三位为偏转角的xyz值
*/
std::vector<double> GD::GetData(std::string name)
{
    std::vector<double> ret;
    int idx = mp1[name];
    ret.push_back(uav[idx].pos.x); ret.push_back(uav[idx].pos.y); ret.push_back(uav[idx].pos.z);
    ret.push_back(uav[idx].vel.x); ret.push_back(uav[idx].vel.y); ret.push_back(uav[idx].vel.z);
    ret.push_back(uav[idx].yaw.x); ret.push_back(uav[idx].yaw.y); ret.push_back(uav[idx].yaw.z);
    return ret;
}

/*
获得所有无人机数据
每一个pair第一个存无人机名称，第二个存无人机数据（同GetData(string name)）
*/
std::vector<std::pair<std::string, std::vector<double>>> GD::GetALLData()
{
    std::vector<std::pair<std::string, std::vector<double>>> ret;
    for (int i = 1; i <= num; ++i)
    {
        ret.push_back(std::make_pair(uav[i].name,GetData(uav[i].name)));
    }
    return ret;
}


//int main()
//{
//    GD d("192.168.1.106","6666");//初始化，连接服务器
//    d.Get();//刷新数据
//    //输出无人机名字和对应数据
//    auto AllData = d.GetALLData();
//    for(auto i:AllData)
//    {
//        qDebug()<<"无人机名称："<<QString::fromLocal8Bit(i.first.c_str());
//        qDebug()<<"位置："<<i.second[0]<<" "<<i.second[1]<<" "<<i.second[2];
//        qDebug()<<"速度："<<i.second[3]<<" "<<i.second[4]<<" "<<i.second[5];
//        qDebug()<<"偏转角："<<i.second[6]<<" "<<i.second[7]<<" "<<i.second[8];
//    }
//    return 0;
//}
