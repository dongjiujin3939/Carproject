#include "planning_base.h"
using namespace std;
/******************************************点******************************************/
Point::Point(const double& p_x, const double& p_y, const double& p_theta, const double& p_R) : x(p_x), y(p_y), thetaP(p_theta), Rp(p_R)//构造点函数
{

}

void Point::showPoint()//绘制点
{
	setfillcolor(BLACK);//绘制线颜色
	solidcircle(x, y, r);//x,y坐标,r半径
}

void Point::pointMove(const double& speed_x, const double& speed_y)//点的移动
{
	x += speed_x;
	y += speed_y;
}

void Point::pointTurn(const Point& center, const double& turn_speed)//点绕center旋转turn_speed为角速度
{
	thetaP += turn_speed;//turn_speed>0，为绕着center逆时针旋转，turn_speed<0，为顺时针旋转
	x = Rp * cos(thetaP) + center.x;
	y = -Rp * sin(thetaP) + center.y;//考虑EasyX坐标系
}

double Point::distanceTo(const Point& p) const//点到点的距离
{
	return hypot(x - p.x, y - p.y);
}

double Point::thetaTo(const Point& p) const//this->�����p�ĽǶ�
{
	if (x >= p.x && y == p.y)//x�������ϣ�������p�غ�
	{
		return 0.0;
	}
	else if (x < p.x && y == p.y)//x������
	{
		return PI;
	}
	else if (x == p.x && y > p.y)//y������
	{
		return -PI / 2.0;
	}
	else if (x == p.x && y < p.y)//y������
	{
		return PI / 2.0;
	}
	else if (x > p.x)//��һ��������
	{
		return -atan((y - p.y) / (x - p.x));//���ǵ�eaxyX����ϵ��ȡ����
	}
	else if (x < p.x)//�ڶ���������
	{
		return PI - atan((y - p.y) / (x - p.x));
	}

	return 0.0;
}

/******************************************����******************************************/
Vec2d::Vec2d(const double& new_x, const double& new_y, const bool& flag) : x(new_x), y(new_y)//ͨ������ֵ����������flag����������һ�����캯��
{

}

Vec2d::Vec2d(const Point& p_start, const Point& p_end)//ͨ�������㹹������
{
	x = p_end.x - p_start.x;
	y = -(p_end.y - p_start.y);//������ֵ�л�Ϊy�����ϵ�ֱ������
}

Vec2d::Vec2d(const double& length, const double& angle)//ͨ�����Ⱥͷ���������
{
	x = length * cos(angle);
	y = length * sin(angle);//������ֵ�л�Ϊy�����ϵ�ֱ������
}

double Vec2d::length()//ģ
{
	return hypot(x, y);
}

double Vec2d::crossProd(const Vec2d& other) const //���
{
	return x * other.y - y * other.x;
}

double Vec2d::innerProd(const Vec2d& other) const //���
{
	return x * other.x + y * other.y;
}

/******************************************全局函数******************************************/
void delay(const int& time) //延时函数，单位ms
{
	clock_t  now = clock(); //获取当前时间
	while (clock() - now < time)
	{

	}
}

double normalizeAngle(const double& theta)//�Ƕ�������[-PI, PI)֮��
{
	double theta_new = fmod(theta + PI, 2.0 * PI);//�ѽǶȶ�2PI��ģ
	if (theta_new < 0.0)
	{
		theta_new += (2.0 * PI);//���С��0�����2PI
	}
	return theta_new - PI;//Ȼ���ȥPI
}

void correctAngleError(double& target_theta, const double& delta_theta)//�Ƕ��������
{
	if (delta_theta > 0.0)
	{
		if (target_theta > 0)//��ʱ��
		{
			target_theta -= delta_theta;
		}
		else if (target_theta < 0)//˳ʱ��
		{
			target_theta += delta_theta;
		}
	}
}

double disPointToLine(const Point& p, const Point& p_start, const Point& p_end)//�㵽ֱ�ߵľ���
{
	Vec2d line(p_start, p_end);
	Vec2d line_p(p_start, p);
	if (line.length() == 0.0)
	{
		return line_p.length();
	}
	return fabs(line.crossProd(line_p)) / line.length();
}