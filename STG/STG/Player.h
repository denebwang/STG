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
	static float speed;
	bool slow;
	bool rebirth;
	CImage m_pngPlayer;
	CImage m_pngHitbox;
	
	void move();
	double dist(bullet* b);
	void death();
public:
	DECLARE_MESSAGE_MAP()
};

