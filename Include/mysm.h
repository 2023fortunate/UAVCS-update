#ifndef MYSM_H
#define MYSM_H

#include<iostream>
#include<vector>
#include<windows.h>
#include<cmath>

#define ll long long
#define EPSILON 100
using namespace std;

struct pt
{
    int x;
    int y;
    int f;
    int t;
    pt(){
        x = 0;
        y = 0;
        f = 1;
        t = 1;
    }
    pt(int x, int y,int _t=1) :x(x), y(y) { f = _t; }
    pt(int x, int y, int _f, int _t) :x(x), y(y) { f = _f; t = _t; }
};

struct P2P
{
    pt Click;
    pt Gaze;
    P2P(){}
    P2P(pt a,pt b):Click(a),Gaze(b){}
};

struct P2M
{
    pt pos;
    vector<pt> arr;
};

struct MeanShift
{
    pt pos;
    pt res;
    int label = -1;
    int f = 1;
    int t = 0;
};

class MS
{
public:
    static vector<MeanShift> solve(vector<pt> P,int DIS);
    static void Update(vector<P2M> &OldPoint, pt NewPoint,int DIS);
private:
    static double GK(int dis,int bw);
    static bool shiftOnce(vector<MeanShift>&dataset,MeanShift &p,int kernel_bandwidth);
    static void LabelClusters(vector<MeanShift>&dataset,int DIS);
    static ll GetEDis(pt a,pt b);

};


#endif // MYSM_H
