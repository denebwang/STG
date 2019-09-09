#include "pch.h"
#include "satori.h"
#include<vector>

satori::satori()
{
	xPos = 384;
	yPos = 350;
	m_pngSatori.Load(TEXT("satori.png"));
	GetAlpha(m_pngSatori);
}
int calBulletSpeed(int level)
{
	switch (level)
	{
	case 2:
		return 3;
	case 4:
		return 5;
	case 6: 
		return 7;
	case 8:
		return 9;
	}
}

void satori::shoot(int t,float level)
{
	for (int i = 0; i < (int)level; i++)
	{
		bullet* newbullet = new bullet(xPos, yPos, sin(t*3.14159/180.0) * 450 + double(i)*360/ level,calBulletSpeed(level));
		bullets.push_back(newbullet);
	}
}
