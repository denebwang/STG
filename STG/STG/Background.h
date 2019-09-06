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
	int death;
	int fps;
	int totalFrames;
	Player m_Player;
	satori m_Satori;

	int level;

	void initGame();
	BOOL startGame();
	Background();
	void update(int t);
	virtual ~Background();
	virtual BOOL create(RECT& rect, CWnd* pParentWnd, UINT nID);

protected:
	CImage m_pngBackground;
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


