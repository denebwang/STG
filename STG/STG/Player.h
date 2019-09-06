#pragma once
#include <afxwin.h>
#include"bullet.h"
class Player :
	public CWnd
{
public:
	Player();
	~Player() {};

	int xPos;
	int yPos;
	int xSpeed;
	int ySpeed;
	static int speed;
	CImage m_pngPlayer;
	

	void move();
	double dist(bullet* b);
public:
	DECLARE_MESSAGE_MAP()
};

