// Background.cpp: 实现文件
//

#include "pch.h"
#include "STG.h"
#include "Background.h"
#include "Player.h"
#include "bullet.h"
#include "satori.h"
#include<vector>

void Background::initGame()
{
	death = 0;
}

BOOL Background::startGame()
{
	SetTimer(1, 1000/fps, NULL);
	initGame();
	return TRUE;
}

Background::Background()
{
	death = 0;
	fps = 60;
	totalFrames = 0;
	level = LEVEL_LUNA;
}

void Background::update(int fps)
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
		if (m_Player.dist((*iter)) < 5)
			death++;
	}
	m_Satori.move((double)totalFrames/50);
	totalFrames++;
	Invalidate();
}

Background::~Background()
{
}

BOOL Background::create(RECT& rect, CWnd* pParentWnd, UINT nID)
{
	CString ClassName = AfxRegisterWndClass(CS_CLASSDC | CS_SAVEBITS | CS_HREDRAW | CS_VREDRAW, NULL, (HBRUSH)CBrush(RGB(0, 0, 255)), NULL);
	rect.right = rect.left + 768+2;   //区域大小
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
			m_pngBackground.Draw(MemDC.m_hDC, 0, 0);

			CString str;

			MemDC.SetBkMode(TRANSPARENT);

			MemDC.SetTextColor(RGB(200, 200, 200));

			str.Format(TEXT("Death Count: %d"), death);

			MemDC.TextOutW(30, 30, str);


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
			m_Player.m_pngPlayer.Draw(MemDC.m_hDC, m_Player.xPos - 25, m_Player.yPos - 45);

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
			m_Satori.m_pngSatori.Draw(MemDC.m_hDC, m_Satori.xPos - 31, m_Satori.yPos - 60);

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
		}
	}

void Background::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case 1:
		update(fps);
		
	}

	CWnd::OnTimer(nIDEvent);
}


BOOL Background::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
	return CWnd::OnEraseBkgnd(pDC);
}
