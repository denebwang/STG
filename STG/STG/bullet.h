#pragma once
#include <afxwin.h>
#include <atlimage.h>
class bullet :
	public CWnd
{
public:
	int speed;
	float angle;
	float xPos;
	float yPos;

	static CImage m_pngBullet;

	bullet(float xpos = 0, float ypos = 0, float angle = 0, int speed = 10);
	void move();
};

