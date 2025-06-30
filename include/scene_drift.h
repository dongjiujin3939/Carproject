#pragma once
#include "scene_base.h"
using namespace std;
class DriftPoint : public SceneBase//����Ư��
{
public:
	DriftPoint();
	void showScene();//��ʾ
	bool planning_process() override;//��������

public:
	unique_ptr<Cone> cone;//׶Ͱ
	int lap = 0;//��׮Ȧ��
};

class DriftParking : public SceneBase//Ư�Ʋ���
{
public:
	DriftParking();
	void showScene();//��ʾ
	bool planning_process() override;//��������

public:
	unique_ptr<CarObsStatic> ob1;
	unique_ptr<CarObsStatic> ob2;
	double park_length = 0.0;//��ĳ���
};