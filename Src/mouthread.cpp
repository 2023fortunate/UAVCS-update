#include "Include/mouthread.h"
#include <windows.h>                			//GetAsyncKeyState所需头文件
#include <iostream>
#include <QFile>
#include <QPoint>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)  //用来检测按键的点击事件

MouThread::~MouThread()
{

}


void MouThread::run(){
    while(1)// 循环检测
    {
        if(KEY_DOWN(VK_LBUTTON)){ // 鼠标左键按下
            POINT temp;
            GetCursorPos(&temp);

            emit signal_Click(QPoint(temp.x,temp.y));
        }
        Sleep(100);
    }

}

void MouThread::slot_runEvent()
{

}



