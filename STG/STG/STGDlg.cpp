
// STGDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "STG.h"
#include "STGDlg.h"
#include "afxdialogex.h"
#include "Background.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif





CSTGDlg::CSTGDlg(CWnd* pParent)
	: CDialogEx(IDD_STG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON);
}

void CSTGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSTGDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_UPDATE_COMMAND_UI(ID_QUIT, &CSTGDlg::OnUpdateQuit)
	ON_COMMAND(ID_START, &CSTGDlg::OnStart)
	ON_COMMAND(ID_EASY, &CSTGDlg::OnEasy)
	ON_COMMAND(ID_NORMAL, &CSTGDlg::OnNormal)
	ON_COMMAND(ID_HARD, &CSTGDlg::OnHard)
	ON_COMMAND(ID_LUNATIC, &CSTGDlg::OnLunatic)
END_MESSAGE_MAP()



BOOL CSTGDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);	
	SetIcon(m_hIcon, FALSE);

	m_menu.LoadMenuW(IDR_MENU);
	SetMenu(& m_menu);

	CMenu* level_menu= m_menu.GetSubMenu(1)->GetSubMenu(0);
	level_menu->CheckMenuRadioItem(0, 3, 1, MF_BYPOSITION);

	m_Background.create(CRect(0, 0, 0, 0), this, IDB_BG);
	m_Background.level = LEVEL_NORM;
	::SetWindowPos(this->m_hWnd, HWND_BOTTOM, 0, 0, 768, 960, SWP_NOZORDER);
	return TRUE; 
}

void CSTGDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CSTGDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSTGDlg::OnUpdateQuit(CCmdUI* pCmdUI)
{
	CDialog::OnCancel();
}


void CSTGDlg::OnStart()
{
	m_Background.startGame();
}


void CSTGDlg::OnEasy()
{
	CMenu* level_menu = m_menu.GetSubMenu(1)->GetSubMenu(0);
	level_menu->CheckMenuRadioItem(0, 3, 0, MF_BYPOSITION);
	m_Background.level = LEVEL_EASY;
}


void CSTGDlg::OnNormal()
{
	CMenu* level_menu = m_menu.GetSubMenu(1)->GetSubMenu(0);
	level_menu->CheckMenuRadioItem(0, 3, 1, MF_BYPOSITION);
	m_Background.level = LEVEL_NORM;
}


void CSTGDlg::OnHard()
{
	CMenu* level_menu = m_menu.GetSubMenu(1)->GetSubMenu(0);
	level_menu->CheckMenuRadioItem(0, 3, 2, MF_BYPOSITION);
	m_Background.level = LEVEL_HARD;
}


void CSTGDlg::OnLunatic()
{
	CMenu* level_menu = m_menu.GetSubMenu(1)->GetSubMenu(0);
	level_menu->CheckMenuRadioItem(0, 3, 3, MF_BYPOSITION);
	m_Background.level = LEVEL_LUNA;
}
