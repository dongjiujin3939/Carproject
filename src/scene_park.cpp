#include "scene_park.h"
using namespace std;
/******************************************������ʽ1******************************************/
ReverseParking1::ReverseParking1()//������ʽ1
{
	road0 = make_unique<RoadNormal>(250.0);
	ob1 = make_unique<CarObsStatic>(road0->right_boundary - 90.0, SHEIGHT / 2.0, PI / 2.0);
	ob2 = make_unique<CarObsStatic>(road0->right_boundary - 90.0, SHEIGHT / 2.0 + 200.0, PI / 2.0);
	park_width = ob2->topPos - ob1->bottomPos;
	dis_in = ob1->car_length * 0.8;
	cout << "park_width = " << park_width << ", dis_in = " << dis_in << endl;

	car0 = make_unique<CarNormal>(ob1->leftPos - dis_obs_L, SHEIGHT - 80.0);
	car0->speed = -3.0;
	car0->Gear = Shift::m_D;//��ǰ����

	car0->coutInfo();
	ob1->coutInfo();
	ob2->coutInfo();

	showScene();
	system("pause");
}

void ReverseParking1::showScene()//��ʾ
{
	BeginBatchDraw();
	cleardevice();

	road0->showRoad();
	ob1->showCar(RED);
	ob2->showCar(RED);
	car0->showCar(BLACK);

	if (SHOWCIRCLE && car0->p_center)//���ƹ켣��
	{
		car0->showCircle();
	}

	EndBatchDraw();
	delay(DELAYTIME);
}

bool ReverseParking1::planning_process()//������������
{
	//�жϿ�Ŀ����Ƿ��㹻
	if (park_width <= car0->car_width * 1.2)
	{
		cout << "����̫խ������ʧ��" << endl;
		return false;
	}

	//����R��stopline
	double R = ob1->car_length + dis_obs_L - dis_in;//ת��뾶
	double dis_obs_S = R - park_width / 2.0;//���ϰ����·����������
	double stopline = ob1->bottomPos - dis_obs_S;//ֱ�н���λ��
	cout << "R = " << R << ", dis_obs_S = " << dis_obs_S << ", stopline = " << stopline << endl;

	cout << "ֱ��ǰ��" << endl;
	uniformStraight(car0->pmidr->y - stopline);
	car0->Gear = Shift::m_R;
	delay(CHANGETIME);

	cout << "������ת" << endl;
	car0->speed = 2.0;//���ٶȣ�����Ϊ��
	car0->delta_theta = car0->speed / R;//���ٶ�=���ٶ�/�뾶��ע��������;
	carTurn(TurnDirection::TurnRight, R, PI / 2.0);

	cout << "����ֱ��" << endl;
	car0->speed = 2.0;
	uniformStraight(road0->right_boundary - safedis - car0->pmidr->x);
	car0->Gear = Shift::m_P;

	cout << "�������" << endl;
	return true;
}

/******************************************������ʽ2******************************************/
ReverseParking2::ReverseParking2()//������ʽ2
{
	road0 = make_unique<RoadNormal>(250.0);
	ob1 = make_unique<CarObsStatic>(road0->right_boundary - 90.0, SHEIGHT / 2.0, PI / 2.0);
	ob2 = make_unique<CarObsStatic>(road0->right_boundary - 90.0, SHEIGHT / 2.0 + 200.0, PI / 2.0);
	park_width = ob2->topPos - ob1->bottomPos;
	dis_in = ob1->car_length * 0.8;
	cout << "park_width = " << park_width << ", dis_in = " << dis_in << endl;

	car0 = make_unique<CarNormal>(ob1->leftPos - dis_obs_L, SHEIGHT - 80.0);
	car0->speed = -2.0;
	car0->Gear = Shift::m_D;//��ǰ����

	car0->coutInfo();
	ob1->coutInfo();
	ob2->coutInfo();

	showScene();
	system("pause");
}

void ReverseParking2::showScene()//��ʾ
{
	BeginBatchDraw();
	cleardevice();

	road0->showRoad();
	ob1->showCar(RED);
	ob2->showCar(RED);
	car0->showCar(BLACK);

	if (SHOWCIRCLE && car0->p_center)//���ƹ켣��
	{
		car0->showCircle();
	}

	EndBatchDraw();
	delay(DELAYTIME);
}

