#ifndef GETDATA_H
#define GETDATA_H
#include<zmq.h>
#include<iostream>
#include<string>
#include<assert.h>
//#include<QJsonArray>
#include<QDebug>
#include<Include/dist/json/json.h>

class GD
{
private:
    struct TP
    {
        double x, y, z;
    };
    struct UAV
    {
           std::string name;
           std::string port;
           TP pos, vel, yaw;
    };
    UAV uav[100];
    void* context_data;
    void* all_data;
    void* context_REP;
    void* sub;
    void* sub_REP;
    void* sub_ALL;
    char buf[200000];
    int num;
    std::string tar_ip;
    std::map<std::string, std::string>mp;
    std::map<std::string, int>mp1;
public:

    void Get();
    std::string AGet();
    void initA(std::string ipdz);
    GD();
    ~GD();
    GD(std::string ip, std::string port);
    int GetNum();
    std::vector<std::string> GetALLName();
    std::string GetPort(std::string name);
    std::vector<std::pair<std::string,std::string>> GetALLPort();
    std::vector<double> GetData(std::string name);
    std::vector<std::pair<std::string,std::vector<double>>> GetALLData();

};
#endif   //GETDATA_H
