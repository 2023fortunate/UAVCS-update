#ifndef GUESS_H
#define GUESS_H

#include <vector>
#include <mutex>
#include <sstream>
#include "Include/mysm.h"
#include "Include/sap.h"
#include <ctime>
#include <thread>

struct LayoutPoint
{
    pt first, second;
    MyQueue Gazes;
};

class Guess
{
public:
    Guess();
    ~Guess();
    void init();
    void GetClickAndGaze(int ClickX, int ClickY, int GazeX, int GazeY, int DIS);
    void GetLayout(vector<P2P> OpePoint);
    bool MoveJudge(vector<pt> Mouses);
    void RefreshM();
    void RefreshP2M(int DIS);
    void check();
    pair<int, int> RetUserPos(int x, int y);
private:
    vector<pt> Gazes, Clicks; //保存所有凝视点和点击点
    vector<LayoutPoint> Layouts;//可操作点
    vector<P2P> Combines;//所有未处理的点击点和凝视点
    vector<P2M> ClicksGazes;
    int GetDis(pt a, pt b);//获得两个点的欧几里得距离
    time_t t;
    void ClickCluster(pt NewPoint,int DIS);
    bool between(pt a, pt b, pt c);

};




#endif // GUESS_H
