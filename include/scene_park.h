#pragma once
#include "scene_base.h"
#include <memory>
using namespace std;
class ReverseParking1 : public SceneBase //������ʽ1
{
public:
	ReverseParking1();//����
	void showScene();//��ʾ
	bool planning_process() override;//������������

public:
	unique_ptr<CarObsStatic> ob1;
	unique_ptr<CarObsStatic> ob2;
	double dis_in = 0.0;//����ֱ�еľ���
	double park_width = 0.0;//��Ŀ���	
	double dis_obs_L = 120.0;//���ϰ����󷽵ĺ������
	double safedis = 10.0;//���·�ұ߽�İ�ȫ����
};

class ReverseParking2 : public SceneBase //������ʽ2
{
public:
	ReverseParking2();//����
	void showScene();//��ʾ
	bool planning_process() override;//������������

public:
	unique_ptr<CarObsStatic> ob1;
	unique_ptr<CarObsStatic> ob2;
	double dis_in = 0.0;//����ֱ�еľ���
	double park_width = 0.0;//��Ŀ���
	double dis_obs_L = 80.0;//���ϰ����󷽵ĺ������
	double safedis = 10.0;//���·�ұ߽�İ�ȫ����
};

class ParallelParking : public SceneBase //�෽λ����
{
public:
	ParallelParking();//����
	void showScene();//��ʾ
	bool planning_process() override;//������������

public:
	unique_ptr<CarObsStatic> ob1;
	unique_ptr<CarObsStatic> ob2;
	double safedis = 10.0;//��󷽰�ȫ����
	double park_length = 0.0;//��ĳ���
	double dis_obs_L = 80.0;//���ϰ����󷽵ĺ������
};