bool ReverseParking2::planning_process()//������������
{
	//�жϿ�Ŀ����Ƿ��㹻
	if (park_width <= car0->car_width * 1.2)
	{
		cout << "����̫խ������ʧ��" << endl;
		return false;
	}

	//���㵹���뾶����תĿ��ת�ǣ�stopline
	double stopline = ob2->topPos;//ֱ�н���λ��
	double Rl = 200.0;//��ʼ����תת��뾶
	double center_x = car0->pmidr->x - Rl;
	double M = park_width / 2.0;
	double N = road0->right_boundary - dis_in - center_x;
	double Rr = (pow(Rl, 2) - pow(M, 2) - pow(N, 2)) / (M * 2 - Rl * 2);//��ת�����뾶	
	double target_theta = atan((Rr + M) / N);//��תĿ��ת��
	cout << "M = " << M << ", N = " << N << ", Rl = " << Rl << ", Rr = " << Rr << ", target_theta = " << target_theta / PI << ", stopline = " << stopline << endl;

	cout << "ֱ��ǰ��" << endl;
	uniformStraight(car0->pmidr->y - stopline);

	cout << "��תǰ��" << endl;
	car0->delta_theta = -car0->speed / Rl;//���ٶ�=���ٶ�/�뾶��ע��������;
	carTurn(TurnDirection::TurnLeft, Rl, target_theta);
	car0->Gear = Shift::m_R;
	delay(CHANGETIME);

	cout << "������ת" << endl;
	car0->delta_theta = -car0->speed / Rr;//���ٶ�=���ٶ�/�뾶��ע��������;
	carTurn(TurnDirection::TurnRight, Rr, PI / 2.0 - target_theta);

	cout << "����ֱ��" << endl;
	car0->speed = 2.0;
	uniformStraight(road0->right_boundary - safedis - car0->pmidr->x);
	car0->Gear = Shift::m_P;

	cout << "�������" << endl;
	return true;
}

/******************************************�෽λ����******************************************/
ParallelParking::ParallelParking()//�෽λ����
{
	road0 = make_unique<RoadNormal>(180.0);
	ob1 = make_unique<CarObsStatic>(road0->right_boundary - 50.0, SHEIGHT / 2.0);
	ob2 = make_unique<CarObsStatic>(road0->right_boundary - 50.0, SHEIGHT / 2.0 + 410.0);
	park_length = ob2->topPos - ob1->bottomPos;
	cout << "park_length = " << park_length << endl;

	car0 = make_unique<CarNormal>(ob1->leftPos - dis_obs_L, SHEIGHT - 80.0);
	car0->speed = -3.0;
	car0->Gear = Shift::m_D;//��ǰ����

	car0->coutInfo();
	ob1->coutInfo();
	ob2->coutInfo();

	showScene();
	system("pause");
}

void ParallelParking::showScene()//��ʾ
{
	BeginBatchDraw();
	cleardevice();

	road0->showRoad();
	ob1->showCar(RED);
	ob2->showCar(RED);
	car0->showCar(BLACK);

	if (SHOWCIRCLE && car0->p_center)//���ƹ켣��
	{
		car0->showCircle();
	}

	EndBatchDraw();
	delay(DELAYTIME);
}

bool ParallelParking::planning_process()//������������
{
	//�жϿ�ĳ����Ƿ��㹻
	if (park_length <= car0->car_length * 1.2)
	{
		cout << "����̫�̣�����ʧ��" << endl;
		return false;
	}

	//����R��Ŀ��ת�Ǻ�stopline
	double stopline = ob1->bottomPos;//ֱ�н���λ��
	double L = (dis_obs_L + ob1->car_width / 2.0) / 2.0;
	double h = (park_length - safedis) / 2.0;
	double R = (pow(L, 2) + pow(h, 2)) / L / 2.0;//ת��뾶
	double target_theta = asin(h / R);//Ŀ��ת��
	cout << "R = " << R << ", target_theta = " << target_theta / PI << ", stopline = " << stopline << endl;

	cout << "ֱ��ǰ��" << endl;
	uniformStraight(car0->pmidr->y - stopline);
	car0->Gear = Shift::m_R;
	delay(CHANGETIME);

	cout << "������ת" << endl;
	car0->speed = 2.0;//���ٶȣ�����Ϊ��
	car0->delta_theta = car0->speed / R;//���ٶ�=���ٶ�/�뾶��ע��������;
	carTurn(TurnDirection::TurnRight, R, target_theta);

	cout << "������ת" << endl;
	car0->delta_theta = -car0->speed / R;//�л�����
	carTurn(TurnDirection::TurnLeft, R, target_theta);
	car0->Gear = Shift::m_D;
	delay(CHANGETIME);

	cout << "ֱ��ǰ��" << endl;
	car0->speed = -2.0;
	uniformStraight(30.0);
	car0->Gear = Shift::m_P;

	cout << "�������" << endl;
	return true;
}