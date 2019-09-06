#pragma once
#include <afxwin.h>
#include <atlimage.h>
#include <list>
#include "bullet.h"
class satori :
	public CWnd
{
public:
	satori();
	~satori() {};

	int xPos;
	int yPos;
	std::list<bullet*> bullets;
	CImage m_pngSatori;

	void shoot(int t,float );
	void move(double t);
};

