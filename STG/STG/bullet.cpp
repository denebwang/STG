#include "pch.h"
#include "bullet.h"
#include <math.h>



bullet::bullet(float xpos, float ypos, float angle_, int speed_)
{
	speed = speed_;
	angle = angle_;
	xPos = xpos;
	yPos = ypos;
	m_pngBullet.Load(TEXT("bullet.png"));
}

void bullet::move()
{
	xPos += double(speed) * cos(angle*ATR);
	yPos += double(speed) * sin(angle * ATR);
}
