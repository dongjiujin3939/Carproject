#pragma once //防止头文件重复包含
#include <iostream>
#include <graphics.h>
#include <cmath>
#include <ctime>
#include <string>
#include <vector>
using namespace std;

/********************************************全局变量************************************/
constexpr auto SWIDTH = 1200.0;//窗口宽
constexpr auto SHEIGHT = 1200.0;//窗口高
constexpr auto PI = 3.14159265358979323846;//圆周率PI
constexpr auto SHOWCIRCLE = false;//是否绘制轨迹
constexpr auto DELAYTIME = 20;//间隔时间， ms
constexpr auto CHANGETIME = 1000;//换挡时间，ms

/************************************************************************************/
class Point//点 
{
public:
	Point() = default;
	Point(const double& p_x, const double& p_y, const double& p_theta = 0.0, const double& p_R = 0.0);
	void showPoint();//绘制点
	void pointMove(const double& speed_x, const double& speed_y);//点的移动
	void pointTurn(const Point& center, const double& turn_speed);//点绕center旋转turn_speed为角速度
	double distanceTo(const Point& p) const;//点到点的距离
	double thetaTo(const Point& p) const;//this->角度到p的角度

public:
	double x;
	double y;
	double thetaP = 0.0;//角度
	double Rp = 0.0;//旋转半径
	int r = 5;//绘制半径
};


class Vec2d
{
public:
	Vec2d() = default;
	Vec2d(const double& new_x, const double& new_y, const bool& flag);//ͨ������ֵ����������flag����������һ�����캯��
	Vec2d(const Point& p_start, const Point& p_end);//ͨ�������㹹������
	Vec2d(const double& length, const double& angle);//ͨ�����Ⱥͷ���������
	double length();//ģ
	double crossProd(const Vec2d& other) const;//���
	double innerProd(const Vec2d& other) const;//���

public:
	double x;
	double y;
};

/******************************************全局函数******************************************/
void delay(const int& time); //延时函数，单位ms
double normalizeAngle(const double& theta); //角度归一化到[-PI, PI)之间
void correctAngleError(double& target_theta, const double& delta_theta);//角度误差修正
double disPointToLine(const Point& p, const Point& p_start, const Point& p_end);//点到直线的距离