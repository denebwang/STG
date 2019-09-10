#include "pch.h"
#include "Player.h"
#include "resource.h"
#include<cmath>
#include <mmsystem.h>
BEGIN_MESSAGE_MAP(Player, CWnd)
END_MESSAGE_MAP()

float Player::speed = 10;

Player::Player()
{
	xPos = 384;
	yPos = 820;
	xSpeed = ySpeed = 0;
	m_pngPlayer.Load(TEXT("player.png"));
	m_pngHitbox.Load(TEXT("hitbox.png"));
	GetAlpha(m_pngPlayer);	
	GetAlpha(m_pngHitbox);
	rebirth = slow =false;
}


void Player::move()
{ 
	if (GetAsyncKeyState(VK_SHIFT) < 0)
	{
		speed = 2.5;
		slow = true;
	}
	else
	{
		speed = 5;
		slow = false;
	}

	if (GetKeyState(VK_UP)< 0)
		ySpeed = -speed;
	if (GetKeyState(VK_DOWN) < 0)
		ySpeed = speed;
	if (GetKeyState(VK_LEFT) < 0)
		xSpeed = -speed;
	if (GetKeyState(VK_RIGHT) < 0)
		xSpeed = speed;

	xPos += xSpeed;
	yPos += ySpeed;

	if (xPos > 743)
		xPos = 743;
	if (xPos < 25)
		xPos = 25;
	if (yPos > 853)
		yPos = 853;
	if (yPos < 45)
		yPos = 45;

	xSpeed = ySpeed = 0;
}

double Player::dist(bullet* b)
{
	return sqrt(double((xPos-b->xPos)* (xPos - b->xPos)+(yPos- b->yPos)* (yPos - b->yPos)));
}

void Player::death()
{
	xPos = 384;
	yPos = 820;
	xSpeed = ySpeed = 0;
	mciSendString(TEXT("close dead.wav"), NULL, 0, NULL);
	mciSendString(TEXT("play dead.wav"), NULL, 0, NULL);
	rebirth = true;
}
