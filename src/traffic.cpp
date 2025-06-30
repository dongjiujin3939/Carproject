#include "traffic.h"
using namespace std;
/******************************************障碍物******************************************/
Cone::Cone(const double& pos_x, const double& pos_y, const double& R) : r(R)//锥桶
{
	p_center = make_unique<Point>(pos_x, pos_y);
}

void Cone::showCone()//绘制
{
	setfillcolor(RGB(255, 127, 0));//橙色
	solidcircle(p_center->x, p_center->y, r);
}

Person::Person(const double& pos_x, const double& pos_y)//行人
{
	p_center = make_unique<Point>(pos_x, pos_y);
}

void Person::personMove()//行人移动
{
	p_center->x += speed;
}

void Person::showPerson()//绘制
{
	setfillcolor(YELLOW);
	fillcircle(p_center->x, p_center->y, r);
}

CarObsStatic::CarObsStatic(const double& pos_x, const double& pos_y, const double& heading, const double& width, const double& length)//静态障碍物
{
	initCar(pos_x, pos_y, heading, width, length);

	topPos = min(min(plf->y, prf->y), min(plr->y, prr->y));
	bottomPos = max(max(plf->y, prf->y), max(plr->y, prr->y));
	leftPos = min(min(plf->x, prf->x), min(plr->x, prr->x));
	rightPos = max(max(plf->x, prf->x), max(plr->x, prr->x));
	cout << "topPos = " << topPos << ", bottomPos = " << bottomPos << ", leftPos = " << leftPos << ", rightPos = " << rightPos << endl;
}