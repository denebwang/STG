#include "pch.h"
#include "Player.h"
#include "resource.h"
#include<cmath>
#include <mmsystem.h>
BEGIN_MESSAGE_MAP(Player, CWnd)
END_MESSAGE_MAP()

const float Player::speed = 6;

Player::Player()
{
	xPos = 384;									//��ʼλ��
	yPos = 820;
	m_pngPlayer.Load(TEXT("player.png"));		//����ͼƬ
	m_pngHitbox.Load(TEXT("hitbox.png"));
	GetAlpha(m_pngPlayer);
	GetAlpha(m_pngHitbox);
	rebirth = slow =false;
}


int Player::GetxPos()
{
	return xPos;
}

int Player::GetyPos()
{
	return yPos;
}

void Player::move()
{ 
	float moveSpeed;
	if (GetAsyncKeyState(VK_SHIFT) < 0)				//�Ƿ����
	{
		moveSpeed = speed/2.0f;
		slow = true;
	}
	else
	{
		moveSpeed = speed;
		slow = false;
	}
	float ySpeed = 0.0f;
	float xSpeed = 0.0f;
	if (GetKeyState(VK_UP)< 0)
		ySpeed = -moveSpeed;
	if (GetKeyState(VK_DOWN) < 0)
		ySpeed = moveSpeed;
	if (GetKeyState(VK_LEFT) < 0)
		xSpeed = -moveSpeed;
	if (GetKeyState(VK_RIGHT) < 0)
		xSpeed = moveSpeed;

	if (xSpeed && ySpeed)							//ʸ���ϳɱ�֤�ƶ��ٶȲ���
	{
		xSpeed /= sqrtf(2.0f);
		ySpeed /= sqrtf(2.0f);
	}

	xPos += xSpeed;
	yPos += ySpeed;

	if (xPos > 743)									//�ƶ���Χ����
		xPos = 743;
	if (xPos < 25)
		xPos = 25;
	if (yPos > 853)
		yPos = 853;
	if (yPos < 45)
		yPos = 45;
}

double Player::dist(bullet* b)
{
	return sqrt(double((xPos-b->xPos)* (xPos - b->xPos)+(yPos- b->yPos)* (yPos - b->yPos)));
}

void Player::death()
{
	xPos = 384;										//���õ���ʼλ��
	yPos = 820;
	mciSendString(TEXT("close dead.wav"), NULL, 0, NULL);//ֹͣ��һ����Ч�Ĳ��ţ���ֹ����
	mciSendString(TEXT("play dead.wav"), NULL, 0, NULL);//����������Ч
	rebirth = true;									//��ҽ����޵�״̬
}
