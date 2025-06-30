#include "scene_drift.h"
using namespace std;
/******************************************U����Ư�ơ�����Ư��******************************************/
DriftPoint::DriftPoint()//U����Ư�ơ�����Ư��
{
	road0 = make_unique<RoadNormal>(400.0);
	cone = make_unique<Cone>(SWIDTH / 2.0, SHEIGHT / 2.0 + 220.0, 40.0);//����׶Ͱ

	//���㶨λ������
	double pos_x = SWIDTH / 2.0 - road0->Rwidth / 2.0;
	double pos_y = 100.0;
	cout << "LocX = " << pos_x << ", LocY = " << pos_y << endl;

	car0 = make_unique<CarNormal>(pos_x, pos_y, PI);
	car0->speed = -5.0;

	car0->coutInfo();
	showScene();
	system("pause");
}

void DriftPoint::showScene()//��ʾ
{
	BeginBatchDraw();
	cleardevice();

	road0->showRoad();
	cone->showCone();
	car0->showCar(BLACK);

	EndBatchDraw();
	delay(DELAYTIME);
}

bool DriftPoint::planning_process()//��������
{
	cout << "ֱ������" << endl;
	double drift_start = SHEIGHT / 2.0 - 160.0;//��Ư��
	uniformStraight(drift_start - car0->pmidr->y);

	cout << "��Ư" << endl;
	car0->delta_theta_rot = PI / 200.0;
	driftStraightByS(cone->p_center->y - car0->pmid->y);

	cout << "����" << endl;
	double R = car0->pmid->distanceTo(*cone->p_center);
	car0->delta_theta = -car0->speed / R;//���ٶȣ�ע��������
	car0->delta_theta_rot = car0->delta_theta;//����ת������ת���ٶȺ͹�ת���
	double target_theta = PI * 2.0 - car0->heading_theta;
	driftTurnByRev(target_theta + lap * 2.0 * PI, *cone->p_center);

	cout << "����" << endl;
	car0->delta_theta = -car0->speed / R;//���ٶȣ�ע��������
	car0->delta_theta_rot = 0.0;
	driftTurnByRev(PI - target_theta, *cone->p_center);

	cout << "ֱ�г���" << endl;
	car0->updatePmidr();
	uniformStraight(car0->pmidr->y - 0.0);
	return true;
}

/******************************************Ư�Ʋ���******************************************/
DriftParking::DriftParking()//Ư�Ʋ���
{
	road0 = make_unique<RoadNormal>(180.0);
	ob1 = make_unique<CarObsStatic>(road0->right_boundary - 50.0, SHEIGHT / 2.0);
	ob2 = make_unique<CarObsStatic>(road0->right_boundary - 50.0, SHEIGHT / 2.0 + 410.0);
	park_length = ob2->topPos - ob1->bottomPos;
	cout << "park_length = " << park_length << endl;

	car0 = make_unique<CarNormal>(SWIDTH / 2.0 - road0->Rwidth / 3.0, 100.0, PI);
	car0->speed = -5.0;

	car0->coutInfo();
	ob1->coutInfo();
	ob2->coutInfo();

	showScene();
	system("pause");
}

void DriftParking::showScene()
{
	BeginBatchDraw();
	cleardevice();

	road0->showRoad();
	ob1->showCar(RED);
	ob2->showCar(RED);
	car0->showCar(BLACK);

	EndBatchDraw();
	delay(DELAYTIME);
}

bool DriftParking::planning_process()//��������
{
	//�жϿ�ĳ����Ƿ��㹻
	if (park_length <= car0->car_length * 1.2)
	{
		cout << "����̫�̣�����ʧ��" << endl;
		return false;
	}

	//Ŀ��ͣ����
	double park_x = ob1->pmid->x;
	double park_y = ob1->bottomPos + park_length / 2.0;

	//��ת����
	double Rturn = park_x - car0->pmid->x;
	Point p_center(park_x, park_y - Rturn);

	cout << "ֱ������" << endl;
	uniformStraight(p_center.y - car0->pmid->y + 5.0);

	cout << "���" << endl;
	car0->delta_theta = PI / 80.0;
	car0->delta_theta_rot = car0->delta_theta * 2.0;
	driftTurnByRev(PI / 2.0, p_center);
	return true;
}