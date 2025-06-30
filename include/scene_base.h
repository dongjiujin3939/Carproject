#pragma once
#include "car.h"
#include "road.h"
using namespace std;
/******************************************״̬��******************************************/
enum LaneChangeType//��������
{
	singleType,//������
	doubleType//˫����
};

class SceneBase//场景基类
{
public:
	virtual ~SceneBase() = default;//虚析构函数
	virtual void showScene();//绘制场景
	virtual void obsMoveStep() {}//障碍物移动步骤
	virtual bool planning_process() = 0;//规划过程

	/******************************************直行******************************************/
	void uniformStraight(const double& total_s);//直行，匀速运动 //total_s为目标为匀速运动的距离
	void uniformAccBySpeed(const double& target_speed_y);//直行，匀加速运动，目标速度为target_speed_y
	void uniformAccByDis(const double& dis, const double& target_speed_y);//直行，匀加速运动，目标速度为target_speed_y，行驶指定的距离时速度达到指定速度
	void uniformAccByTime(const double& target_speed, const double& target_time);//直行，匀加速运动，目标速度为target_speed，时间为target_time，在目标时间达到目标速度

	/******************************************转向******************************************/
	void carTurn(const int& turn_state, const double& R, const double& total_theta);//转向，已知半径和角度 //total_theta为当前为匀速转向的角度
	void laneChange(const Point& target_point, const int& type, const double& s = 0.0);//变道，分为单车道和双车道

	/******************************************漂移******************************************/
	void driftStraightByS(const double& total_s);//直线漂移，包含转向+直线运动，仅在目标位置
	void driftStraightByTheta(const double& total_theta);//直线漂移，包含转向+直线运动，仅在目标角度
	void driftTurnByRot(const double& total_theta, const Point& center);//漂移转向，包含转向+旋转，仅在目标旋转角度 //旋转时需要考虑旋转中心
	void driftTurnByRev(const double& total_theta, const Point& center);//Ư�ƹ��䣨��ת+��ת����ֻ���ǹ�תת�� //����תʱ������ת�͹�ת���ٶ���Ⱦ���

public:
	unique_ptr<RoadBase> road0;//道路父类指针
	unique_ptr<CarBase> car0;//主车父类指针
	double speedlimit = -6.0;//道路速度限制
};

