#include "pch.h"
#include "satori.h"
#include<vector>

satori::satori()
{
	xPos = 384;
	yPos = 400;
	m_pngSatori.Load(TEXT("satori.png"));
}
int calBulletSpeed(int level)
{
	switch (level)
	{
	case 2:
		return 7;
	case 4:
		return 10;
	case 6: 
		return 13;
	case 8:
		return 15;
	}
}

void satori::shoot(int t,float level)
{
	for (int i = 0; i < (int)level; i++)
	{
		bullet* newbullet = new bullet(xPos, yPos, sin(1.5*t*3.14159/180.0) * 540 + double(i)*360/ level,calBulletSpeed(level));
		bullets.push_back(newbullet);
	}
}

void satori::move(double t)
{
	//xPos = 384 + 150 * sin(t);
}
