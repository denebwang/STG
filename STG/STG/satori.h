#pragma once
#include <afxwin.h>
#include <atlimage.h>
#include <list>
#include "bullet.h"
//����
class satori :
	public CWnd
{
private:
	int xPos;					//����
	int yPos;
	
public:
	satori();
	~satori() {};

	CImage m_pngSatori;			//��ͼ
	std::list<bullet*> bullets;	//���з�����ӵ�

	int Getx();
	int Gety();

	void shoot(int t,float );	//�ӵ����亯��
};

