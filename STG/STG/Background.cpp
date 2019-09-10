// Background.cpp: 实现文件
//

#include "pch.h"
#include "STG.h"
#include "Background.h"
#include "Player.h"
#include "bullet.h"
#include "satori.h"
#include<vector>
#include <mmsystem.h>


int Background::totalFrames = 0;
float Background::fps = 0;
float Background::currentTime = timeGetTime();
float Background::iniTime = currentTime;


void Background::startGame()
{
	SetTimer(1, 15, NULL);
	death = totalFrames = 0;
	m_Satori.bullets.clear();
	iniTime = timeGetTime();
	sndPlaySound(TEXT("少女さとり ～ 3rd eye.wav"), SND_ASYNC);
}

void Background::stopGame()
{
	KillTimer(1);
	sndPlaySound(NULL, SND_ASYNC);
	CString str;
	str.Format(TEXT("您一共死了%d次\n再来一把吗"), death);
	int result = MessageBoxW(str,TEXT("游戏到此为止了！"),MB_YESNO);
	switch (result)
	{
	case IDYES:
		startGame();
		break;
	case IDNO:
		exit(0);
		break;
	default:
		break;
	}
}

void Background::update()
{
	m_Player.move();
	if(totalFrames%2)
		m_Satori.shoot(totalFrames,level);
	for (auto iter = m_Satori.bullets.begin(); iter != m_Satori.bullets.end(); iter++)
	{
		(*iter)->move();
		if ((*iter)->xPos > 768 || (*iter)->xPos < 0 || (*iter)->yPos>898 || (*iter)->yPos < 0)
		{
			auto tempptr = *iter;
			iter = m_Satori.bullets.erase(iter);
			delete tempptr;
		}
		if (!m_Player.rebirth && m_Player.dist((*iter)) < 8)
		{
			auto tempptr = *iter;
			iter = m_Satori.bullets.erase(iter);
			delete tempptr;

			death++;
			m_Player.death();
			SetTimer(2, 2000, NULL);
		}
	}

	if ((currentTime - iniTime) >= 90000)
	{
		stopGame();
	}
	fps = CalculateFPS();
	totalFrames++;
	currentTime = timeGetTime();
	Invalidate();
}



BOOL Background::create(RECT& rect, CWnd* pParentWnd, UINT nID)
{
	CString ClassName = AfxRegisterWndClass(CS_CLASSDC | CS_SAVEBITS | CS_HREDRAW | CS_VREDRAW, NULL, (HBRUSH)CBrush(RGB(0, 0, 255)), NULL);
	rect.right = rect.left + 768+2; 
	rect.bottom = rect.top + 898+2;
	if (!CWnd::CreateEx(WS_EX_CLIENTEDGE, ClassName, TEXT("STG"), WS_CHILD | WS_VISIBLE | WS_TABSTOP, rect, pParentWnd, nID, NULL))
		return FALSE;
	UpdateWindow();
	m_pngBackground.Load(TEXT("stage.png"));
	return TRUE;
}

BEGIN_MESSAGE_MAP(Background, CWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

void Background::OnPaint()
{
	CPaintDC dc(this);
			          
	CRect rectBig;
	this->GetClientRect(rectBig);

	{
		CBitmap bitmap;
		CDC MemDC;
		bitmap.CreateCompatibleBitmap(&dc, rectBig.Width(), rectBig.Height());
		MemDC.CreateCompatibleDC(&dc);
		MemDC.SelectObject(&bitmap);
		MemDC.SetStretchBltMode(HALFTONE);
		MemDC.FillSolidRect(rectBig, RGB(0, 0, 0));
		m_pngBackground.Draw(MemDC.m_hDC, 0, 0,768,898,0,898-getBGpos(totalFrames),768,898);

		{
			CFont font;
			font.CreateFontW(25,10, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, 
				OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
				DEFAULT_PITCH | FF_SWISS, TEXT("黑体"));
			MemDC.SelectObject(&font);

			CString str;

			MemDC.SetBkMode(TRANSPARENT);

			MemDC.SetTextColor(RGB(200, 200, 200));

			str.Format(TEXT("Death Count: %d"), death);

			MemDC.TextOutW(30, 30, str);

			str.Format(TEXT("%.2f"), 90.0f - (currentTime - iniTime) / 1000.0f);

			MemDC.TextOutW(350, 30, str);

			str.Format(TEXT("%.2fFPS"), fps);

			MemDC.TextOutW(670, 850, str);

			str.Format(TEXT("「波与粒的境界」"));

			MemDC.TextOutW(590, 30, str);
		}


		m_Player.m_pngPlayer.Draw(MemDC.m_hDC,
			m_Player.xPos - 32, m_Player.yPos - 48,
			64, 96, 64 * ((totalFrames/5) % 8), 0, 64, 96);

		if (m_Player.slow)
			m_Player.m_pngHitbox.Draw(MemDC.m_hDC,
				m_Player.xPos - 64, m_Player.yPos - 64, 
				128, 128, 0, 0, 128, 128);

		m_Satori.m_pngSatori.Draw(MemDC.m_hDC,
			m_Satori.xPos - 48, m_Satori.yPos - 64,
			96, 128, 96 * ((totalFrames / 10) % 4), 128 * ((int)(((totalFrames / 10) % 8) / 4)), 96, 128);

		for (auto iter = m_Satori.bullets.begin(); iter != m_Satori.bullets.end(); iter++)
			bullet::m_pngBullet.Draw(MemDC.m_hDC, (*iter)->xPos - 8, (*iter)->yPos - 14);

		dc.StretchBlt(rectBig.left, rectBig.top, rectBig.Width(), rectBig.Height(), &MemDC, rectBig.left, rectBig.top, rectBig.Width(), rectBig.Height(), SRCCOPY);
		
		ValidateRect(&rectBig);
		bitmap.DeleteObject();
		DeleteDC(MemDC);
	}
}

void Background::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case 1:
		update();
		break;
	case 2:
		m_Player.rebirth = false;
		KillTimer(2);
		break;
	}
	CWnd::OnTimer(nIDEvent);
}


BOOL Background::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}
