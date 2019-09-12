#pragma once
#include "Player.h"
#include "satori.h"

#define LEVEL_EASY 2
#define LEVEL_NORM 4
#define LEVEL_HARD 6
#define LEVEL_LUNA 8

// Background

class Background : public CWnd
{
public:
	int death;					//��������
	Player m_Player;			//���
	satori m_Satori;			//����

	CImage m_pngBackground;		//����ͼ

	static int totalFrames;		//��Ϸ������֡��
	static float fps;			//��Ϸ��ǰfps
	static float currentTime;	//ÿ��update��ʱ��
	static float iniTime;		//��Ϸ��ʼʱ��ʱ��

	int level;					//��Ϸ�Ѷ�

	void startGame();			
	void stopGame();
	void update();

	Background() {};			//���ݳ�ʼ����create���
	~Background() {};

	//��Ա����
	void SetLevel(int level);

	BOOL create(RECT& rect, CWnd* pParentWnd, UINT nID);


public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


