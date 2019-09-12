#pragma once
#include <afxwin.h>
#include"bullet.h"
//�����
class Player :
	public CWnd
{
private:
	int xPos;							//����
	int yPos;	
	static const float speed;			//����ƶ��ٶ�
public:
	Player();
	~Player() {};

	bool slow;							//״̬�ж�
	bool rebirth;
	CImage m_pngPlayer;					//�����ͼ
	CImage m_pngHitbox;					//�ж�����ͼ

	int GetxPos();
	int GetyPos();

	void move();						//�ƶ�������ÿ֡����
	double dist(bullet* b);				//��ȡ���ӵ��ľ���
	void death();						//����ʱ����
public:
	DECLARE_MESSAGE_MAP()
};

