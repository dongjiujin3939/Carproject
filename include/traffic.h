#pragma once
#include "planning_base.h"
#include "car.h"
using namespace std;
/******************************************障碍物******************************************/
class Cone//锥体
{
public:
	Cone() = default;
	Cone(const double& pos_x, const double& pos_y, const double& R = 20.0);
	void showCone();//显示

public:
	unique_ptr<Point> p_center;//中心
	double r = 20.0;//半径
};

class Person//行人
{
public:
	Person() = default;
	Person(const double& pos_x, const double& pos_y);
	void personMove();//行人移动
	void showPerson();//绘制

public:
	unique_ptr<Point> p_center;//中心点
	double r = 20.0;//半径
	double speed = 0.0;//速度
};

class CarObsStatic : public CarBase//��̬�ϰ���
{
public:
	CarObsStatic() = default;
	CarObsStatic(const double& pos_x, const double& pos_y, const double& heading = 0.0, const double& width = 80.0, const double& length = 160.0);//��̬�ϰ���

public:
	//4����λ��
	double topPos = 0.0;
	double rightPos = 0.0;
	double leftPos = 0.0;
	double bottomPos = 0.0;
};