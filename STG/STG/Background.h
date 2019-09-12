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
	int death;					//死亡次数
	Player m_Player;			//玩家
	satori m_Satori;			//敌人

	CImage m_pngBackground;		//背景图

	static int totalFrames;		//游戏运行总帧数
	static float fps;			//游戏当前fps
	static float currentTime;	//每次update的时间
	static float iniTime;		//游戏开始时的时间

	int level;					//游戏难度

	void startGame();			
	void stopGame();
	void update();

	Background() {};			//内容初始化由create完成
	~Background() {};

	//成员方法
	void SetLevel(int level);

	BOOL create(RECT& rect, CWnd* pParentWnd, UINT nID);


public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


