#ifndef GETVEDIO_H
#define GETVEDIO_H
#include<zmq.h>
#include<iostream>
#include<assert.h>
#include<string>
#include<QPixmap>
#include<QLabel>
#include "Include/GetData.h"

class GV
{
    void* context;
    void* sub;
    char* buf;
    std::pair<int, char*> GetVedio();
    std::string a;
public:
    GV();
    ~GV();
    GV(std::string ip, std::string port);
    void init(std::string ip, std::string port);
    void release();
    QPixmap GetImg();
};

#endif   //GETVEDIO_H
