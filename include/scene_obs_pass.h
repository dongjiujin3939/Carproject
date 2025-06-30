#pragma once
#include "scene_base.h"
#include <memory>
using namespace std;
class StaticObs : public SceneBase//��̬����
{
public:
	StaticObs();
	void showScene();//��ʾ
	bool planning_process() override;//��������

public:
	unique_ptr<Cone> cone;//׶Ͱ
	double start_dis = 200.0;//��ʼ���ϵľ���
};

class OvertakeObs : public SceneBase//����
{
public:
	OvertakeObs();
	void obsMoveStep();
	void showScene();//��ʾ
	bool planning_process() override;//��������

public:
	unique_ptr<CarNormal> carObs;//ǰ�ϰ���
	double start_dis = 0.0;//��ʼ���ϵľ���
};

class MeetingObs : public SceneBase//�ᳵ
{
public:
	MeetingObs();
	void obsMoveStep();
	void showScene();//��ʾ
	bool planning_process() override;//��������

public:
	unique_ptr<CarNormal> carObs;//�ϰ���
	double start_dis = 200.0;//��ʼ���ϵľ���
};