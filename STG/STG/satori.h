#pragma once
#include <afxwin.h>
#include <atlimage.h>
#include <list>
#include "bullet.h"
//敌人
class satori :
	public CWnd
{
private:
	int xPos;					//坐标
	int yPos;
	
public:
	satori();
	~satori() {};

	CImage m_pngSatori;			//贴图
	std::list<bullet*> bullets;	//所有发射的子弹

	int Getx();
	int Gety();

	void shoot(int t,float );	//子弹发射函数
};

