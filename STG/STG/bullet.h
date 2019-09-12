#pragma once
#include <afxwin.h>
#include <atlimage.h>
class bullet :
	public CWnd
{
public:
	int speed;						//子弹速度
	float angle;					//飞行角度
	float xPos;						//当前坐标
	float yPos;

	static CImage m_pngBullet;		//所有子弹公用一个贴图

	bullet(float xpos, float ypos, float angle, int speed);
	void move();					
};

