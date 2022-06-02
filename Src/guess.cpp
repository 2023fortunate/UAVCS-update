#include <vector>
#include <mutex>
#include <sstream>
#include "Include/mysm.h"
#include "Include/SAP.h"
#include <ctime>
#include <thread>
#include "Include/Guess.h"



Guess::Guess()
{

}

Guess::~Guess()
{

}

// 获得点击点和对应的注视点
void Guess::GetClickAndGaze(int ClickX, int ClickY, int GazeX, int GazeY,int DIS)
{
    pt a = pt(ClickX, ClickY);
    pt b = pt(GazeX, GazeY);
    Combines.push_back(P2P(a, b));
    a.f = 1;
    ClickCluster(a,DIS);

    for (auto &i : ClicksGazes)
    {
        if ((GazeX	- i.pos.x)*(GazeX - i.pos.x) + (GazeY - i.pos.y)*(GazeY - i.pos.y) <= 300*300)
        {
            b.t = time(&t);
            b.f = 1;
            i.arr.push_back(b);
            break;
        }
    }

}

void Guess::GetLayout(vector<P2P> OpePoint)
{
    for (auto i : OpePoint)
    {
        //这里的Click和Gaze分别指左上角点和右下角点
        LayoutPoint va;
        va.first = i.Click;
        va.second = i.Gaze;
        Layouts.push_back(va);
        va.second.t = time(&t);
        Gazes.push_back(va.second);
    }
}

//此处未判定鼠标实在正处于移动状态
bool Guess::MoveJudge(vector<pt> Mouses)
{
    int now = Gazes.size();
    if (Gazes[now - 1].t - Gazes[now - 10].t <= 200)
        return false;
}

void Guess::RefreshM()
{
    for (int i = 0; i < Layouts.size(); ++i)
    {
        Layouts[i].Gazes.del(time(&t), 1800);//把三十分钟没用的聚类带你删了
    }

    int mx = 0;//统计聚类点数量
    for (int i = 0; i < Layouts.size(); ++i)
    {
        vector<pt> MSInput;
        for (int j = 0; j < Layouts[i].Gazes.size(); ++j)
            MSInput.push_back(Layouts[i].Gazes[j]);
        vector<MeanShift> m = MS::solve(MSInput, 20);
        vector<MeanShift> d(1000);
        mx = 0;
        for (int i = 0; i < m.size(); ++i)
        {
            d[m[i].label].pos.x += m[i].res.x * m[i].f;
            d[m[i].label].pos.y += m[i].res.y * m[i].f;
            d[m[i].label].f += m[i].f;
            d[m[i].label].t = max(d[m[i].label].t, m[i].t);
            mx = max(mx, m[i].label);
        }
        Layouts[i].Gazes.clear();
        for (int i = 0; i <= mx; ++i)
        {
            Layouts[i].Gazes.push(pt(d[i].pos.x / d[i].f, d[i].pos.y / d[i].f , d[i].f, d[i].t));
        }
    }

}

void Guess::RefreshP2M(int DIS)
{
    for (auto i : ClicksGazes)
    {
        vector<pt> MSInput;
        for (auto j : i.arr)
            MSInput.push_back(j);
        vector<MeanShift> m = MS::solve(MSInput, DIS);
        vector<MeanShift> d(1000);
        int mx = 0;
        for (int j = 0; j < m.size(); ++j)
        {
            d[m[j].label].pos.x += m[j].res.x * m[j].f;
            d[m[j].label].pos.y += m[j].res.y * m[j].f;
            d[m[j].label].f += m[j].f;
            d[m[j].label].t = max(d[m[j].label].t, m[j].t);
            mx = max(mx, m[j].label);
        }
        i.arr.clear();
        for (int j = 0; j <= mx; ++j)
        {
            i.arr.push_back(pt(d[j].pos.x / d[j].f, d[j].pos.y / d[j].f, d[j].f, d[j].t));
        }
    }
}

void Guess::check()
{
    for (auto i : ClicksGazes)
    {
        cout << i.pos.x << " " << i.pos.y << endl;
        for (auto j : i.arr)
            cout <<" "<< j.x << " " << j.y << endl;
    }
}

pair<int, int> Guess::RetUserPos(int x, int y)
{
    pair<int, int> RetP(-1,-1);
    int f = 0;
    for (auto i : ClicksGazes)
    {
        for (auto j : i.arr)
        {
            if (GetDis(j, pt(x, y)) < 300*300)
                return pair<int, int>(i.pos.x, i.pos.y);
        }
    }
    return RetP;
}

int Guess::GetDis(pt a, pt b)
{
    return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

bool Guess::between(pt a, pt b, pt c)
{
    if (a.x <= c.x && a.y <= c.y)
        if (c.x <= b.x && c.y <= b.y)
            return true;
    return false;
}

void Guess::init()
{
    Gazes.clear();
    Clicks.clear();
    Layouts.clear();
    Combines.clear();
}

void Guess::ClickCluster(pt NewPoint,int DIS)
{
    MS::Update(ClicksGazes,NewPoint,DIS);
}
