#include "pch.h"
#include "satori.h"
#include"bullet.h"
#include<vector>

satori::satori()
{
	xPos = 384;
	yPos = 350;
	m_pngSatori.Load(TEXT("satori.png"));
	bullet::m_pngBullet.Load(TEXT("bullet.png"));
	GetAlpha(bullet::m_pngBullet);
	GetAlpha(m_pngSatori);
}


void satori::shoot(int t,float level)
{
	for (int i = 0; i < (int)level; i++)
	{
		bullet* newbullet = new bullet(xPos, yPos, sin((double)t * 3.14159 / 180.0)* 380 + double(i) * 360 / level, level);
		bullets.push_back(newbullet);
	}
}
