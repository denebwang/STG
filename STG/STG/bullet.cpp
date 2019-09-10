#include "pch.h"
#include "bullet.h"
#include <math.h>

CImage bullet::m_pngBullet;

bullet::bullet(float xpos, float ypos, float angle_, int speed_)
{
	speed = speed_;
	angle = angle_;
	xPos = xpos;
	yPos = ypos;
}

void bullet::move()
{
	xPos += double(speed) * cos(angle * ATR);
	yPos += double(speed) * sin(angle * ATR);
}
