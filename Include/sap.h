#ifndef SAP_H
#define SAP_H

#include<cstdio>
#include<iostream>
#include<vector>
#include"Include/mysm.h"

using namespace std;

struct MyQueue    //自定义一个堆
{
    pt *arr;
    int s, e;
    int num;
    MyQueue()
    {
        int x = 1000;
        num = x;
        arr = new pt[x];
        s = 0; e = -1;
    }
    MyQueue(int x)
    {
        if (x <= 0)
            x = 1;
        num = x;
        arr = new pt[x];
        s = 0; e = -1;
    }
    void init(int x)
    {
        if (x <= 0)
            x = 1;
        num = x;
        arr = new pt[x];
        s = 0; e = -1;
    }
    bool push(pt x)
    {
        if ((e + 1) % num == s && e != -1)
            return 0;
        e = (e + 1) % num;
        arr[e] = x;
        return 1;
    }
    bool full()
    {
        if (e != -1 && (e + 1) % num == s)
            return 1;
        return 0;
    }
    bool pop()
    {
        if (e == -1)
            return 0;
        if (s == e)
            s = 0, e = -1;
        else
            s = (s + 1) % num;
        return 1;
    }
    pt top()
    {
        return arr[s];
    }
    pt& operator[](int n)
    {
        return arr[(s + n) % num];
    }
    void push(int x, int y, int tm)
    {
        pt d;
        d.x = x;
        d.y = y;
        d.f = tm;
        push(d);
    }
    int size()
    {
        return e - s + 1;
    }
    int del(int now, int t)
    {
        int cnt = 0;
        while (size())
        {
            pt x = top();
            if (now - x.f > t)
                pop();
            else
                break;
            cnt++;
        }
        return cnt;
    }
    void clear()
    {
        s = 0; e = -1;
    }
};



#endif // SAP_H

