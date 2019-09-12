#include "pch.h"
#include "satori.h"
#include"bullet.h"
#include<list>

//返回子弹速度
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
	xPos = 384;									//敌人位置
	yPos = 350;
	m_pngSatori.Load(TEXT("satori.png"));		//加载贴图
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
	static float angle=0;						//发射角度，逐次增加
	float angleAcc = (float)t/8.0f;				//角加速度，与总帧数成正比
	angle += angleAcc;
	for (int i = 0; i < (int)level; i++)
	{
		bullet* newbullet = new bullet(xPos, yPos, /*sin((double)t * 3.14159 / 180.0)* 380*/angle + double(i) * 360 / level, GetBulletSpeed( level));//发射方向与子弹速度与难度有关
		bullets.push_back(newbullet);
	}
}
