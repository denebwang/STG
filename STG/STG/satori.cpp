#include "pch.h"
#include "satori.h"
#include<vector>

satori::satori()
{
	xPos = 384;
	yPos = 100;
	m_pngSatori.Load(TEXT("satori.png"));
}

void satori::shoot(int t,float it)
{
	for (int i = 0; i < (int)it; i++)
	{
		bullet* newbullet = new bullet(xPos, yPos, sin(t*3.14159/180.0) * 360 + double(i)*360/it);
		bullets.push_back(newbullet);
	}
}

void satori::move(double t)
{
	xPos = 384 + 150 * sin(t);
}
