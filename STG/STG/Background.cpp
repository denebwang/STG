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
int Background::framerate = 60;
float Background::fps = 0;
float Background::currentTime = timeGetTime();
float Background::iniTime = currentTime;

void Background::initGame()
{
	death = 0;
}

BOOL Background::startGame()
{
	SetTimer(1, 1000/framerate, NULL);
	initGame();
	iniTime = timeGetTime();
	sndPlaySound(TEXT("少女さとり ～ 3rd eye.wav"), SND_ASYNC);
	return TRUE;
}

void Background::stopGame()
{
	sndPlaySound(NULL, SND_ASYNC);
	CString str;
	str.Format(TEXT("您一共死了%d次\n再来一把吗"), death);
	int result = MessageBoxW(str,TEXT("游戏到此为止了！"),MB_YESNO);
	switch (result)
	{
	case IDYES:
		m_Satori.bullets.clear();
		startGame();
		break;
	case IDNO:
		exit(0);
		break;
	}
}

void Background::update()
{
	m_Player.move();
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
		if (m_Player.dist((*iter)) < 10&&!m_Player.rebirth)
		{
			auto tempptr = *iter;
			iter = m_Satori.bullets.erase(iter);
			delete tempptr;

			death++;
			m_Player.death();
			SetTimer(2, 2000, NULL);
		}
	}
	m_Satori.move((double)totalFrames/50);

	if ((currentTime - iniTime) >= 90000)
	{
		KillTimer(1);
		stopGame();
		return;
	}
	CalculateFPS();
	totalFrames++;
	currentTime = timeGetTime();
	Invalidate();
}

void Background::CalculateFPS()
{

	static int frameCount = 0;
	static float currentTime = 0.0f;
	static float lastTime = 0.0f;
	frameCount++;
	currentTime = timeGetTime() / 1000.0f;
	if (currentTime - lastTime > 1.0f)
	{
		fps = frameCount / (currentTime - lastTime);
		lastTime = currentTime;
		frameCount = 0;
	}
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
		m_pngBackground.Draw(MemDC.m_hDC, 0, 0,768,898,0,898-getBGpos(),768,898);

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

			str.Format(TEXT("%.1f"), 90 - (currentTime - iniTime) / 1000.0f);

			MemDC.TextOutW(350, 30, str);

			str.Format(TEXT("FPS: %.1f"), fps);

			MemDC.TextOutW(650, 800, str);

			str.Format(TEXT("「波与粒的境界」"));

			MemDC.TextOutW(550, 50, str);
		}

		if (m_Player.m_pngPlayer.GetBPP() == 32)
		{
			int i;
			int j;
			for (i = 0; i < m_Player.m_pngPlayer.GetWidth(); i++)
			{
				for (j = 0; j < m_Player.m_pngPlayer.GetHeight(); j++)
				{
					byte* pByte = (byte*)m_Player.m_pngPlayer.GetPixelAddress(i, j);
					pByte[0] = pByte[0] * pByte[3] / 255;
					pByte[1] = pByte[1] * pByte[3] / 255;
					pByte[2] = pByte[2] * pByte[3] / 255;
				}
			}
		}
		m_Player.m_pngPlayer.Draw(MemDC.m_hDC, m_Player.xPos - 32, m_Player.yPos - 48,64,96,64*(totalFrames%8),0,64,96);

		if (m_Satori.m_pngSatori.GetBPP() == 32)
		{
			int i;
			int j;
			for (i = 0; i < m_Satori.m_pngSatori.GetWidth(); i++)
			{
				for (j = 0; j < m_Satori.m_pngSatori.GetHeight(); j++)
				{
					byte* pByte = (byte*)m_Satori.m_pngSatori.GetPixelAddress(i, j);
					pByte[0] = pByte[0] * pByte[3] / 255;
					pByte[1] = pByte[1] * pByte[3] / 255;
					pByte[2] = pByte[2] * pByte[3] / 255;
				}
			}
		}
		m_Satori.m_pngSatori.Draw(MemDC.m_hDC, m_Satori.xPos - 48, m_Satori.yPos - 64,96,128,96*((totalFrames/2)%4),128*((int)(((totalFrames/2)%8)/4)),96,128);

		for (auto iter = m_Satori.bullets.begin(); iter != m_Satori.bullets.end(); iter++)
		{
			if ((*iter)->m_pngBullet.GetBPP() == 32)
			{
				int i;
				int j;
				for (i = 0; i < (*iter)->m_pngBullet.GetWidth(); i++)
				{
					for (j = 0; j < (*iter)->m_pngBullet.GetHeight(); j++)
					{
						byte* pByte = (byte*)(*iter)->m_pngBullet.GetPixelAddress(i, j);
						pByte[0] = pByte[0] * pByte[3] / 255;
						pByte[1] = pByte[1] * pByte[3] / 255;
						pByte[2] = pByte[2] * pByte[3] / 255;
					}
				}
			}
			(*iter)->m_pngBullet.Draw(MemDC.m_hDC, (*iter)->xPos - 8, (*iter)->yPos - 14);
		}

		dc.StretchBlt(rectBig.left, rectBig.top, rectBig.Width(), rectBig.Height(), &MemDC, rectBig.left, rectBig.top, rectBig.Width(), rectBig.Height(), SRCCOPY);
		
		ValidateRect(&rectBig);
		bitmap.DeleteObject();
		ReleaseDC(&dc);
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


int Background::getBGpos()
{
	int movespeed = 5;
	int pos = (movespeed * totalFrames) % 768;
	return pos;
}