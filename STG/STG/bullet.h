#pragma once
#include <afxwin.h>
#include <atlimage.h>
class bullet :
	public CWnd
{
public:
	int speed;						//�ӵ��ٶ�
	float angle;					//���нǶ�
	float xPos;						//��ǰ����
	float yPos;

	static CImage m_pngBullet;		//�����ӵ�����һ����ͼ

	bullet(float xpos, float ypos, float angle, int speed);
	void move();					
};

