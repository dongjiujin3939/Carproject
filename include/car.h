#pragma once
#include "planning_base.h"
#include <memory>
using namespace std;
/******************************************状态机******************************************/
enum Shift//档位
{
	m_D,//前进档
	m_N,//空档
	m_R,//倒档
	m_P//停车档
};

enum TurnDirection//转向状态机
{
	TurnRight,//右转
	TurnLeft,//左转
};

/******************************************车辆基类******************************************/
class CarBase//车辆基类
{
public:
	virtual ~CarBase() = default;//虚析构函数
	void initCar(const double& pos_x, const double& pos_y, const double& heading, const double& width, const double& length);//初始化，车辆中心点坐标
	void updatePmidf();//更新前中点的xy值
	void updatePmidr();//更新后中点的xy值
	void updatePmid();//更新几何中点的xy值
	void showCar(const COLORREF& color);//绘制车辆矩形
	void showCircle();//绘制轨迹线
	void coutInfo();//打印信息

	void moveStraightStep();//单帧直线行驶
	void carTurnStep();//单帧转向
	void carRotationStep();//旋转

	void updateRinRout(const double& R);//更新4个半径
	void updateTurnInfo(const int& turn_state, const double& R);//更新转向信息
	void updateXYva();//更新x和y方向的速度和加速度
	void updateStraightInfo();//更新直行信息
	void updateDriftRotInfo();//更新漂移旋转信息
	void updateDriftRotRevInfo(const Point& center);//更新漂移旋转+逆时针旋转信息

public:
	double car_width = 80.0;//车宽
	double car_length = 160.0;//车长

	unique_ptr<Point> plf;//左前点
	unique_ptr<Point> plr;//左后点
	unique_ptr<Point> prf;//右前点
	unique_ptr<Point> prr; //右后点
	unique_ptr<Point> p_center;//转向中心点

	unique_ptr<Point> pmidf;//前轴中点
	unique_ptr<Point> pmidr;//后轴中点
	unique_ptr<Point> pmid;//几何中点

	double Rmin = 100.0;//最小转弯半径
	double Rof = 0.0;//外侧半径
	double Ror = 0.0;//内侧半径
	double Rif = 0.0;//内前半径
	double Rir = 0.0;//内后半径

	double R0;//半斜长，自转半径
	double theta0;//atan(car_length / car_width)

	double speed = 0.0;//车速，负前进，正倒车
	double speed_x = 0.0;//x方向速度，负左，正右
	double speed_y = 0.0;//y方向速度，负上，正下

	double a = 0.0;//加速度，负加速，正减速
	double a_x = 0.0;//x方向加速度，负左，正右
	double a_y = 0.0;//y方向加速度，负上，正下

	double delta_theta = 0.0;//角速度//负逆时针，正顺时针
	double delta_theta_rot = 0.0;//旋转角速度//负逆时针，正顺时针
	double heading_theta = 0.0;//航向角//为0时表示正前方，顺时针为正，逆时针为负

	int Gear = m_P;//档位
};

/******************************************一般车******************************************/
class CarNormal : public CarBase
{
public:
	CarNormal(const double& pos_x, const double& pos_y, const double& heading = 0.0, const double& width = 80.0, const double& length = 160.0);
};