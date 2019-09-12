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
	SetTimer(1, 15, NULL);										//15ms=64fps
	death = totalFrames = 0;									//初始化内容，用于重开游戏时清零
	m_Satori.bullets.clear();
	iniTime = timeGetTime();
	sndPlaySound(TEXT("少女さとり ～ 3rd eye.wav"), SND_ASYNC);//播放bgm
}

void Background::stopGame()
{
	KillTimer(1);												//停止刷新
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

void Background::update()										//每帧的更新函数
{
	m_Player.move();
	if(totalFrames%2)											//每两帧发射一轮子弹
		m_Satori.shoot(totalFrames,level);
	for (auto iter = m_Satori.bullets.begin(); iter != m_Satori.bullets.end(); iter++)//遍历子弹
	{
		(*iter)->move();
		if ((*iter)->xPos > 768 || (*iter)->xPos < 0 || (*iter)->yPos>898 || (*iter)->yPos < 0)//出边界则删除
		{
			auto tempptr = *iter;
			iter = m_Satori.bullets.erase(iter);
			delete tempptr;
		}
		if (!m_Player.rebirth && m_Player.dist((*iter)) < 8)					//命中玩家删除子弹并记录
		{
			auto tempptr = *iter;
			iter = m_Satori.bullets.erase(iter);
			delete tempptr;

			death++;
			m_Player.death();
			SetTimer(2, 2000, NULL);											//中弹后2秒无敌时间
		}
	}

	if ((currentTime - iniTime) >= 90000)										//游戏计时
	{
		stopGame();
	}
	fps = CalculateFPS();														//更新fps
	totalFrames++;																//总帧数计数
	currentTime = timeGetTime();												//更新时间用于计时
	Invalidate();																//重绘窗口
}



void Background::SetLevel(int level)
{
	this->level = level;
}

BOOL Background::create(RECT& rect, CWnd* pParentWnd, UINT nID)
{
	CString ClassName = AfxRegisterWndClass(CS_CLASSDC | CS_SAVEBITS | CS_HREDRAW | CS_VREDRAW, NULL, (HBRUSH)CBrush(RGB(0, 0, 255)), NULL);
	rect.right = rect.left + 768+2; //游戏区域大小
	rect.bottom = rect.top + 898+2;
	if (!CWnd::CreateEx(WS_EX_CLIENTEDGE, ClassName, TEXT("STG"), WS_CHILD | WS_VISIBLE | WS_TABSTOP, rect, pParentWnd, nID, NULL))
		return FALSE;
	UpdateWindow();
	m_pngBackground.Load(TEXT("stage.png"));									//载入背景图片
	return TRUE;
}

BEGIN_MESSAGE_MAP(Background, CWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

void Background::OnPaint()														//画面绘制函数
{
	CPaintDC dc(this);
			          
	CRect rectBig;
	this->GetClientRect(rectBig);

	{
		CBitmap bitmap;															//创建背景位图
		CDC MemDC;
		bitmap.CreateCompatibleBitmap(&dc, rectBig.Width(), rectBig.Height());
		MemDC.CreateCompatibleDC(&dc);
		MemDC.SelectObject(&bitmap);
		MemDC.SetStretchBltMode(HALFTONE);
		MemDC.FillSolidRect(rectBig, RGB(0, 0, 0));
		m_pngBackground.Draw(MemDC.m_hDC, 0, 0,768,898,0,898-getBGpos(totalFrames),768,898);//绘制背景图

		//输出文字
		{
			CFont font;																		//设置字体
			font.CreateFontW(25,10, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, 
				OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
				DEFAULT_PITCH | FF_SWISS, TEXT("黑体"));
			MemDC.SelectObject(&font);

			CString str;

			MemDC.SetBkMode(TRANSPARENT);

			MemDC.SetTextColor(RGB(200, 200, 200));

			str.Format(TEXT("Death Count: %d"), death);										//死亡计数器

			MemDC.TextOutW(30, 30, str);

			str.Format(TEXT("%.2f"), 90.0f - (currentTime - iniTime) / 1000.0f);			//倒计时

			MemDC.TextOutW(350, 30, str);

			str.Format(TEXT("%.2fFPS"), fps);												//FPS显示

			MemDC.TextOutW(670, 850, str);

			str.Format(TEXT("「波与粒的境界」"));											//弹幕名称
				
			MemDC.TextOutW(590, 30, str);
		}

		//绘制各对象
		m_Player.m_pngPlayer.Draw(MemDC.m_hDC,													
			m_Player.GetxPos() - 32, m_Player.GetyPos() - 48,											//8种贴图循环播放
			64, 96, 64 * ((totalFrames / 5) % 8), 0, 64, 96);								//实现动画效果
																							

		if (m_Player.slow)																	//低速下显示判定点
			m_Player.m_pngHitbox.Draw(MemDC.m_hDC,
				m_Player.GetxPos() - 64, m_Player.GetyPos() - 64,
				128, 128, 0, 0, 128, 128);

		m_Satori.m_pngSatori.Draw(MemDC.m_hDC,
			m_Satori.Getx() - 48, m_Satori.Gety() - 64,
			96, 128, 96 * ((totalFrames / 10) % 4), 128 * ((int)(((totalFrames / 10) % 8) / 4)), 96, 128);

		for (auto iter = m_Satori.bullets.begin(); iter != m_Satori.bullets.end(); iter++)
			bullet::m_pngBullet.Draw(MemDC.m_hDC, (*iter)->xPos - 8, (*iter)->yPos - 14);
		//将内存dc内容贴至总dc
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
	case 1://游戏循环
		update();
		break;
	case 2://无敌计时
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
