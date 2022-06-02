#include "Include/mysm.h"

ll MS::GetEDis(pt a, pt b)//获得欧几里得距离
{
    return 1ll*(a.x-b.x)*(a.x-b.x)+1ll*(a.y-b.y)*(a.y-b.y);
}
void MS::Update(vector<P2M> &OldPoint, pt NewPoint,int DIS)
{
    bool flag = 0;
    for (int i = 0; i < OldPoint.size(); ++i)
    {
        if (GetEDis(OldPoint[i].pos, NewPoint) <= DIS*DIS)
        {
            OldPoint[i].pos.x = (OldPoint[i].pos.x*OldPoint[i].pos.f + NewPoint.x) / (OldPoint[i].pos.f + 1);
            OldPoint[i].pos.f++;
            flag = 1;
        }
    }
    if (flag == 0)
    {
        P2M x;
        x.pos = NewPoint;
        x.pos.f = 1;
        OldPoint.push_back(x);
    }

}
double MS::GK(int dis,int bw)//高斯核函数
{
    return exp(-0.5*sqrt(dis)/(bw*bw));
}
//主函数，输入为点和核带宽
vector<MeanShift> MS::solve(vector<pt> P,int DIS)
{
    bool stop = false;
    int kernel_bandwidth = DIS;
    int point_num = P.size();
    MeanShift tmp;
    vector<MeanShift>dataset;
    //把数据扔进dataset准备处理
    for(int i=0;i<point_num;++i)
    {
        tmp.pos.x = P[i].x;
        tmp.pos.y = P[i].y;
        tmp.res.x = P[i].x;
        tmp.res.y = P[i].y;
        tmp.f = P[i].f;
        tmp.t = P[i].t;
        dataset.push_back(tmp);
    }
    for(int i=0;i<point_num;++i)
    {
        stop = false;
        while(!stop)
            stop = shiftOnce(dataset,dataset[i],DIS);
    }
    LabelClusters(dataset,DIS);
    return dataset;
}

//进行一次偏移
bool MS::shiftOnce(vector<MeanShift>&dataset,MeanShift& p,int kernel_bandwidth)
{
    bool flag = 0;
    double x_sum = 0;
    double y_sum = 0;
    double weight_sum = 0;
    int point_num = dataset.size();
    for(int i = 0;i<point_num;++i)
    {
        //只统计一个区域中的点
        int dis = GetEDis(p.res,dataset[i].pos);
        if(dis> kernel_bandwidth*kernel_bandwidth)
            continue;
        //不同的点给不同的权重
        //double weight = GK(dis,kernel_bandwidth);
        double weight = 1.0;
        x_sum += dataset[i].pos.x * weight*dataset[i].f;
        y_sum += dataset[i].pos.y * weight*dataset[i].f;
        weight_sum += weight * dataset[i].f;
    }
    pt sv(int(x_sum/weight_sum),int(y_sum/weight_sum));
    double shift_distance = GetEDis(p.res,sv);
    if(shift_distance< kernel_bandwidth)
        flag = 1;
    p.res = sv;
    return flag;
}

void MS::LabelClusters(vector<MeanShift>&dataset,int DIS)
{
    int current_label = -1;
    int point_num = dataset.size();
    for(int i=0;i<point_num;++i)
    {
        if(dataset[i].label != -1)
            continue;
        current_label++;
        for(int j=0;j<point_num;++j)
            if(GetEDis(dataset[i].res,dataset[j].res)<1ll*DIS*DIS)
                dataset[j].label = current_label;
    }
}
