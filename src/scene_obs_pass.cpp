#include "scene_obs_pass.h"
using namespace std;
/******************************************��̬����******************************************/
StaticObs::StaticObs()//��̬����
{
	road0 = make_unique<RoadNormal>(250.0);
	cone = make_unique<Cone>(SHEIGHT / 2.0, SWIDTH / 2.0, 50.0);

	car0 = make_unique<CarNormal>(SWIDTH / 2.0, SHEIGHT - 70.0);
	car0->speed = -4.0;

	car0->coutInfo();
	showScene();
	system("pause");
}

void StaticObs::showScene()//��ʾ
{
	BeginBatchDraw();
	cleardevice();

	road0->showRoad();
	cone->showCone();
	car0->showCar(BLACK);

	if (SHOWCIRCLE && car0->p_center)//���ƹ켣��
	{
		car0->showCircle();
	}

	EndBatchDraw();
	delay(DELAYTIME);
}

bool StaticObs::planning_process()
{
	double start_line = cone->p_center->y + cone->r + start_dis + car0->car_length;//��ʼ���ϵ�λ��
	uniformStraight(car0->pmidr->y - start_line);

	//����Ŀ���
	double dis_l_L = cone->p_center->x - cone->r - road0->left_boundary;//����
	double dis_r_L = road0->right_boundary - cone->p_center->x - cone->r;//�Ҽ��
	double target_l_x = road0->left_boundary + dis_l_L / 2.0;//��Ŀ���x
	double target_r_x = road0->right_boundary - dis_r_L / 2.0;//��Ŀ���x
	double target_y = cone->p_center->y;//������Ҽ���е��y
	Point target_l_point(target_l_x, target_y);//��Ŀ���
	Point target_r_point(target_r_x, target_y);//��Ŀ���
	cout << "dis_l_L = " << dis_l_L << ", dis_r_L = " << dis_r_L << ", target_l_x= " << target_l_x << ", target_r_x= " << target_r_x << ", target_y= " << target_y << endl;

	if (dis_l_L > car0->car_width * 1.2)//�����߹��������ȴ�����
	{
		laneChange(target_l_point, LaneChangeType::doubleType);
	}
	else//��߲�����
	{
		if (dis_r_L > car0->car_width * 1.2)//����ұ߹�����������
		{
			laneChange(target_r_point, LaneChangeType::doubleType);
		}
		else//�ұ�Ҳ������
		{
			cout << "���ҿ��Ȳ���ͨ�У�����ͣ��" << endl;
			double stopline = cone->p_center->y + cone->r + 50.0;
			uniformAccByDis(car0->pmidf->y - stopline, 0.0);
			return false;
		}
	}

	car0->updatePmidr();
	uniformStraight(car0->pmidr->y - 0.0);
	return true;
}

/******************************************����******************************************/
OvertakeObs::OvertakeObs()//����
{
	double Rwidth = 100.0;
	road0 = make_unique<RoadDoubleLane>(Rwidth);
	carObs = make_unique<CarNormal>(SWIDTH / 2.0 + Rwidth / 2.0, SHEIGHT - 400.0, 0.0, 50.0, 100.0);
	car0 = make_unique<CarNormal>(SWIDTH / 2.0 + Rwidth / 2.0, SHEIGHT - 70.0, 0.0, 40.0, 80.0);

	carObs->speed = -2.0;
	car0->speed = -6.0;

	carObs->updateStraightInfo();//��carObs׼��ֱ��

	car0->coutInfo();
	carObs->coutInfo();

	showScene();
	system("pause");
}

void OvertakeObs::obsMoveStep()
{
	carObs->moveStraightStep();
}

void OvertakeObs::showScene()//��ʾ
{
	BeginBatchDraw();
	cleardevice();

	road0->showRoad();
	carObs->showCar(RED);
	car0->showCar(BLACK);

	if (SHOWCIRCLE && car0->p_center)//���ƹ켣��
	{
		car0->showCircle();
	}

	EndBatchDraw();
	delay(DELAYTIME);
}

