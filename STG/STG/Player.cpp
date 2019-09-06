#include "pch.h"
#include "Player.h"
#include "resource.h"
#include<cmath>
BEGIN_MESSAGE_MAP(Player, CWnd)
END_MESSAGE_MAP()

int Player::speed = 10;

Player::Player()
{
	xPos = 384;
	yPos = 820;
	xSpeed = ySpeed = 0;
	m_pngPlayer.Load(TEXT("player.png"));
}


void Player::move()
{ 
	if (GetAsyncKeyState(VK_SHIFT) < 0)
		speed = 5;
	else speed = 10;

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
