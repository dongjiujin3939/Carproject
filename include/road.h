#pragma once
#include "traffic.h"
using namespace std;
/******************************************道路基类******************************************/
class RoadBase//道路基类
{
public:
	virtual ~RoadBase() = default;//虚析构函数
	virtual void showRoad() = 0;//绘制道路

	//获取道路的上下边界
	virtual double getUpLine() { return 0.0; }
	virtual double getMidLine() { return 0.0; }
	virtual double getDownLine() { return 0.0; }

public:
	double Rwidth = 200.0;//道路宽度
	double up_boundary = 0.0;//上边界
	double down_boundary = 0.0;//下边界
	double left_boundary = 0.0;//左边界
	double right_boundary = 0.0;//右边界
};

class RoadNormal : public RoadBase//一般道路
{
public:
	RoadNormal(const double& r_width = 200.0);
	void showRoad() override;//绘制道路
};

class RoadDoubleLane : public RoadBase//双车道
{
public:
	RoadDoubleLane(const double& r_width = 200.0);
	void showRoad() override;//绘制道路
};

class RoadCrosswalk : public RoadBase//斑马线道路
{
public:
	RoadCrosswalk(const double& r_width = 200.0);
	void showRoad() override;//绘制道路
	double getUpLine() { return this->up_line; }//获取上边界
	double getMidLine() { return this->mid_line; }//获取中间线
	double getDownLine() { return this->down_line; }//获取下边界

public:
	double up_line = 0.0;//斑马线上边界
	double mid_line = 0.0;//斑马线中心线
	double down_line = 0.0;//斑马线下边界
	double disRec = 20.0;//距离
};