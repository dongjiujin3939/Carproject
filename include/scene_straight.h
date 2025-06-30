#pragma once
#include "scene_base.h"
using namespace std;
class StraightStopObs : public SceneBase //ͣ停障
{
public:
	StraightStopObs();
	void showScene();//显示
	bool planning_process() override;

public:
	unique_ptr<Cone> cone;//锥桶
	double safedis = 50.0;//停止安全距离
};

class StraightStation : public SceneBase //停车站
{
public:
	StraightStation();
	void showScene();//显示
	bool planning_process() override;

public:
	unique_ptr<Point> station;//站点
	int stop_time = 3;//停车时间
};

class StraightFollow : public SceneBase //跟车
{
public:
	StraightFollow();
	void showScene();//显示
	bool planning_process() override;

public:
	unique_ptr<CarNormal> carObs;//跟车目标
	double safedis = 120.0;//安全距离
};

class StraightCrosswalk : public SceneBase //通过斑马线
{
public:
	StraightCrosswalk();
	bool peopleInCross();//斑马线是否有人
	void showScene();//显示
	bool planning_process() override;

public:
	int people_num = 5;//人数
	vector<unique_ptr<Person>> people;//行人
	double speedlimit_cross = -3.0;//限速
};