bool OvertakeObs::planning_process()
{
	double delta_speed = fabs(car0->speed) - fabs(carObs->speed);//�ٶȲ�ڱ������б��ֲ���
	cout << "delta_speed = " << delta_speed << endl;
	if (delta_speed <= 0.0)//�����������޷�ʵ�ֳ���
	{
		cout << "�����������޷�ʵ�ֳ���" << endl;
		return false;
	}

	double dis_l_L = carObs->plr->x - road0->left_boundary;//����
	double target_l_x = road0->left_boundary + dis_l_L / 2.0;//��Ŀ���x
	cout << "dis_l_L = " << dis_l_L << ", target_l_x = " << target_l_x << endl;
	if (dis_l_L <= car0->car_width * 1.2)
	{
		cout << "�����Ȳ�������" << endl;
		return false;
	}

	start_dis = car0->car_length * 3.5;
	double dis0 = car0->pmidr->y - carObs->pmidr->y;//��ʼ����
	cout << "start_dis = " << start_dis << ", dis0 = " << dis0 << endl;
	if (dis0 < start_dis)
	{
		cout << "����ǰ��̫����������벻��" << endl;
		return false;
	}

	uniformStraight(dis0 - start_dis);//ֱ�е�������
	double time_lane_change = dis0 / delta_speed;//��ʻ������λ�û���ʱ�䣨ѭ��������,���ʱ��
	double dis_target = carObs->car_length;//Ŀ����룬����1����������
	double target_y = car0->pmidr->y + car0->speed * time_lane_change;//��ʻ�����ŵ�λ�ã���Ŀ���y
	double time_straight = dis_target / delta_speed;//ֱ��ʱ��
	double s = fabs(car0->speed) * time_straight;//ֱ�еľ���
	cout << "dis_target = " << dis_target << ", target_y = " << target_y << ", s = " << s << endl;

	Point target_l_point(target_l_x, target_y);//��Ŀ���
	laneChange(target_l_point, LaneChangeType::doubleType, s);//��ʻ������λ�ú�����ǰֱ������1�������������ұ��

	car0->updatePmidr();
	uniformStraight(car0->pmidr->y - 0.0);
	return true;
}

/******************************************�ᳵ******************************************/
MeetingObs::MeetingObs()//�ᳵ
{
	road0 = make_unique<RoadNormal>(100.0);
	carObs = make_unique<CarNormal>(SWIDTH / 2.0, 50.0, PI, 50.0, 100.0);
	car0 = make_unique<CarNormal>(SWIDTH / 2.0, SHEIGHT - 70.0, 0.0, 40.0, 80.0);
	carObs->speed = -3.0;
	car0->speed = -4.0;

	carObs->updateStraightInfo();//��carObs׼��ֱ��

	car0->coutInfo();
	carObs->coutInfo();
	showScene();
	system("pause");
}

void MeetingObs::obsMoveStep()
{
	carObs->moveStraightStep();
}

void MeetingObs::showScene()//��ʾ
{
	BeginBatchDraw();
	cleardevice();

	road0->showRoad();
	carObs->showCar(RED);
	car0->showCar(BLACK);

	if (SHOWCIRCLE && car0->p_center)//���ƹ켣��
	{
		car0->showCircle();
	}

	EndBatchDraw();
	delay(DELAYTIME);
}

bool MeetingObs::planning_process()
{
	double total_speed = fabs(car0->speed) + fabs(carObs->speed);//�ٶȺͣ��ڱ������б��ֲ���
	double dis0 = fabs(car0->pmidf->y - carObs->pmidf->y);//��ʼ����
	if (total_speed <= 0.0)
	{
		cout << "��������ֹ" << endl;
		return false;
	}

	double dis_r_L = road0->right_boundary - carObs->plr->x;//�Ҽ��
	double target_r_x = road0->right_boundary - dis_r_L / 2.0;//��Ŀ���x
	cout << "dis_r_L = " << dis_r_L << ", target_r_x = " << target_r_x << endl;
	if (dis_r_L <= car0->car_width * 1.2)
	{
		cout << "�Ҳ���Ȳ�������" << endl;
		return false;
	}

	double time = dis0 / total_speed;//����ײ��ʱ�䣬ѭ������
	double meeting_point_y = car0->pmidf->y + car0->speed * time;//��ײ��λ��y
	double s0 = car0->pmidf->y - (meeting_point_y + start_dis);//ֱ�е����ϵ�ľ���
	cout << "total_speed = " << total_speed << ", dis0 = " << dis0 << ", meeting_point_y = " << meeting_point_y << ", s0 = " << s0 << endl;
	if (s0 < 0.0)
	{
		cout << "����̫���������ƿ�" << endl;
		return false;
	}

	uniformStraight(s0);//ֱ�е�������
	Point target_r_point(target_r_x, meeting_point_y);//��Ŀ���
	laneChange(target_r_point, LaneChangeType::doubleType);

	car0->updatePmidr();
	uniformStraight(car0->pmidr->y - 0.0);
	return true;
}