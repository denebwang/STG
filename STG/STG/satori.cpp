#include "pch.h"
#include "satori.h"
#include"bullet.h"
#include<list>

//�����ӵ��ٶ�
int GetBulletSpeed(int level)
{
	switch (level)
	{
	case 2:
	case 4:
		return 4;
		break;
	case 6:
	case 8:
		return 6;
		break;
	}
}


satori::satori()
{
	xPos = 384;									//����λ��
	yPos = 350;
	m_pngSatori.Load(TEXT("satori.png"));		//������ͼ
	bullet::m_pngBullet.Load(TEXT("bullet.png"));
	GetAlpha(bullet::m_pngBullet);
	GetAlpha(m_pngSatori);
}


int satori::Getx()
{
	return xPos;
}

int satori::Gety()
{
	return yPos;
}

void satori::shoot(int t,float level)
{
	static float angle=0;						//����Ƕȣ��������
	float angleAcc = (float)t/8.0f;				//�Ǽ��ٶȣ�����֡��������
	angle += angleAcc;
	for (int i = 0; i < (int)level; i++)
	{
		bullet* newbullet = new bullet(xPos, yPos, /*sin((double)t * 3.14159 / 180.0)* 380*/angle + double(i) * 360 / level, GetBulletSpeed( level));//���䷽�����ӵ��ٶ����Ѷ��й�
		bullets.push_back(newbullet);
	}
}
